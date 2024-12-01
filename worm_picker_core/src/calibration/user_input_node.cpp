// user_input_node.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/calibration/user_input_node.hpp"

UserInputNode::UserInputNode(int argc, char **argv)
    : service_name_("/calibration_command")
{
    initializeROS(argc, argv);
}

void UserInputNode::initializeROS(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    node_ = rclcpp::Node::make_shared("user_input_node");
    client_ = node_->create_client<CalibrationCommandService>(service_name_);
    waitForService();
}

void UserInputNode::waitForService()
{
    while (!client_->wait_for_service(std::chrono::seconds(1))) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(node_->get_logger(), "Interrupted while waiting for the service. Exiting.");
            rclcpp::shutdown();
            exit(1);
        }
    }
    RCLCPP_INFO(node_->get_logger(), "Service '%s' is available.", service_name_.c_str());
}

std::shared_ptr<worm_picker_custom_msgs::srv::CalibrationCommand::Request> UserInputNode::createRequest(const std::string& command) const
{
    auto request = std::make_shared<worm_picker_custom_msgs::srv::CalibrationCommand::Request>();
    request->command = command;
    return request;
}

void UserInputNode::sendRequest(const std::shared_ptr<worm_picker_custom_msgs::srv::CalibrationCommand::Request>& request) const
{
    auto result_future = client_->async_send_request(request);
    receiveResponse(result_future.share());
}

void UserInputNode::receiveResponse(const rclcpp::Client<worm_picker_custom_msgs::srv::CalibrationCommand>::SharedFuture& result_future) const
{
    if (rclcpp::spin_until_future_complete(node_, result_future) == rclcpp::FutureReturnCode::SUCCESS) {
        auto result = result_future.get();
        if (result->success) {
            RCLCPP_INFO(node_->get_logger(), "Command executed successfully: %s", result->feedback.c_str());
        } else {
            RCLCPP_ERROR(node_->get_logger(), "Command failed: %s", result->feedback.c_str());
        }
    } else {
        RCLCPP_ERROR(node_->get_logger(), "Failed to call service.");
    }
}

void UserInputNode::runCommandLoop()
{
    std::string command;
    while (rclcpp::ok()) {
        std::cout << "Enter command ('next', 'retry', 'record', or 'quit'): ";
        std::cin >> command;

        if (command == "quit" || command == "q") {
            break;
        } else if (command == "next" || command == "retry" || command == "record") {
            auto request = createRequest(command);
            sendRequest(request);
        } else {
            std::cout << "Unknown command. Please enter 'next', 'retry', 'record', or 'quit'." << std::endl;
        }
    }
}

int main(int argc, char **argv)
{
    auto user_input_node = std::make_shared<UserInputNode>(argc, argv);
    user_input_node->runCommandLoop();

    rclcpp::shutdown();
    return 0;
}
