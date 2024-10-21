// task_factory.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
// Additional Contributions: Fang-Yen Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");

#ifndef TASK_FACTORY_HPP
#define TASK_FACTORY_HPP

#include <rclcpp/rclcpp.hpp>
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/stages.h>
#include <moveit/task_constructor/solvers.h>

#include "worm_picker_core/tasks/task_data_structure.hpp"
#include "worm_picker_core/exceptions/exceptions.hpp"

/** 
 * @brief Factory class to create MoveIt tasks based on predefined commands.
 */
class TaskFactory 
{
public:
    /** 
     * @brief Constructs a TaskFactory with the given ROS2 node.
     * @param node Shared pointer to the ROS2 node.
     * @throws NullNodeException if the provided node is null.
     */
    TaskFactory(const rclcpp::Node::SharedPtr& node);

    /** 
     * @brief Sets up the planning scene by initializing stages and tasks.
     */
    void setupPlanningScene();

    /** 
     * @brief Creates a MoveIt task based on the provided command.
     * @param command The command name to create the task.
     * @return moveit::task_constructor::Task The constructed task.
     * @throws TaskCommandNotFoundException If the command is not found in task_data_map_.
     * @throws NullNodeException If the node is null.
     * @throws UnknownStageTypeException If an unknown StageType is encountered.
     */
    moveit::task_constructor::Task createTask(const std::string& command);

private:
    /**
     * @brief Adds a joint move stage to the task.
     * @param task The MoveIt task to which the stage will be added.
     * @param name The name of the stage.
     * @param joint_data Shared pointer to the JointData containing joint positions and scaling factors.
     * @throws StageCreationFailedException If the stage creation fails.
     */
    void addJointStage(moveit::task_constructor::Task& task, const std::string& name, const std::shared_ptr<JointData>& joint_data);

    /** 
     * @brief Adds a MoveTo stage to the task.
     * @param task The MoveIt task to which the stage will be added.
     * @param name The name of the stage.
     * @param move_to_data Shared pointer to the MoveToData containing pose information and scaling factors.
     * @throws StageCreationFailedException If the stage creation fails.
     */
    void addMoveToStage(moveit::task_constructor::Task& task, const std::string& name, const std::shared_ptr<MoveToData>& move_to_data);
    
    rclcpp::Node::SharedPtr worm_picker_node_;                          ///< Shared pointer to the WormPicker node.
    std::map<std::string, std::shared_ptr<StageData>> stage_data_map_;  ///< Map of stage names to StageData.
    std::map<std::string, TaskData> task_data_map_;                     ///< Map of task commands to TaskData.
};

#endif // TASK_FACTORY_HPP