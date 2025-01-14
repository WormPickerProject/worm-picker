// core_command_interface.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <random>
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

bool CoreCommandInterface::parseVelAcc(const std::string& value, double& result) const 
{
    try {
        result = std::stod(value);
        return result >= 0.0 && result <= 1.0;
    } catch (...) {
        return false;
    }
}

std::string CoreCommandInterface::formatCommand(const std::string& base_command) const 
{
    if (!current_vel_.has_value() && !current_acc_.has_value()) {
        return base_command;
    }
    
    std::string formatted_command = base_command;
    if (current_vel_.has_value()) {
        formatted_command += ":" + std::to_string(current_vel_.value());
    }
    if (current_acc_.has_value()) {
        formatted_command += ":" + std::to_string(current_acc_.value());
    }
    return formatted_command;
}

bool CoreCommandInterface::sendCommandRequest(const std::string& command) 
{
    return sendRequest(formatCommand(command));
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

void CoreCommandInterface::processUserCommand(const std::string& command) 
{
    current_vel_ = std::nullopt;
    current_acc_ = std::nullopt;
    
    std::vector<std::string> parts;
    std::istringstream iss(command);
    std::string part;
    
    while (std::getline(iss, part, ':')) {
        parts.push_back(part);
    }
    
    if (parts.empty()) return;
    
    if (parts.size() >= 3) {
        double vel, acc;
        if (parseVelAcc(parts[parts.size()-2], vel) && 
            parseVelAcc(parts[parts.size()-1], acc)) {
            current_vel_ = vel;
            current_acc_ = acc;
            parts.resize(parts.size() - 2);
        }
    }
    
    const std::string& base_command = parts[0];
    if (base_command == "moveAllPoints") {
        moveAllPoints();
    }
    else if (base_command == "moveAllPlates") {
        moveAllPlates();
    }
    else if (base_command == "moveAllPlatesRandom") {
        moveAllPlatesRandom();
    }
    else if (base_command == "moveRowPoints" && parts.size() >= 2) {
        moveRowPoints(parts[1]);
    }
    else if (base_command == "moveRowPlates" && parts.size() >= 2) {
        moveRowPlates(parts[1]);
    }
    else {
        sendRequest(command);
    }
}

void CoreCommandInterface::moveAllPoints()
{
    for (const auto &point : move_to_points_) {
        sendCommandRequest("moveToPoint:" + point);
    }
    sendCommandRequest("homeEndFactor");
}

void CoreCommandInterface::moveRowPoints(const std::string &row_letter)
{
    if (!isRowLetter(row_letter)) {
        RCLCPP_ERROR(node_->get_logger(), "Invalid row letter: '%s'", row_letter.c_str());
        return;
    }
    const char row = static_cast<char>(std::toupper(row_letter[0]));
    
    for (const auto &point : move_to_points_) {
        if (!point.empty() && point.front() == row) {
            sendCommandRequest("moveToPoint:" + point);
        }
    }
    sendCommandRequest("homeEndFactor");
}

void CoreCommandInterface::moveRowPlates(const std::string &row_letter)
{
    if (!isRowLetter(row_letter)) {
        RCLCPP_ERROR(node_->get_logger(), "Invalid row letter: '%s'", row_letter.c_str());
        return;
    }
    const char row = static_cast<char>(std::toupper(row_letter[0]));
    
    auto row_points = getRowPoints(row);
    movePlatesRowSequence(row_points);
}

void CoreCommandInterface::moveAllPlates()
{
    sendCommandRequest("pickPlateWorkStation:G1");
    sendCommandRequest("placePlateWorkStation:A1");
    sendCommandRequest("pickPlateWorkStation:A1");
    sendCommandRequest("placePlateWorkStation:B1");
    sendCommandRequest("pickPlateWorkStation:B1");
    sendCommandRequest("placePlateWorkStation:C1");
    sendCommandRequest("pickPlateWorkStation:C1");

    static const std::vector<char> rows = {'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
    for (size_t i = 0; i < rows.size(); ++i) {
        auto row_points = getRowPoints(rows[i]);

        for (size_t j = 0; j + 1 < row_points.size(); ++j) {
            const auto &next_point = row_points[j + 1];
            sendCommandRequest("placePlateWorkStation:" + next_point);
            sendCommandRequest("pickPlateWorkStation:" + next_point);
        }

        if (i + 1 < rows.size()) {
            const auto next_row_first = std::string(1, rows[i + 1]) + "1";
            sendCommandRequest("placePlateWorkStation:" + next_row_first);
            sendCommandRequest("pickPlateWorkStation:" + next_row_first);
        } else {
            sendCommandRequest("placePlateWorkStation:L1");
            sendCommandRequest("pickPlateWorkStation:L1");
            sendCommandRequest("placePlateWorkStation:M1");
            sendCommandRequest("pickPlateWorkStation:M1");
            sendCommandRequest("placePlateWorkStation:G1");
        }
    }
    sendCommandRequest("homeEndFactor");
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
    if (row_points.front() != "G1") {
        sendCommandRequest("pickPlateWorkStation:G1");
        sendCommandRequest("placePlateWorkStation:" + row_points.front());
    }

    for (size_t i = 0; i + 1 < row_points.size(); ++i) {
        const auto &current_point = row_points[i];
        const auto &next_point    = row_points[i + 1];

        sendCommandRequest("pickPlateWorkStation:" + current_point);
        sendCommandRequest("placePlateWorkStation:" + next_point);
    }

    sendCommandRequest("pickPlateWorkStation:" + row_points.back());
    sendCommandRequest("placePlateWorkStation:G1");
    sendCommandRequest("homeEndFactor");
}

void CoreCommandInterface::moveAllPlatesRandom()
{
    std::vector<std::string> available_points;
    for (const auto& point : move_to_points_) {
        if (point != "A2" && point != "B2" && point != "L2" && point != "M2") {
            available_points.push_back(point);
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    sendCommandRequest("pickPlateWorkStation:G1");

    available_points.erase(
        std::remove(available_points.begin(), available_points.end(), "G1"),
        available_points.end()
    );

    const size_t total_points = available_points.size();
    size_t points_processed = 0;
    while (!available_points.empty()) {
        std::uniform_int_distribution<> dis(0, available_points.size() - 1);
        int random_index = dis(gen);

        std::string next_point = available_points[random_index];
        available_points.erase(available_points.begin() + random_index);

        points_processed++;
        RCLCPP_INFO(node_->get_logger(), "Moving plate %zu/%zu - Position: %s", 
                    points_processed, total_points, next_point.c_str());

        sendCommandRequest("placePlateWorkStation:" + next_point);
        sendCommandRequest("pickPlateWorkStation:" + next_point);
    }

    sendCommandRequest("placePlateWorkStation:G1");
    sendCommandRequest("homeEndFactor");
}