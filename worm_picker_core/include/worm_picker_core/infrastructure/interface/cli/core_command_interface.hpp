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
    bool sendCommandRequest(const std::string &command);
    std::string formatCommand(const std::string &base_command) const;
    void processUserCommand(const std::string &command);
    void moveAllPoints();
    void moveRowPoints(const std::string &row_letter);
    void moveRowPlates(const std::string &row_letter);
    void moveAllPlates();
    void moveAllPlatesRandom();
    std::vector<std::string> getRowPoints(char row) const;
    bool isRowLetter(const std::string &row_letter) const;
    void movePlatesRowSequence(const std::vector<std::string> &row_points);
    bool parseVelAcc(const std::string &value, double &result) const;

    static constexpr const char* SERVICE_NAME = "/task_command";
    rclcpp::Node::SharedPtr node_;
    rclcpp::Client<TaskCommand>::SharedPtr client_;
    std::vector<std::string> move_to_points_;
    std::optional<double> current_vel_;
    std::optional<double> current_acc_;
};

#endif // CORE_COMMAND_INTERFACE_HPP