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
class TaskFactory 
{
public:
    /** 
     * @brief Constructs a TaskFactory with the specified ROS 2 node.
     * 
     * Initializes the TaskFactory with a shared ROS 2 node pointer, enabling task creation
     * with access to ROS parameters and services.
     * 
     * @param node Shared pointer to the ROS 2 node used for parameter and service access.
     * @throws TaskFactoryError if the provided node is null.
     */
    explicit TaskFactory(const rclcpp::Node::SharedPtr& node);

    /**
     * @brief Generates a MoveIt task based on the specified command.
     * 
     * This function creates a task tailored to the given command. Each command corresponds
     * to a predefined task configuration, enabling the factory to produce specific motion
     * planning and execution behaviors.
     * 
     * @param command The name of the command used to identify and configure the task.
     * @return Task The constructed MoveIt task ready for planning and execution.
     * @throws TaskFactoryError if task creation fails due to an invalid command or other setup issues.
     */
    [[nodiscard]] moveit::task_constructor::Task createTask(std::string_view command);

private:
    /// Path to configuration files for workstation and hotel data.
    static constexpr char CONFIG_PATH[] = "/worm-picker/worm_picker_description/program_data/data_files";

    /// Alias for the MoveIt Task used in task construction.
    using Task = moveit::task_constructor::Task;

    /// Alias for the MoveIt stage representing the current state of the robot.
    using CurrentStateStage = moveit::task_constructor::stages::CurrentState;

    /// Alias for the execution information used in trajectory planning.
    using TrajectoryExecutionInfo = moveit::task_constructor::TrajectoryExecutionInfo;

    /// Map of workstation IDs to workstation data, including Cartesian coordinates.
    using WorkstationDataMap = std::unordered_map<std::string, WorkstationData>;

    /// Map of hotel data IDs to hotel data, used as a placeholder for future development.
    using HotelDataMap = std::unordered_map<std::string, HotelData>;

    /// Shared pointer type for stage data, used in task stages.
    using StageDataPtr = std::shared_ptr<StageData>;

    /**
     * @brief Declares the parameters required by the TaskFactory.
     * 
     * Initializes ROS parameters such as file paths and task-related configurations
     * required for the TaskFactory to operate correctly.
     */
    void declareParameters();

    /** 
     * @brief Parses workstation and hotel data from their respective JSON files.
     * 
     * Loads the data required for workstation and hotel operations from configuration files
     * and stores them in their corresponding data maps.
     */
    void parseData();

    /** 
     * @brief Sets up the planning scene by initializing stages and tasks.
     * 
     * Prepares the environment and configures necessary stages to execute tasks, allowing
     * for detailed planning and execution within the task framework.
     */
    void setupPlanningScene();

    /**
     * @brief Creates a base task with the specified command name.
     * 
     * Initializes a base task according to the given command, setting up preliminary
     * configurations and properties necessary for task execution.
     * 
     * @param command The command name to assign to the task.
     * @return Task The initialized base task.
     */
    Task createBaseTask(std::string_view command);

    /// Shared pointer to the WormPicker node, responsible for ROS 2 communication.
    rclcpp::Node::SharedPtr worm_picker_node_;

    /// Map linking workstation IDs (e.g., "A1") to WorkstationData, containing Cartesian coordinates and robot joint positions.
    WorkstationDataMap workstation_data_map_;

    /// Placeholder map for hotel data, to be populated with HotelData in future development.
    HotelDataMap hotel_data_map_;

    /// Map linking stage names to shared pointers of StageData, used in task staging.
    std::unordered_map<std::string, StageDataPtr> stage_data_map_;

    /// Map associating task commands with TaskData, defining data required for specific tasks.
    std::map<std::string, TaskData> task_data_map_;

    // Temporary Functions
    void logDataMaps() const;
};

#endif // TASK_FACTORY_HPP