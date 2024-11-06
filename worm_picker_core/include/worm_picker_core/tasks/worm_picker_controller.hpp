// worm_picker_controller.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

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
 * @brief Enhanced controller for worm picking tasks using ROS 2 services and actions.
 * 
 * @details
 * The WormPickerController class manages automated worm picking operations through ROS 2
 * services and actions. It integrates with MoveIt Task Constructor to plan and execute
 * complex motion sequences for precise worm manipulation.
 */
class WormPickerController
{
public:
    /** 
     * @brief Status codes for task execution
     */
    enum class TaskExecutionStatus {
        Success,
        PlanningFailed,
        ExecutionFailed
    };

    /**
     * @brief Construct a new WormPicker Controller
     * @param options Node options for ROS 2
     */
    explicit WormPickerController(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());

    /**
     * @brief Get the Base Interface of the node
     * @return Node base interface shared pointer
     */
    [[nodiscard]] rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getBaseInterface();

private:
    static constexpr const char* NODE_NAME = "worm_picker_controller";
    static constexpr const char* TIMER_LOG_PATH = "/worm-picker/worm_picker_description/program_data/timer_log";
    static constexpr const char* EXECUTE_TASK_ACTION_NAME = "/execute_task_solution";
    static constexpr const char* TASK_COMMAND_SERVICE_NAME = "/task_command";

    using ExecuteTaskSolutionAction = moveit_task_constructor_msgs::action::ExecuteTaskSolution;
    using ExecuteTaskSolutionClientPtr = rclcpp_action::Client<ExecuteTaskSolutionAction>::SharedPtr;
    using TaskCommandService = worm_picker_custom_msgs::srv::TaskCommand;
    using TaskCommandRequest = TaskCommandService::Request;
    using TaskCommandResponse = TaskCommandService::Response;

    /**
     * @brief Initialize ROS 2 parameters
     */
    void declareParameters();

    /**
     * @brief Setup services and actions
     */
    void setupServicesAndActions();

    /**
     * @brief Wait for action server to become available
     */
    void waitForActionServer();

    /**
     * @brief Handle incoming task commands
     * @param request Task command request
     * @param response Task command response
     */
    void handleTaskCommand(std::shared_ptr<const TaskCommandRequest> request,
                          std::shared_ptr<TaskCommandResponse> response);

    /**
     * @brief Execute a task
     * @param command Task command string
     * @return Task execution status
     */
    [[nodiscard]] TaskExecutionStatus doTask(std::string_view command);

    /**
     * @brief Check execution result
     * @param result MoveIt error codes
     * @param command Task command string
     * @return Task execution status
     */
    [[nodiscard]] TaskExecutionStatus checkExecutionResult(
        const moveit_msgs::msg::MoveItErrorCodes& result,
        std::string_view command);

    // Node and components
    rclcpp::Node::SharedPtr worm_picker_node_;
    std::shared_ptr<TaskFactory> task_factory_;
    std::shared_ptr<TimerDataCollector> timer_data_collector_;
    
    // Action clients and services
    ExecuteTaskSolutionClientPtr execute_task_action_client_;
    rclcpp::Service<TaskCommandService>::SharedPtr task_command_service_;
    
    // Task management
    moveit::task_constructor::Task current_task_;
    std::jthread execute_task_wait_thread_;
    std::atomic<bool> server_ready_{false};
};

#endif  // WORM_PICKER_CONTROLLER_HPP