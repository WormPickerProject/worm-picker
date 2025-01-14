// cal_command_interface_main.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/infrastructure/interface/cli/cal_command_interface.hpp"

int main(int argc, char **argv) 
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("cal_command_interface");

    auto command_interface = std::make_unique<CalCommandInterface>(node);
    command_interface->runCommandLoop();
        
    rclcpp::shutdown();
    return 0;
}