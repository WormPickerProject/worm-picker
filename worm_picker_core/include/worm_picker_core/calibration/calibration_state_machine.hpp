// calibrations_state_machine.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef CALIBRATION_STATE_MACHINE_HPP
#define CALIBRATION_STATE_MACHINE_HPP

#include <rclcpp/rclcpp.hpp>
#include <worm_picker_custom_msgs/srv/calibration_command.hpp>
#include "worm_picker_core/calibration/robot_controller.hpp"

class CalibrationStateMachine {
public:
    enum class State { Idle, Moving, AwaitingAdjustment, Completed };

    CalibrationStateMachine(const rclcpp::Node::SharedPtr& node,
                            const std::shared_ptr<RobotController>& robot_controller);

    void processCommand(const std::string& command,
                        const std::shared_ptr<worm_picker_custom_msgs::srv::CalibrationCommand::Response>& response);

private:
    void moveToNextPoint();
    void retryCurrentPoint();
    void recordCurrentPosition();

    rclcpp::Node::SharedPtr node_;
    std::shared_ptr<RobotController> robot_controller_;
    State state_;
    size_t current_point_index_;
    std::vector<geometry_msgs::msg::PoseStamped> recorded_positions_;
};

#endif // CALIBRATION_STATE_MACHINE_HPP
