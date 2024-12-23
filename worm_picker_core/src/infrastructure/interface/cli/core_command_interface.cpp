// core_command_interface.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/infrastructure/interface/cli/core_command_interface.hpp"

CoreCommandInterface::CoreCommandInterface(rclcpp::Node::SharedPtr node)
    : node_(std::move(node))  
{
    client_ = node_->create_client<TaskCommand>(SERVICE_NAME);
    waitForService();
}

void CoreCommandInterface::waitForService() 
{
    while (!client_->wait_for_service(std::chrono::seconds(1))) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(node_->get_logger(), "Interrupted while waiting for service.");
            rclcpp::shutdown();
            std::exit(EXIT_FAILURE);
        }
    }
}

void CoreCommandInterface::sendRequest(const std::string &command) 
{
    auto request = std::make_shared<TaskCommand::Request>();
    request->command = command;

    auto future = client_->async_send_request(request);
    auto status = rclcpp::spin_until_future_complete(node_, future);

    if (status != rclcpp::FutureReturnCode::SUCCESS) {
        RCLCPP_ERROR(node_->get_logger(), "Failed to call service.");
        return;
    }

    auto response = future.get();
    if (!response->success) {
        RCLCPP_ERROR(node_->get_logger(), "Task execution failed.");
    }
}

void CoreCommandInterface::runCommandLoop() 
{
    std::string command;
    while (rclcpp::ok()) {
        std::cout << "Enter command (or 'quit'): ";
        if (!std::getline(std::cin >> std::ws, command)) {
            break;
        }
        if (command == "quit" || command == "q") {
            break;
        }
        sendRequest(command);
    }
}