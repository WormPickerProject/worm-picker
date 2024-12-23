// core_command_interface.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef CORE_COMMAND_INTERFACE_HPP
#define CORE_COMMAND_INTERFACE_HPP

#include <rclcpp/rclcpp.hpp>
#include <worm_picker_custom_msgs/srv/task_command.hpp>

class CoreCommandInterface {
public:
    explicit CoreCommandInterface(rclcpp::Node::SharedPtr node);
    void runCommandLoop();

private:
    using TaskCommand = worm_picker_custom_msgs::srv::TaskCommand;

    void waitForService();
    void sendRequest(const std::string &command);

    static constexpr const char* SERVICE_NAME = "/task_command";
    rclcpp::Node::SharedPtr node_;
    rclcpp::Client<TaskCommand>::SharedPtr client_;
};

#endif // CORE_COMMAND_INTERFACE_HPP
