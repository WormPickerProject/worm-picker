// task_factory.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef TASK_FACTORY_HPP
#define TASK_FACTORY_HPP

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
     * @brief Parses the workstation (and soon hotel) data from their respective JSON file.
     */
    void parseData();
    
    /** 
     * @brief Sets up the planning scene by initializing stages and tasks.
     */
    void setupPlanningScene();

    // Type aliases
    using Task = moveit::task_constructor::Task;
    using CurrentStateStage = moveit::task_constructor::stages::CurrentState;
    using TrajectoryExecutionInfo = moveit::task_constructor::TrajectoryExecutionInfo;
    using WorkstationDataMap = std::unordered_map<std::string, WorkstationData>;
    using HotelDataMap = std::unordered_map<std::string, HotelData>; 

    rclcpp::Node::SharedPtr worm_picker_node_;                          ///< Shared pointer to the WormPicker node.
    WorkstationDataMap workstation_data_map_;                           ///< Map of workstation IDs (e.g., "A1") to `WorkstationData` containing Cartesian `Coordinate` and robot `Joint` positions.
    HotelDataMap hotel_data_map_;                                       ///< Filler, not done 
    std::unordered_map<std::string, std::shared_ptr<StageData>> stage_data_map_;  ///< Map of stage names to StageData.
    std::map<std::string, TaskData> task_data_map_;                     ///< Map of task commands to TaskData.

    // Temporary Functions
    void logDataMaps() const;
};

#endif // TASK_FACTORY_HPP