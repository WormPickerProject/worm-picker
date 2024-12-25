// command_networking_main.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/infrastructure/interface/network/ros_command_client.hpp"

int main(int argc, char **argv) 
{
    auto client = std::make_shared<RosCommandClient>(argc, argv);

    std::jthread([client]() { client->connectToTaskCommandService(); });
    client->runSocketServer(12345);

    return 0;
}