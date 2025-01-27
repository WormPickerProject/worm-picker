// ros_command_client.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp> 
#include <worm_picker_custom_msgs/srv/task_command.hpp> 
#include <motoros2_interfaces/srv/start_traj_mode.hpp> 
#include <std_srvs/srv/trigger.hpp>
#include "worm_picker_core/infrastructure/interface/network/tcp_socket_server.hpp"

class RosCommandClient : public std::enable_shared_from_this<RosCommandClient> {
public:
    RosCommandClient(int argc, char **argv);
    void connectToTaskCommandService();
    void runSocketServer(int server_port);

private:
    using TaskCommand = worm_picker_custom_msgs::srv::TaskCommand;
    using StartTrajMode = motoros2_interfaces::srv::StartTrajMode;
    using Trigger = std_srvs::srv::Trigger;
    using StatusCallback = std::function<void(bool, std::string)>;

    void initializeCommandHandlers();
    void handleCommand(const std::string& command, StatusCallback completion_callback);
    void sendTaskCommandRequest(const std::shared_ptr<TaskCommand::Request>& request, 
                                StatusCallback completion_callback);

    rclcpp::Node::SharedPtr node_;
    rclcpp::Client<TaskCommand>::SharedPtr task_command_client_;
    rclcpp::Client<StartTrajMode>::SharedPtr start_traj_client_;
    rclcpp::Client<Trigger>::SharedPtr stop_traj_client_;
    std::unordered_map<std::string, std::function<void(StatusCallback)>> command_handlers_;
};