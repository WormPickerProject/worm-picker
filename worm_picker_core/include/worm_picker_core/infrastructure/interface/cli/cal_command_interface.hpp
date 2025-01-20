// cal_command_interface.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <worm_picker_custom_msgs/srv/calibration_command.hpp>

class CalCommandInterface {
public:
    explicit CalCommandInterface(rclcpp::Node::SharedPtr node);
    void runCommandLoop();

private:
    using CalibrationCommand = worm_picker_custom_msgs::srv::CalibrationCommand;

    void waitForService();
    void sendRequest(const std::string &command);

    static constexpr const char* SERVICE_NAME = "/calibration_command";
    rclcpp::Node::SharedPtr node_;
    rclcpp::Client<CalibrationCommand>::SharedPtr client_;
};