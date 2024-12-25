// worm_picker_main.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/system/nodes/worm_picker_controller.hpp"

// int main(int argc, char **argv) 
// {
//     rclcpp::init(argc, argv);
//     auto options = rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true);
//     auto worm_picker_controller = std::make_shared<WormPickerController>(options);
    
//     rclcpp::executors::MultiThreadedExecutor executor;
//     executor.add_node(worm_picker_controller->getBaseInterface());
//     executor.spin();
//     executor.remove_node(worm_picker_controller->getBaseInterface());

//     rclcpp::shutdown();
//     return 0;
// }