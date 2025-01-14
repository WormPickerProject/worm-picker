// core_command_interface.hpp
//
// Copyright (c) 2025
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

    void awaitService();
    bool sendRequest(const std::string &command);
    void processUserCommand(const std::string &command);
    void moveToAllPoints();
    void moveToRowPoints(const std::string &row_letter);
    void movePlatesRow(const std::string &row_letter);
    void movePlatesAll();
    std::vector<std::string> getRowPoints(char row) const;
    bool isRowLetter(const std::string &row_letter) const;
    void movePlatesRowSequence(const std::vector<std::string> &row_points);

    static constexpr const char* SERVICE_NAME = "/task_command";
    rclcpp::Node::SharedPtr node_;
    rclcpp::Client<TaskCommand>::SharedPtr client_;
    std::vector<std::string> move_to_points_;
};

#endif // CORE_COMMAND_INTERFACE_HPP