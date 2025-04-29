// ros_command_client.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/infrastructure/interface/network/ros_command_client.hpp"

RosCommandClient::RosCommandClient(int argc, char **argv)
  : strand_(io_ctx_.get_executor())
{
    rclcpp::init(argc, argv);
    node_ = rclcpp::Node::make_shared("ros_command_client");

    task_cli_  = node_->create_client<Task>   (TASK_SRV);
    start_cli_ = node_->create_client<StartTM>(START_SRV);

    initCmdTable();
}

RosCommandClient::~RosCommandClient()
{
    shutdownInternal();
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
}

void RosCommandClient::initCmdTable()
{
    cmd_tbl_["startWormPicker"] = [this](ReplyFn reply) {
        RCLCPP_INFO(node_->get_logger(), "Start command received.");

        using StartFuture = rclcpp::Client<StartTM>::SharedFuture;
        auto response = [self = shared_from_this(), reply](const StartFuture future) {
            using Ready = motoros2_interfaces::msg::MotionReadyEnum;
            bool success = (future.get()->result_code.value == Ready::READY);
            reply(success ? Reply::success("Robot started") : Reply::error("Robot not started"));
        };

        auto request  = std::make_shared<StartTM::Request>();
        start_cli_->async_send_request(request, std::move(response));
    };

    cmd_tbl_["quit"] = [this](ReplyFn reply) {
        RCLCPP_INFO(node_->get_logger(), "Quit command received.");
        reply(Reply::success("Shutting down..."));
        rclcpp::shutdown();
    };

    cmd_tbl_["q"] = cmd_tbl_["quit"];

    /* To be implemented in the future
        cmd_tbl_["stopWormPicker"] = [this](ReplyFn reply) { 
            RCLCPP_INFO(node_->get_logger(), "Stop command received.");
            // Logic to stop the robot
        };

        cmd_tbl_["launchWormPickerCore"] = [this](ReplyFn reply) { 
            RCLCPP_INFO(node_->get_logger(), "Launch robot application command received.");
            // Logic to launch the robot core application
        };
    */
}

void RosCommandClient::connectToTaskCommandService()
{
    rclcpp::Rate r(1.0);
    while (rclcpp::ok() && !task_cli_->wait_for_service(std::chrono::seconds{5}))
    {
        RCLCPP_WARN_THROTTLE(node_->get_logger(), *node_->get_clock(),
                             2000, "Waiting for %s ...", TASK_SRV);
        r.sleep();
    }
    RCLCPP_INFO(node_->get_logger(),"Connected to %s", TASK_SRV);
}

void RosCommandClient::runSocketServer(int port)
{
    work_guard_.emplace(boost::asio::make_work_guard(io_ctx_));
    server_ = std::make_unique<TcpSocketServer>(io_ctx_, port);

    std::weak_ptr<RosCommandClient> weak = shared_from_this();
    server_->setCommandHandler([weak, strand=strand_](std::string cmd, ReplyFn reply) {
        boost::asio::dispatch(strand, [weak, cmd=std::move(cmd), reply=std::move(reply)]() mutable {
            if(auto self = weak.lock()) {
                self->handleCmd(cmd,std::move(reply));
            } else {
                reply(Reply::error("ROS object destroyed"));
            }
        });
    });

    if (!server_->startServer()) {
        RCLCPP_ERROR(node_->get_logger(),"TCP server failed to start");
        return;
    }
    io_thread_ = std::jthread([this]{ io_ctx_.run(); });

    rclcpp::executors::MultiThreadedExecutor exec;
    exec.add_node(node_);
    exec.spin();

    shutdownInternal();
}

void RosCommandClient::handleCmd(const std::string& cmd, ReplyFn reply)
{
    if (auto it = cmd_tbl_.find(cmd); it != cmd_tbl_.end()){
        it->second(std::move(reply)); 
        return;
    }

    auto request = std::make_shared<Task::Request>();
    request->command = cmd;
    forwardTask(request, std::move(reply));
}

void RosCommandClient::forwardTask(std::shared_ptr<Task::Request> request, ReplyFn reply)
{
    RCLCPP_INFO(node_->get_logger(),"→ task_command: '%s'", request->command.c_str());

    using TaskFuture = rclcpp::Client<Task>::SharedFuture;
    auto response = [self = shared_from_this(), reply](const TaskFuture future) {
        auto response = future.get();
        reply(response->success ? 
            Reply::success(response->feedback) : 
            Reply::error(response->feedback));
    };

    task_cli_->async_send_request(request, std::move(response));
}

void RosCommandClient::shutdownInternal()
{
    if (server_) {
        server_->stopServer();
    }
    if (work_guard_) {
        work_guard_.reset();
    }
    io_ctx_.stop();
}