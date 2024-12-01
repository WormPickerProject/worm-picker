// user_input_node.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef USER_INPUT_NODE_HPP
#define USER_INPUT_NODE_HPP

#include <rclcpp/rclcpp.hpp>
#include <worm_picker_custom_msgs/srv/calibration_command.hpp>

class UserInputNode {
public:
    UserInputNode(int argc, char **argv);
    void runCommandLoop();

private:
    void initializeROS(int argc, char **argv);
    void waitForService();
    std::shared_ptr<worm_picker_custom_msgs::srv::CalibrationCommand::Request> createRequest(const std::string& command) const;
    void sendRequest(const std::shared_ptr<worm_picker_custom_msgs::srv::CalibrationCommand::Request>& request) const;
    void receiveResponse(const rclcpp::Client<worm_picker_custom_msgs::srv::CalibrationCommand>::SharedFuture& result_future) const;

    using CalibrationCommandService = worm_picker_custom_msgs::srv::CalibrationCommand;

    rclcpp::Node::SharedPtr node_;
    rclcpp::Client<CalibrationCommandService>::SharedPtr client_;
    std::string service_name_;
};

#endif // USER_INPUT_NODE_HPP
