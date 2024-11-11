// task_factory.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef TASK_FACTORY_HPP
#define TASK_FACTORY_HPP

#include <fmt/format.h>

#include <rclcpp/rclcpp.hpp>
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/stages.h>

#include "worm_picker_core/tools/parsers/workstation_data_parser.hpp"
#include "worm_picker_core/tools/parsers/hotel_data_parser.hpp"
#include "worm_picker_core/exceptions/exceptions.hpp"

#include "worm_picker_core/tasks/task_data.hpp"
#include "worm_picker_core/stages/move_relative_data.hpp"
#include "worm_picker_core/stages/move_to_joint_data.hpp"
#include "worm_picker_core/stages/move_to_point_data.hpp"

/** 
* @brief Factory class responsible for creating MoveIt tasks based on predefined commands.
* 
* The TaskFactory class uses a ROS 2 node to generate tasks that can be executed
* by the MoveIt framework. Tasks are created based on commands, each with specific
* configurations and planning requirements for robotic manipulation.
*/
class TaskFactory {
public:
   // Type Aliases
   using Task = moveit::task_constructor::Task;
   using Node = rclcpp::Node;
   using NodePtr = Node::SharedPtr;

    /** 
     * @brief Constructs a TaskFactory with the specified ROS 2 node
     * 
     * @param node Shared pointer to the ROS 2 node used for parameter and service access
     * @throws TaskFactoryError if the provided node is null
     */
    explicit TaskFactory(const NodePtr& node);
 
    /**
     * @brief Default virtual destructor
     */
    virtual ~TaskFactory() = default;
 
    /**
     * @brief Generates a MoveIt task based on the specified command
     * 
     * Creates a task tailored to the given command, with each command corresponding
     * to a predefined task configuration.
     * 
     * @param command The name of the command used to identify and configure the task
     * @return Task The constructed MoveIt task ready for planning and execution
     * @throws TaskFactoryError if task creation fails
     */
    Task createTask(std::string_view command);

private:
    // Private Type Aliases
    using CurrentStateStage = moveit::task_constructor::stages::CurrentState;
    using TrajectoryExecutionInfo = moveit::task_constructor::TrajectoryExecutionInfo;
    using TaskDataMap = std::map<std::string, TaskData>;

    /**
     * @brief Initializes and populates the task map with predefined stages and tasks
     * 
     * @throws TaskFactoryError if initialization fails
     */
    void initializeTaskMap();
 
    /**
     * @brief Creates a base task with the specified command name
     * 
     * @param command The command name to assign to the task
     * @return Task The initialized base task
     * @throws TaskFactoryError if base task creation fails
     */
    Task createBaseTask(std::string_view command);
 
    /**
     * @brief Logs the current task map (temporary debug function)
     */
    void logTaskMap();
 
    // Member Variables
    NodePtr worm_picker_node_;     /// ROS 2 node for communication
    TaskDataMap task_data_map_;    /// Map of task commands to task data
};

#endif // TASK_FACTORY_HPP