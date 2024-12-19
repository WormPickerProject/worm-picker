// action_client_manager.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tasks/controllers/action_client_manager.hpp"

ActionClientManager::ActionClientManager(const NodePtr& node)
    : node_{node},
      server_available_{false}
{
    initializeActionClient();
}

void ActionClientManager::initializeActionClient()
{
    const auto action_name = node_->get_parameter("exec_task_action_name").as_string();

    action_client_ = rclcpp_action::create_client<ExecTaskSolutionAction>(node_, action_name);
    
    if (!action_client_) {
        throw std::runtime_error("Failed to create action client for: " + action_name);
    }

    wait_thread_ = Thread{[this] { waitForServer(); }};
}

bool ActionClientManager::isServerAvailable() const noexcept 
{
    return server_available_.load(std::memory_order_acquire);
}

const ActionClientManager::ActionClientPtr& ActionClientManager::getClient() const noexcept 
{
    return action_client_;
}

void ActionClientManager::waitForServer() 
{
    using namespace std::chrono_literals;
    
    const auto max_retries = node_->get_parameter("max_retries").as_int();
    const auto timeout = std::chrono::seconds{
        node_->get_parameter("action_server_timeout_sec").as_int()
    };

    for (int retry_count = 0; rclcpp::ok() && retry_count < max_retries; ++retry_count) {
        if (action_client_->wait_for_action_server(timeout)) {
            server_available_.store(true, std::memory_order_release);
            return;
        }
    }

}
