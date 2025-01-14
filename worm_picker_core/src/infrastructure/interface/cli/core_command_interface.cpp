// core_command_interface.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/infrastructure/interface/cli/core_command_interface.hpp"

CoreCommandInterface::CoreCommandInterface(rclcpp::Node::SharedPtr node)
    : node_(std::move(node))
{
    client_ = node_->create_client<TaskCommand>(SERVICE_NAME);
    awaitService();
    move_to_points_ = {
        "A1", "A2",
        "B1", "B2",
        "C1", "C2", "C3",
        "D1", "D2", "D3",
        "E1", "E2", "E3", "E4",
        "F1", "F2", "F3",
        "G1", "G2", "G3", "G4",
        "H1", "H2", "H3",
        "I1", "I2", "I3", "I4",
        "J1", "J2", "J3",
        "K1", "K2", "K3",
        "L1", "L2",
        "M1", "M2"
    };
}

void CoreCommandInterface::awaitService()
{
    using namespace std::chrono_literals;
    while (!client_->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(node_->get_logger(),  "Interrupted while waiting. Shutting down...");
            rclcpp::shutdown();
            std::exit(EXIT_FAILURE);
        }
    }
}

bool CoreCommandInterface::sendRequest(const std::string &command)
{
    auto request = std::make_shared<TaskCommand::Request>();
    request->command = command;

    auto future = client_->async_send_request(request);
    const auto status = rclcpp::spin_until_future_complete(node_, future);
    
    if (status != rclcpp::FutureReturnCode::SUCCESS) {
        RCLCPP_ERROR(node_->get_logger(), "Failed to call service '%s'.", SERVICE_NAME);
        return false;
    }

    auto response = future.get();
    if (!response->success) {
        RCLCPP_ERROR(node_->get_logger(), "Task execution failed for command '%s'.", command.c_str());
        return false;
    }
    
    return true;
}

void CoreCommandInterface::runCommandLoop()
{
    std::string command;
    while (rclcpp::ok()) {
        std::cout << "Enter command (or 'quit'/'q'): ";
        if (!std::getline(std::cin >> std::ws, command)) {
            break;
        }
        if (command == "quit" || command == "q") {
            break;
        }

        processUserCommand(command);
    }
}

void CoreCommandInterface::processUserCommand(const std::string &command)
{
    if (command == "moveToAllPoints") {
        moveToAllPoints();
    } 
    else if (command == "movePlatesAll") {
        movePlatesAll();
    }
    else if (command.rfind("moveToRowPoints:", 0) == 0) {
        const auto row_letter = command.substr(16); 
        moveToRowPoints(row_letter);
    }
    else if (command.rfind("movePlatesRow:", 0) == 0) {
        const auto row_letter = command.substr(14); 
        movePlatesRow(row_letter);
    }
    else {
        sendRequest(command);
    }
}

void CoreCommandInterface::moveToAllPoints()
{
    for (const auto &point : move_to_points_) {
        sendRequest("moveToPoint:" + point);
    }
}

void CoreCommandInterface::moveToRowPoints(const std::string &row_letter)
{
    if (!isRowLetter(row_letter)) {
        RCLCPP_ERROR(node_->get_logger(), "Invalid row letter: '%s'", row_letter.c_str());
        return;
    }
    const char row = static_cast<char>(std::toupper(row_letter[0]));
    
    for (const auto &point : move_to_points_) {
        if (!point.empty() && point.front() == row) {
            sendRequest("moveToPoint:" + point);
        }
    }
}

void CoreCommandInterface::movePlatesRow(const std::string &row_letter)
{
    if (!isRowLetter(row_letter)) {
        RCLCPP_ERROR(node_->get_logger(), "Invalid row letter: '%s'", row_letter.c_str());
        return;
    }
    const char row = static_cast<char>(std::toupper(row_letter[0]));
    
    auto row_points = getRowPoints(row);
    movePlatesRowSequence(row_points);
}

void CoreCommandInterface::movePlatesAll()
{
    sendRequest("pickPlateWorkStation:C1");

    static const std::vector<char> rows = {'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
    for (size_t i = 0; i < rows.size(); ++i) {
        auto row_points = getRowPoints(rows[i]);

        for (size_t j = 0; j + 1 < row_points.size(); ++j) {
            const auto &next_point = row_points[j + 1];
            sendRequest("placePlateWorkStation:" + next_point);
            sendRequest("pickPlateWorkStation:" + next_point);
        }

        if (i + 1 < rows.size()) {
            const auto next_row_first = std::string(1, rows[i + 1]) + "1";
            sendRequest("placePlateWorkStation:" + next_row_first);
            sendRequest("pickPlateWorkStation:" + next_row_first);
        } else {
            sendRequest("placePlateWorkStation:C1");
        }
    }

    sendRequest("home");
    sendRequest("homeEndFactor");
}

std::vector<std::string> CoreCommandInterface::getRowPoints(char row) const
{
    std::vector<std::string> result;
    for (const auto &point : move_to_points_) {
        if (!point.empty() && point.front() == row) {
            result.push_back(point);
        }
    }
    return result;
}

bool CoreCommandInterface::isRowLetter(const std::string &row_letter) const
{
    return (row_letter.size() == 1 && std::isalpha(row_letter[0]));
}

void CoreCommandInterface::movePlatesRowSequence(const std::vector<std::string> &row_points)
{
    for (size_t i = 0; i + 1 < row_points.size(); ++i) {
        const auto &current_point = row_points[i];
        const auto &next_point    = row_points[i + 1];

        sendRequest("pickPlateWorkStation:" + current_point);
        sendRequest("placePlateWorkStation:" + next_point);
    }

    sendRequest("home");
    sendRequest("homeEndFactor");
}