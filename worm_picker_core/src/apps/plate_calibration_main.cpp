// plate_calibration_main.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/system/nodes/plate_calibration.hpp"

// int main(int argc, char **argv) 
// {
//     rclcpp::init(argc, argv);
//     auto options = rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true);
//     auto plate_calibration = std::make_shared<PlateCalibration>(options);

//     rclcpp::executors::MultiThreadedExecutor executor;
//     executor.add_node(plate_calibration->getNodeBase());
//     executor.spin();
//     executor.remove_node(plate_calibration->getNodeBase());

//     rclcpp::shutdown();
//     return 0;
// }