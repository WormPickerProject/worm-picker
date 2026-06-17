// command_networking_main.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <string>

#include "worm_picker_core/infrastructure/interface/network/ros_command_client.hpp"

int main(int argc, char **argv) 
{
    // Snapshot positional args before rclcpp::init may rewrite argv.
    const std::string device = (argc > 1) ? argv[1] : "/dev/ttyUSB0";
    const unsigned    baud   = (argc > 2)
                                   ? static_cast<unsigned>(std::stoul(argv[2]))
                                   : 115200u;

    auto client = std::make_shared<RosCommandClient>(argc, argv);

    std::jthread([client]() { client->connectToTaskCommandService(); });
    client->runSerialServer(device, baud);

    return 0;
}