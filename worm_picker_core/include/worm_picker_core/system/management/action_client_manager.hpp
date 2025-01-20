// action_client_manager.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <moveit_task_constructor_msgs/action/execute_task_solution.hpp>

class ActionClientManager {
public:
    using NodePtr = rclcpp::Node::SharedPtr;
    using ExecTaskSolutionAction = moveit_task_constructor_msgs::action::ExecuteTaskSolution;
    using ActionClientPtr = rclcpp_action::Client<ExecTaskSolutionAction>::SharedPtr;

    explicit ActionClientManager(const NodePtr& node);
    bool isServerAvailable() const;
    const ActionClientPtr& getClient() const;

private:
    using AtomicBool = std::atomic<bool>;

    void initializeActionClient();
    void waitForServer();

    NodePtr node_;
    ActionClientPtr action_client_;
    std::jthread wait_thread_;
    AtomicBool server_available_;
};