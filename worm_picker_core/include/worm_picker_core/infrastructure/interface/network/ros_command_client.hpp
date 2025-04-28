// ros_command_client.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <boost/asio.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <motoros2_interfaces/srv/start_traj_mode.hpp>
#include <worm_picker_custom_msgs/srv/task_command.hpp>
#include "worm_picker_core/core/result.hpp"
#include "worm_picker_core/infrastructure/interface/network/tcp_socket_server.hpp"

class RosCommandClient : public std::enable_shared_from_this<RosCommandClient>
{
public:
    explicit RosCommandClient(int argc, char **argv);
    ~RosCommandClient();
    void connectToTaskCommandService();
    void runSocketServer(int port);

private:
    using Task              = worm_picker_custom_msgs::srv::TaskCommand;
    using StartTM           = motoros2_interfaces::srv::StartTrajMode;
    using Trigger           = std_srvs::srv::Trigger;
    using Reply             = Result<std::string>;
    using ReplyFn           = std::function<void(Reply)>;
    using CommandHandler    = std::function<void(ReplyFn)>;
    using CommandRegistry   = std::unordered_map<std::string, CommandHandler>;
    using IoExecutor        = boost::asio::io_context::executor_type;
    using IoStrand          = boost::asio::strand<IoExecutor>;
    using WorkGuard         = boost::asio::executor_work_guard<IoExecutor>;
    using OptionalWorkGuard = std::optional<WorkGuard>;

    static inline constexpr char const* k_task_srv  = "/task_command";
    static inline constexpr char const* k_start_srv = "/start_traj_mode";
    static inline constexpr char const* k_stop_srv  = "/stop_traj_mode";

    void initCmdTable();
    void handleCmd(const std::string& cmd, ReplyFn reply);
    void forwardTask(std::shared_ptr<Task::Request> req, ReplyFn reply);
    void shutdownInternal();

    rclcpp::Node::SharedPtr            node_;
    rclcpp::Client<Task>::SharedPtr    task_cli_;
    rclcpp::Client<StartTM>::SharedPtr start_cli_;
    rclcpp::Client<Trigger>::SharedPtr stop_cli_;
    CommandRegistry                    cmd_tbl_;
    boost::asio::io_context            io_ctx_;
    IoStrand                           strand_;
    OptionalWorkGuard                  work_guard_;
    std::unique_ptr<TcpSocketServer>   server_;
    std::jthread                       io_thread_;
};