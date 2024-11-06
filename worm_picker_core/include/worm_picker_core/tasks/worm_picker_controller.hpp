// worm_picker_controller.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef WORM_PICKER_CONTROLLER_HPP
#define WORM_PICKER_CONTROLLER_HPP

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

#include <std_srvs/srv/trigger.hpp>
#include <worm_picker_custom_msgs/srv/task_command.hpp>

#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
#include <moveit_task_constructor_msgs/action/execute_task_solution.hpp>

#include <moveit/robot_model/robot_model.h>
#include <moveit/planning_scene/planning_scene.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2_eigen/tf2_eigen.hpp>

#include "worm_picker_core/tasks/task_factory.hpp"
#include "worm_picker_core/tools/timing/execution_timer.hpp"
#include "worm_picker_core/tools/timing/timer_data_collector.hpp"
#include "worm_picker_core/exceptions/exceptions.hpp"

/**
 * @class WormPickerController
 * @brief Enhanced controller for managing automated worm picking tasks using ROS 2 services and
 *        actions.
 * 
 * @details
 * The WormPickerController class integrates with MoveIt Task Constructor to plan and execute
 * complex motion sequences required for precise worm manipulation. It uses ROS 2 actions and
 * services to handle task commands and coordinate execution while maintaining timing data and
 * managing task-related parameters.
 */
class WormPickerController
{
public:
    /**
     * @brief Status codes representing the result of task execution.
     */
    enum class TaskExecutionStatus {
        /// Task executed successfully.
        Success,
        /// Task planning phase failed.
        PlanningFailed,
        /// Task execution phase failed.
        ExecutionFailed
    };

    /**
     * @brief Constructs a new WormPickerController.
     * 
     * Initializes the controller, setting up ROS 2 services, actions, and parameters for worm 
     * picking tasks.
     * 
     * @param options Node options for ROS 2, allowing customization of node parameters.
     */
    explicit WormPickerController(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());

    /**
     * @brief Retrieves the base interface of the ROS 2 node.
     * 
     * Provides access to the core node interface required for communication and ROS 2 integration.
     * 
     * @return Shared pointer to the node base interface.
     */
    rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getBaseInterface();

private:
    /// ROS 2 node name for WormPickerController.
    static constexpr const char* NODE_NAME = "worm_picker_controller";

    /// Path for storing timer log data.
    static constexpr const char* TIMER_LOG_PATH = "/worm-picker/worm_picker_description/program_data/timer_log";

    /// Name of the action used to execute task solutions.
    static constexpr const char* EXECUTE_TASK_ACTION_NAME = "/execute_task_solution";

    /// Name of the service for handling task commands.
    static constexpr const char* TASK_COMMAND_SERVICE_NAME = "/task_command";

    /// Alias for the action type used in executing task solutions.
    using ExecTaskSolutionAction = moveit_task_constructor_msgs::action::ExecuteTaskSolution;

    /// Shared pointer type for the action client.
    using ExecTaskSolutionClientPtr = rclcpp_action::Client<ExecTaskSolutionAction>::SharedPtr;

    /// Alias for the service type handling task commands.
    using TaskCommandService = worm_picker_custom_msgs::srv::TaskCommand;

    /// Type for task command requests.
    using TaskCommandRequest = TaskCommandService::Request;

    /// Type for task command responses.
    using TaskCommandResponse = TaskCommandService::Response;

    /**
     * @brief Declares parameters required by the WormPickerController.
     * 
     * Sets up default parameters for controlling task retries, timeouts, and planning attempts.
     */
    void declareParameters();

    /**
     * @brief Initializes ROS 2 services and action clients.
     * 
     * Configures the service for task command handling and sets up the action client
     * to communicate with the task execution server.
     */
    void setupServicesAndActions();

    /**
     * @brief Waits for the task execution action server to become available.
     * 
     * Continuously checks the availability of the action server, retrying based on
     * the configured timeout and retry parameters.
     */
    void waitForActionServer();

    /**
     * @brief Processes incoming task commands received via ROS 2 service interface.
     * 
     * Executes a specified task based on the command received, reporting success or failure.
     * 
     * @param request Task command request containing the command to execute.
     * @param response Task command response indicating the success of the task execution.
     */
    void handleTaskCommand(std::shared_ptr<const TaskCommandRequest> request,
                          std::shared_ptr<TaskCommandResponse> response);

    /**
     * @brief Executes a task based on a command string.
     * 
     * Manages the creation, planning, and execution stages for the specified command, recording 
     * timing data.
     * 
     * @param command Task command string specifying the task to execute.
     * @return TaskExecutionStatus indicating whether the task succeeded, failed in planning, or 
     *         failed in execution.
     */
    TaskExecutionStatus doTask(std::string_view command);

    /**
     * @brief Evaluates the result of task execution.
     * 
     * Checks the result code of the executed task and logs any failure reasons.
     * 
     * @param result MoveIt error codes representing the outcome of the task.
     * @param command Task command string associated with the execution.
     * @return TaskExecutionStatus indicating whether the execution succeeded or failed.
     */
    TaskExecutionStatus checkExecutionResult(
        const moveit_msgs::msg::MoveItErrorCodes& result,
        std::string_view command);

    /// Shared pointer to the main ROS 2 node for managing the WormPicker system.
    rclcpp::Node::SharedPtr worm_picker_node_;

    /// Factory for creating and managing tasks based on commands.
    std::shared_ptr<TaskFactory> task_factory_;

    /// Collector for timing data related to task execution.
    std::shared_ptr<TimerDataCollector> timer_data_collector_;

    /// Action client for communicating with the task execution server.
    ExecTaskSolutionClientPtr execute_task_action_client_;

    /// Service for handling task command requests via ROS 2.
    rclcpp::Service<TaskCommandService>::SharedPtr task_command_service_;

    /// The currently active task being processed.
    moveit::task_constructor::Task current_task_;

    /// Thread for continuously monitoring the action server's availability.
    std::jthread execute_task_wait_thread_;

    /// Flag indicating whether the action server is available.
    std::atomic<bool> server_ready_{false};
};

#endif  // WORM_PICKER_CONTROLLER_HPP