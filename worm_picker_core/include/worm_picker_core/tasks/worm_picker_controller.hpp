// worm_picker_controller.hpp
//
// Copyright (c) 2024
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
#include "worm_picker_core/tasks/task_factory.hpp"
#include "worm_picker_core/tools/timing/execution_timer.hpp"
#include "worm_picker_core/tools/timing/timer_data_collector.hpp"
#include "worm_picker_core/exceptions/exceptions.hpp"

/**
 * @class WormPickerController
 * @brief Manages the worm picking tasks using ROS 2 services and actions.
 * 
 * The WormPickerController class is responsible for initializing the ROS node,
 * setting up services and actions, and handling task commands for the worm
 * picking system. It uses the TaskFactory class to create the tasks, and the 
 * MoveIt Task Constructor to plan and execute tasks based on predefined commands.
 * 
 * @note This class requires ROS 2 and MoveIt Task Constructor to be properly set up.
 * 
 * @par Example Usage:
 * @code
 * rclcpp::NodeOptions options;
 * auto controller = std::make_shared<WormPickerController>(options);
 * controller->getBaseInterface();
 * @endcode
 * 
 * @par Dependencies:
 * - ROS 2
 * - MoveIt Task Constructor
 * - Custom messages and services defined in worm_picker_custom_msgs
 */
class WormPickerController
{
public:
    /**
     * @brief Constructs the WormPickerController object.
     * 
     * Initializes the ROS node, task factory, and timer data collector.
     * Sets up services and actions for task commands and task execution.
     * 
     * @param options Node options passed to the ROS 2 node (optional).
     * 
     * @details This constructor initializes the core components required for the
     * WormPickerController to function. It creates a ROS node with the provided
     * options, initializes the TaskFactory for creating tasks, and sets up the
     * TimerDataCollector for recording execution times. Additionally, it sets up
     * the necessary ROS services and action clients to handle task commands and
     * execute tasks.
     */
    explicit WormPickerController(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());

    /**
     * @brief Retrieves the base interface of the node.
     * 
     * Provides access to the core interfaces of the node, including 
     * communication interfaces.
     * 
     * @return A shared pointer to the NodeBaseInterface.
     */
    rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getBaseInterface();
private:
    /**
     * @brief Initializes ROS services and action clients for task commands and execution.
     * 
     * Sets up the task command service and action client to interact with
     * the '/execute_task_solution' action server.
     */
    void setupServicesAndActions();

    /**
     * @brief Waits for the '/execute_task_solution' action server to become available.
     * 
     * Polls the action server and retries a limited number of times if the
     * server is not available.
     */
    void waitForActionServer();

    /**
     * @brief Handles incoming task commands through the ROS service interface.
     * 
     * Processes requests to create, plan, and execute tasks based on the 
     * command string received in the request. Responds with success or failure.
     * 
     * @param request Incoming task command request.
     * @param response Response to the service request indicating success or failure.
     * @throws ActionServerUnavailableException If the action server is unavailable during the command.
     * @throws TaskPlanningFailedException If task planning fails.
     * @throws TaskExecutionFailedException If task execution fails.
     */
    void handleTaskCommand(const std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Request> request,
                           std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Response> response);

    /**
     * @brief Executes a task based on the provided command string.
     * 
     * Creates, initializes, plans, and executes the task. Collects timing data
     * for the task execution process and throws exceptions for failures during
     * planning or execution stages.
     * 
     * @param command The task command to be processed.
     * @throws TaskPlanningFailedException If task planning fails.
     * @throws TaskExecutionFailedException If task execution fails.
     */
    void doTask(const std::string& command);

    // Type aliases
    using ExecuteTaskSolutionAction = moveit_task_constructor_msgs::action::ExecuteTaskSolution;
    using ExecuteTaskSolutionClientPtr = rclcpp_action::Client<ExecuteTaskSolutionAction>::SharedPtr;
    using TaskCommandService = worm_picker_custom_msgs::srv::TaskCommand;
    using TaskCommandRequest = TaskCommandService::Request;
    using TaskCommandResponse = TaskCommandService::Response;

    rclcpp::Node::SharedPtr worm_picker_node_;                             ///< ROS 2 node responsible for the WormPicker system.
    std::shared_ptr<TaskFactory> task_factory_;                            ///< Factory object for creating and managing tasks.
    std::shared_ptr<TimerDataCollector> timer_data_collector_;             ///< Utility for collecting and recording task timing data.
    ExecuteTaskSolutionClientPtr execute_task_action_client_;              ///< Action client for executing task solutions.
    std::jthread execute_task_wait_thread_;                                ///< Thread for waiting for the '/execute_task_solution' action server.
    rclcpp::Service<TaskCommandService>::SharedPtr task_command_service_;  ///< Service for handling task command requests.
    moveit::task_constructor::Task current_task_;                          ///< The current task being processed.
};

#endif  // WORM_PICKER_CONTROLLER_HPP