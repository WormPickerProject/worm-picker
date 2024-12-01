// plate_calibration.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/calibration/plate_calibration.hpp"
#include <ament_index_cpp/get_package_share_directory.hpp>

PlateCalibration::PlateCalibration(const rclcpp::NodeOptions& options)
    : node_{std::make_shared<rclcpp::Node>("plate_calibration_node", options)} {
    std::string calibration_file_path = node_->declare_parameter<std::string>("calibration_file_path", "");
    if (calibration_file_path.empty()) {
        std::string package_share_directory = ament_index_cpp::get_package_share_directory("worm_picker_core");
        calibration_file_path = package_share_directory + "/config/initial_calibration_points.json";
    }

    robot_controller_ = std::make_shared<RobotController>(node_, calibration_file_path);
    state_machine_ = std::make_shared<CalibrationStateMachine>(node_, robot_controller_);
    setupServices();
}

void PlateCalibration::setupServices()
{
    calibration_command_service_ = node_->create_service<CalibrationCommandService>(
        "/calibration_command",
        [this](const std::shared_ptr<const CalibrationCommandRequest>& request,
               const std::shared_ptr<CalibrationCommandResponse>& response) {
            handleUserInput(request, response);
        }
    );
}

void PlateCalibration::handleUserInput(const std::shared_ptr<const CalibrationCommandRequest>& request,
                                       const std::shared_ptr<CalibrationCommandResponse>& response)
{
    state_machine_->processCommand(request->command, response);
}

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr PlateCalibration::getNodeBase() const
{
    return node_->get_node_base_interface();
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto plate_calibration = std::make_shared<PlateCalibration>(
        rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));

    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(plate_calibration->getNodeBase());

    executor.spin();

    executor.remove_node(plate_calibration->getNodeBase());
    rclcpp::shutdown();

    return 0;
}
