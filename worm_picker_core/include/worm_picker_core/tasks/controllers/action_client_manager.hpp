// action_client_manager.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef ACTION_CLIENT_MANAGER_HPP
#define ACTION_CLIENT_MANAGER_HPP

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <moveit_task_constructor_msgs/action/execute_task_solution.hpp>

/**
 * @class ActionClientManager
 * @brief Manages an action client for executing task solutions
 * 
 * @details
 * Provides a wrapper around ROS2 action client functionality with automatic
 * server discovery and connection management.
 */
class ActionClientManager {
public:
    // Public Type Aliases
    using NodePtr = rclcpp::Node::SharedPtr;
    using ExecTaskSolutionAction = moveit_task_constructor_msgs::action::ExecuteTaskSolution;
    using ActionClientPtr = rclcpp_action::Client<ExecTaskSolutionAction>::SharedPtr;

    /**
     * @brief Constructs an ActionClientManager
     * 
     * @param node ROS2 node to use for creating the action client
     */
    explicit ActionClientManager(const NodePtr& node);

    /**
     * @brief Checks if the action server is available
     * 
     * @return true if server is available, false otherwise
     */
    bool isServerAvailable() const noexcept;

    /**
     * @brief Gets the underlying action client
     * 
     * @return Shared pointer to the action client
     */
    const ActionClientPtr& getClient() const noexcept;

private:
    // Private Type Aliases
    using Thread = std::jthread;
    using AtomicBool = std::atomic<bool>;

    /**
     * @brief ...
     * 
     * ...
     */
    void initializeActionClient();

    /**
     * @brief Waits for the action server to become available
     * 
     * Runs in a separate thread and attempts to connect to the server
     * up to max_retries times with a configurable timeout.
     */
    void waitForServer();

    // ROS 2 Components
    NodePtr node_;                     ///< ROS2 node handle
    ActionClientPtr action_client_;    ///< Action client instance

    // Threading Components
    Thread wait_thread_;               ///< Thread for server discovery
    AtomicBool server_available_;      ///< Server availability flag
};

#endif // ACTION_CLIENT_MANAGER_HPP
