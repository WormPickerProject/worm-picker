// plate_calibration.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <filesystem>
#include "worm_picker_core/system/calibration/plate_calibration.hpp"

PlateCalibration::PlateCalibration(const rclcpp::NodeOptions& options) 
    : node_{std::make_shared<rclcpp::Node>("plate_calibration_node", options)} 
{
    node_->declare_parameter<std::string>("robot_group", "gp4_arm");
    node_->declare_parameter<std::string>("end_effectors.current_factor", "eoat_tcp");

    const auto robot_group = node_->get_parameter("robot_group").as_string();
    const auto end_effector_link = node_->get_parameter("end_effectors.current_factor").as_string();

    const auto current_path = std::filesystem::current_path().string();
    const auto config_path = "/worm-picker/worm_picker_core/config/initial_calibration_points.json";

    robot_controller_ = std::make_shared<RobotController>(
        node_, current_path + config_path, robot_group, end_effector_link);
    state_machine_ = std::make_shared<CalibrationStateMachine>(node_, robot_controller_);
    setupServices();
}

void PlateCalibration::setupServices() 
{
    action_client_ = rclcpp_action::create_client<ExecuteAction>(node_, "/execute_task_solution");
    server_wait_thread_ = std::jthread{[this] { waitForServer(); }};

    calibration_service_ = node_->create_service<CalibrationCommandService>(
        "/calibration_command",
        [this](const CalibrationCommandRequestPtr& request,
               const CalibrationCommandResponsePtr& response) {
            handleUserInput(request, response);
        }
    );
}

void PlateCalibration::waitForServer() 
{
    for (int retry_count = 0; rclcpp::ok() && retry_count < MAX_SERVER_RETRIES; ++retry_count) {
        if (action_client_->wait_for_action_server(SERVER_TIMEOUT)) {
            return;
        }
    }
}

void PlateCalibration::handleUserInput(const CalibrationCommandRequestPtr& request,
                                       const CalibrationCommandResponsePtr& response) 
{
    state_machine_->processCommand(request->command, response);

    if (state_machine_->getCurrentState() == CalibrationStateMachine::State::Completed) {
        const auto& recorded_positions = state_machine_->getRecordedPositions();

        RCLCPP_INFO(node_->get_logger(), "Calibration completed. Recorded positions:");
        for (const auto& [key, pose] : recorded_positions) {
            RCLCPP_INFO(node_->get_logger(), "Position '%s':", key.c_str());
            RCLCPP_INFO(node_->get_logger(), "  Position: [x: %f, y: %f, z: %f]",
                        pose.pose.position.x, pose.pose.position.y, pose.pose.position.z);
            RCLCPP_INFO(node_->get_logger(), "  Orientation: [x: %f, y: %f, z: %f, w: %f]",
                        pose.pose.orientation.x, pose.pose.orientation.y,
                        pose.pose.orientation.z, pose.pose.orientation.w);
        }
    }
}

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr PlateCalibration::getNodeBase() const 
{
    return node_->get_node_base_interface();
}