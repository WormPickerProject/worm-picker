// worm_picker_controller.hpp
//
// Copyright (c)
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
//
// Licensed under the Apache License, Version 2.0 (the "License");

#ifndef WORM_PICKER_CONTROLLER_HPP
#define WORM_PICKER_CONTROLLER_HPP

// ROS Core and Action includes
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

// ROS Service includes
#include <std_srvs/srv/trigger.hpp>
#include <worm_picker_custom_msgs/srv/task_command.hpp>

// MoveIt Task Constructor includes
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
#include <moveit_task_constructor_msgs/action/execute_task_solution.hpp>

// MoveIt Core and Planning includes
#include <moveit/robot_model/robot_model.h>
#include <moveit/planning_scene/planning_scene.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

// TF2 includes 
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2_eigen/tf2_eigen.hpp>

// WormPicker application includes
#include "worm_picker_core/tasks/task_data_structure.hpp"
#include "worm_picker_core/tasks/task_factory.hpp"
#include "worm_picker_core/tools/execution_timer.hpp"
#include "worm_picker_core/tools/timer_data_collector.hpp"
#include "worm_picker_core/exceptions/exceptions.hpp"

/**
 * @brief Class that manages the task creation, planning, and execution for the WormPicker project.
 */
class WormPickerController
{
public:
    /**
     * @brief Constructs the WormPickerController object.
     * @param options Node options passed to the ROS 2 node.
     */
    explicit WormPickerController(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());

    /**
     * @brief Retrieves the shared pointer to the node's base interface.
     * @return A shared pointer to the NodeBaseInterface.
     */
    rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getBaseInterface();
private:
    /**
     * @brief Sets up the ROS service and action client for task commands and execution.
     */
    void setupServicesAndActions();

    /**
     * @brief Continuously waits for the '/execute_task_solution' action server to become available.
     */
    void waitForActionServer();

    /**
     * @brief Handles incoming task commands from the ROS service.
     * @param request The incoming task command request.
     * @param response The response to be sent back indicating success or failure.
     */
    void handleTaskCommand(
        const std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Request> request,
        std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Response> response);

    /**
     * @brief Executes a task based on the provided command string.
     * @param command The task command as a string.
     */
    void doTask(const std::string& command);

    // Type aliases
    using ExecuteTaskSolutionAction = moveit_task_constructor_msgs::action::ExecuteTaskSolution;
    using ExecuteTaskSolutionClientPtr = rclcpp_action::Client<ExecuteTaskSolutionAction>::SharedPtr;
    using TaskCommandService = worm_picker_custom_msgs::srv::TaskCommand;
    using TaskCommandRequest = TaskCommandService::Request;
    using TaskCommandResponse = TaskCommandService::Response;

    rclcpp::Node::SharedPtr worm_picker_node_;                             // The ROS 2 node responsible for the WormPicker system.
    std::shared_ptr<TaskFactory> task_factory_;                            // Factory object for creating and managing tasks
    std::shared_ptr<TimerDataCollector> timer_data_collector_;             // Utility to collect and record task timing data
    ExecuteTaskSolutionClientPtr execute_task_action_client_;              // Action client for executing task solutions
    std::jthread execute_task_wait_thread_;                                // Thread responsible for waiting for the '/execute_task_solution' action server.
    rclcpp::Service<TaskCommandService>::SharedPtr task_command_service_;  // Service for handling task command requests
    moveit::task_constructor::Task current_task_;                          // The current task being processed
};

#endif  // WORM_PICKER_CONTROLLER_HPP