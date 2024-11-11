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
* @brief Controller for managing automated worm picking tasks using ROS 2 services and actions.
* 
* @details
* The WormPickerController class integrates with MoveIt Task Constructor to plan and execute
* complex motion sequences required for precise worm manipulation. It uses ROS 2 actions and
* services to handle task commands and coordinate execution while maintaining timing data and
* managing task-related parameters.
*/
class WormPickerController {
public:
    /**
     * @brief Status codes representing the result of task execution
     */
    enum class TaskExecutionStatus {
        Success,        /// Task executed successfully
        PlanningFailed, /// Task planning phase failed
        ExecutionFailed /// Task execution phase failed
    };

    /**
     * @brief Constructs a new WormPickerController
     * 
     * Initializes the controller, setting up ROS 2 services, actions, and parameters for worm 
     * picking tasks.
     * 
     * @param options Node options for ROS 2, allowing customization of node parameters
     */
    explicit WormPickerController(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
 
    /**
     * @brief Virtual destructor
     */
    virtual ~WormPickerController() = default;
 
    /**
     * @brief Retrieves the base interface of the ROS 2 node
     * 
     * Provides access to the core node interface required for communication and ROS 2 integration.
     * 
     * @return Shared pointer to the node base interface
     */
    rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getBaseInterface();

private:
    // Private Type Aliases
    using ExecTaskSolutionAction = moveit_task_constructor_msgs::action::ExecuteTaskSolution;
    using TaskClientPtr = rclcpp_action::Client<ExecTaskSolutionAction>::SharedPtr;
    using TaskCommandService = worm_picker_custom_msgs::srv::TaskCommand;
    using TaskCommandRequest = TaskCommandService::Request;
    using TaskCommandResponse = TaskCommandService::Response;
    using TaskServicePtr = rclcpp::Service<TaskCommandService>::SharedPtr;
    using NodePtr = rclcpp::Node::SharedPtr;

    // Constants
    /// Base path for storing timer log data
    static constexpr std::string_view TIMER_LOG_PATH = 
        "/worm-picker/worm_picker_description/program_data/timer_log";

    /// Base path for configuration files
    static constexpr std::string_view CONFIG_PATH = 
        "/worm-picker/worm_picker_description/program_data/data_files";

    /// Name of the ROS 2 node for WormPickerController
    static constexpr std::string_view NODE_NAME = "worm_picker_controller";

    /// Action name for executing task solutions
    static constexpr std::string_view EXECUTE_TASK_ACTION_NAME = "/execute_task_solution";

    /// Service name for handling task commands
    static constexpr std::string_view TASK_COMMAND_SERVICE_NAME = "/task_command";

   // End Effector Modes
   /// Command to switch to plate handling mode
   static constexpr std::string_view PLATE_MODE_COMMAND = "plateMode";

   /// Command to switch to worm handling mode
   static constexpr std::string_view WORM_MODE_COMMAND = "wormMode";

   /// End effector frame for plate handling operations
   static constexpr std::string_view EOAT_TCP = "eoat_tcp";

   /// End effector frame for worm handling operations
   static constexpr std::string_view WORMPICKER_TCP = "wormpicker_tcp";

    // Core Methods
    /**
     * @brief Declares parameters required by the WormPickerController
     * 
     * Sets up default parameters for controlling task retries, timeouts, and planning attempts
     */
    void declareParameters();
 
    /**
     * @brief Initializes ROS 2 services and action clients
     * 
     * Configures the service for task command handling and sets up the action client
     * to communicate with the task execution server
     */
    void setupServicesAndActions();
 
    /**
     * @brief Waits for the task execution action server to become available
     * 
     * Continuously checks the availability of the action server, retrying based on
     * the configured timeout and retry parameters
     */
    void waitForActionServer();
 
    // Task Processing Methods
    /**
     * @brief Processes incoming task commands received via ROS 2 service interface
     * 
     * @param request Task command request containing the command to execute
     * @param response Task command response indicating the success of the task execution
     */
    void handleTaskCommand(std::shared_ptr<const TaskCommandRequest> request,
                          std::shared_ptr<TaskCommandResponse> response);
 
    /**
     * @brief Executes a task based on a command string
     * 
     * @param command Task command string specifying the task to execute
     * @return TaskExecutionStatus indicating execution outcome
     */
    TaskExecutionStatus doTask(std::string_view command);
 
    /**
     * @brief Checks if the given command is a mode switching command
     * 
     * @param command The task command to check
     * @return The corresponding end effector if command is a mode switch, std::nullopt otherwise
     */
    std::optional<std::string_view> isModeSwitch(std::string_view command);
 
    /**
     * @brief Evaluates the result of task execution
     * 
     * @param result MoveIt error codes representing the outcome of the task
     * @param command Task command string associated with the execution
     * @return TaskExecutionStatus indicating whether the execution succeeded or failed
     */
    TaskExecutionStatus checkExecutionResult(const moveit_msgs::msg::MoveItErrorCodes& result,
                                             std::string_view command);
 
    // ROS 2 Communication Members
    NodePtr worm_picker_node_;                 ///< Main ROS 2 node for managing the WormPicker system
    TaskClientPtr execution_action_client_;    ///< Action client for task execution
    TaskServicePtr task_service_;              ///< Service for handling task commands
 
    // Task Management Members
    std::shared_ptr<TaskFactory> task_factory_;      ///< Factory for creating tasks
    moveit::task_constructor::Task current_task_;    ///< Currently active task
 
    // Utility Members
    std::shared_ptr<TimerDataCollector> timer_data_collector_;    ///< Collector for timing data
 
    // Threading & State Members
    std::jthread wait_thread_;                 ///< Thread for action server monitoring
    std::atomic<bool> server_ready_{false};    ///< Action server availability flag
};

#endif  // WORM_PICKER_CONTROLLER_HPP