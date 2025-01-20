// plate_calibration.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <moveit_task_constructor_msgs/action/execute_task_solution.hpp>
#include <worm_picker_custom_msgs/srv/calibration_command.hpp>
#include "worm_picker_core/system/calibration/calibration_state_machine.hpp"
#include "worm_picker_core/system/calibration/robot_controller.hpp"

class PlateCalibration {
public:
    explicit PlateCalibration(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
    rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getNodeBase() const;

private:
    using CalibrationCommandService = worm_picker_custom_msgs::srv::CalibrationCommand;
    using CalibrationCommandRequest = CalibrationCommandService::Request;
    using CalibrationCommandResponse = CalibrationCommandService::Response;
    using CalibrationCommandRequestPtr = std::shared_ptr<const CalibrationCommandRequest>;
    using CalibrationCommandResponsePtr = std::shared_ptr<CalibrationCommandResponse>;
    using ExecuteAction = moveit_task_constructor_msgs::action::ExecuteTaskSolution;

    static constexpr int MAX_SERVER_RETRIES = 10;
    static constexpr auto SERVER_TIMEOUT = std::chrono::seconds{3};

    void setupServices();
    void waitForServer();
    void handleUserInput(const CalibrationCommandRequestPtr& request,
                         const CalibrationCommandResponsePtr& response);

    rclcpp::Node::SharedPtr node_;
    rclcpp_action::Client<ExecuteAction>::SharedPtr action_client_;
    rclcpp::Service<CalibrationCommandService>::SharedPtr calibration_service_;
    std::shared_ptr<CalibrationStateMachine> state_machine_;
    std::shared_ptr<RobotController> robot_controller_;
    std::jthread server_wait_thread_;
};