// action_client_manager.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/system/management/action_client_manager.hpp"
#include "worm_picker_core/utils/parameter_utils.hpp"

ActionClientManager::ActionClientManager(const NodePtr& node)
    : node_{node},
      server_available_{false}
{
    initializeActionClient();
}

void ActionClientManager::initializeActionClient()
{
    const auto action_name = param_utils::getParameter<std::string>(node_, "actions.exec_task");

    action_client_ = rclcpp_action::create_client<ExecTaskSolutionAction>(node_, *action_name);
    if (!action_client_) {
        throw std::runtime_error("Failed to create action client for: " + *action_name);
    }

    wait_thread_ = std::jthread{[this] { waitForServer(); }};
}

void ActionClientManager::waitForServer() 
{
    using namespace std::chrono_literals;
    
    auto max_retries = param_utils::getParameter<int>(node_, "settings.max_retries");
    auto timeout_sec = param_utils::getParameter<int>(node_, "settings.server_timeout");
    const auto timeout = std::chrono::seconds{*timeout_sec};

    for (int retry_count = 0; rclcpp::ok() && retry_count < *max_retries; ++retry_count) {
        if (action_client_->wait_for_action_server(timeout)) {
            server_available_.store(true, std::memory_order_release);
            return;
        }
    }
}

bool ActionClientManager::isServerAvailable() const  
{
    return server_available_.load(std::memory_order_acquire);
}

const ActionClientManager::ActionClientPtr& ActionClientManager::getClient() const  
{
    if (!isServerAvailable()) {
        throw std::runtime_error("Attempting to get client before server is available");
    }
    return action_client_;
}
