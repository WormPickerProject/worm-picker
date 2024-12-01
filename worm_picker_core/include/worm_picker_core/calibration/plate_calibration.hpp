// plate_calibration.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef PLATE_CALIBRATION_HPP
#define PLATE_CALIBRATION_HPP

#include <rclcpp/rclcpp.hpp>
#include <worm_picker_custom_msgs/srv/calibration_command.hpp>
#include "worm_picker_core/calibration/calibration_state_machine.hpp"
#include "worm_picker_core/calibration/robot_controller.hpp"

class PlateCalibration {
public:
    explicit PlateCalibration(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
    rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getNodeBase() const;

private:
    using CalibrationCommandService = worm_picker_custom_msgs::srv::CalibrationCommand;
    using CalibrationCommandRequest = CalibrationCommandService::Request;
    using CalibrationCommandResponse = CalibrationCommandService::Response;

    void setupServices();
    void handleUserInput(const std::shared_ptr<const CalibrationCommandRequest>& request,
                         const std::shared_ptr<CalibrationCommandResponse>& response);

    rclcpp::Node::SharedPtr node_;
    rclcpp::Service<CalibrationCommandService>::SharedPtr calibration_command_service_;
    std::shared_ptr<CalibrationStateMachine> state_machine_;
    std::shared_ptr<RobotController> robot_controller_;
};

#endif // PLATE_CALIBRATION_HPP
