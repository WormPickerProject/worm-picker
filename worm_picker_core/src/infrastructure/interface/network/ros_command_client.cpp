// ros_command_client.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/infrastructure/interface/network/ros_command_client.hpp"

RosCommandClient::RosCommandClient(int argc, char **argv) 
{
    rclcpp::init(argc, argv);
    node_ = rclcpp::Node::make_shared("ros_command_client");

    task_command_client_ = node_->create_client<TaskCommand>("/task_command");
    start_traj_client_ = node_->create_client<StartTrajMode>("/start_traj_mode");
    stop_traj_client_ = node_->create_client<Trigger>("/stop_traj_mode");

    initializeCommandHandlers();
}

void RosCommandClient::initializeCommandHandlers() 
{
    command_handlers_["startWormPicker"] = [this](StatusCallback completion_callback) { 
        RCLCPP_INFO(node_->get_logger(), "Start command received.");

        auto request = std::make_shared<StartTrajMode::Request>();
        auto self = shared_from_this();
        
        using ReadyEnum = motoros2_interfaces::msg::MotionReadyEnum;
        auto response_handler = [self, completion_callback](
            const rclcpp::Client<StartTrajMode>::SharedFuture future) {
                auto response = future.get();
                bool success = (response->result_code.value == ReadyEnum::READY);
                completion_callback(success);
        };

        start_traj_client_->async_send_request(request, std::move(response_handler));
    };

    command_handlers_["quit"] = [this](StatusCallback completion_callback) { 
        RCLCPP_INFO(node_->get_logger(), "Quit command received.");
        rclcpp::shutdown();
        completion_callback(true);
    };
    
    /* To be implemented in the future
        command_handlers_["stopWormPicker"] = [this](StatusCallback completion_callback) { 
            RCLCPP_INFO(node_->get_logger(), "Stop command received.");
            // Logic to stop the robot
        };

        command_handlers_["launchWormPickerCore"] = [this](StatusCallback completion_callback) { 
            RCLCPP_INFO(node_->get_logger(), "Launch robot application command received.");
            // Logic to launch the robot core application
        };
    */
}

void RosCommandClient::connectToTaskCommandService() 
{
    while (rclcpp::ok() && !task_command_client_->wait_for_service(std::chrono::seconds(5))) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    RCLCPP_INFO(node_->get_logger(), "Connected to task command service.");
}

void RosCommandClient::runSocketServer(int server_port) 
{
    auto server = std::make_unique<TcpSocketServer>(server_port);
    auto weak_self = weak_from_this();

    server->setCommandHandler(
        [weak_self](const std::string& command, StatusCallback completion_callback) {
            if (auto self = weak_self.lock()) {
                self->handleCommand(command, completion_callback);
            } else {
                completion_callback(false);
            }
        }
    );

    RCLCPP_INFO(node_->get_logger(), "Starting server.");
    server->startServer();

    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node_);
    executor.spin();

    RCLCPP_INFO(node_->get_logger(), "Stopping server.");
    server->stopServer();
}

void RosCommandClient::handleCommand(const std::string& command, 
                                     StatusCallback completion_callback) 
{
    if (auto it = command_handlers_.find(command); it != command_handlers_.end()) {
        it->second(completion_callback);
        return;
    }

    auto request = std::make_shared<TaskCommand::Request>();
    request->command = command;
    sendTaskCommandRequest(request, completion_callback);
}

void RosCommandClient::sendTaskCommandRequest(const std::shared_ptr<TaskCommand::Request>& request, 
                                              StatusCallback completion_callback) 
{
    RCLCPP_INFO(node_->get_logger(), "Task command received: '%s'", request->command.c_str());

    auto response_handler = [self = shared_from_this(), completion_callback](
        const rclcpp::Client<TaskCommand>::SharedFuture future) {
            auto response = future.get();
            completion_callback(response->success);
    };

    task_command_client_->async_send_request(request, std::move(response_handler));
}

int main(int argc, char **argv) 
{
    auto client = std::make_shared<RosCommandClient>(argc, argv);

    std::jthread([client]() { client->connectToTaskCommandService(); });
    client->runSocketServer(12345);

    return 0;
}
