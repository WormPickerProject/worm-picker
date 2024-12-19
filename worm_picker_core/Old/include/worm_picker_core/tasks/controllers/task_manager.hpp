// task_manager.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

#include <rclcpp/rclcpp.hpp>
#include <moveit_msgs/msg/move_it_error_codes.hpp>

#include "worm_picker_core/tasks/task_factory.hpp"
#include "worm_picker_core/tools/timing/timer_data_collector.hpp"

/**
 * @class TaskManager
 * @brief Manages task execution and mode switching for the worm picker
 * 
 * @details
 * Coordinates task creation, planning, and execution while collecting timing data.
 * Handles mode switching between plate and worm handling operations.
 */
class TaskManager {
public:
    // Public Type Aliases
    using NodePtr = rclcpp::Node::SharedPtr;
    using TaskFactoryPtr = std::shared_ptr<TaskFactory>;
    using TimerDataCollectorPtr = std::shared_ptr<TimerDataCollector>;

    /**
     * @brief Status codes representing the result of task execution
     */
    enum class TaskExecutionStatus {
        Success,           ///< Task executed successfully
        PlanningFailed,    ///< Task planning phase failed
        ExecutionFailed    ///< Task execution phase failed
    };

    /**
     * @brief Constructs a TaskManager
     *
     * @param node ROS2 node handle
     * @param task_factory Factory for creating task instances
     * @param timer_data_collector Collector for timing data
     * @throws std::runtime_error if any pointer is null
     */
    TaskManager(const NodePtr& node,
                const TaskFactoryPtr& task_factory,
                const TimerDataCollectorPtr& timer_data_collector);

    /**
     * @brief Executes a task specified by the command
     *
     * @param command Task command to execute
     * @return TaskExecutionStatus indicating success or failure mode
     * @throws std::runtime_error if task creation or execution fails unexpectedly
     */
    TaskExecutionStatus executeTask(std::string_view command) const;

private:
    // Private Type Aliases
    using Task = moveit::task_constructor::Task;
    using MoveItErrorCodes = moveit_msgs::msg::MoveItErrorCodes;
    using ModeMap = std::unordered_map<std::string, std::string>;
    using TimerResults = std::vector<std::pair<std::string, double>>;

    /**
     * @brief Plans and executes the given task
     *
     * @param task Task to execute
     * @param command Original command for logging
     * @param timer_results Vector to store timing data
     * @return TaskExecutionStatus indicating success or failure
     */
    TaskExecutionStatus performTask(Task& task,
                                    std::string_view command,
                                    TimerResults& timer_results) const;
    
    /**
     * @brief Checks if the command is a mode switch operation
     *
     * @param command Command to check
     * @return Optional containing the new end effector if command is a mode switch
     */
    std::optional<std::string> isModeSwitch(std::string_view command) const;

    /**
     * @brief Checks the execution result and logs any errors
     *
     * @param result MoveIt error code from task execution
     * @param command Original command that was executed
     * @return TaskExecutionStatus based on the execution result
     */
    TaskExecutionStatus checkExecutionResult(const MoveItErrorCodes& result,
                                             std::string_view command) const;

    // ROS 2 Components
    NodePtr node_;                                  ///< ROS2 node handle

    // WormPicker Components
    TaskFactoryPtr task_factory_;                   ///< Task factory component
    TimerDataCollectorPtr timer_data_collector_;    ///< Timer data collection component

    // Mode Commands and End Effectors
    std::string plate_mode_command_;                ///< Command for plate mode switching
    std::string worm_mode_command_;                 ///< Command for worm mode switching
    std::string plate_end_effector_;                ///< End effector for plate handling
    std::string worm_end_effector_;                 ///< End effector for worm handling
    ModeMap mode_map_;                              ///< Mapping of mode commands to end effectors
};

#endif // TASK_MANAGER_HPP
