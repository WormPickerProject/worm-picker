// core_command_interface_main.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/infrastructure/interface/cli/core_command_interface.hpp"

int main(int argc, char **argv) 
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("core_command_interface");

    auto command_interface = std::make_unique<CoreCommandInterface>(node);
    command_interface->runCommandLoop();
        
    rclcpp::shutdown();
    return 0;
}