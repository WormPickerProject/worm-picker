// task_data_structure.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
// Additional Contributions: Fang-Yen Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");

#ifndef TASK_DATA_STRUCTURE_HPP
#define TASK_DATA_STRUCTURE_HPP

#include <tf2/LinearMath/Quaternion.h>
#include <rclcpp/rclcpp.hpp>

/** 
 * @enum StageType
 * @brief Enumerates the types of stages available.
 */
enum class StageType { MOVE_TO, JOINT };

/** 
 * @struct StageData
 * @brief Abstract base struct for different types of stage data.
 */
struct StageData { 
    virtual ~StageData() = default;

    /** 
     * @brief Retrieves the type of the stage.
     * 
     * @return StageType The type of the stage.
     */
    virtual StageType getType() const = 0;
};

/** 
 * @struct MoveToData
 * @brief Struct representing data for a MoveTo-based stage.
 */
struct MoveToData : public StageData { 
    double x, y, z;  // Position coordinates.
    double qx, qy, qz, qw;  // Orientation as a quaternion.
    double velocity_scaling_factor;  // Velocity scaling factor.
    double acceleration_scaling_factor;  // Acceleration scaling factor.

    /** 
     * @brief Default constructor.
     */
    MoveToData() = default;

    /** 
     * @brief Constructs a MoveToData with the given parameters.
     * @param px Position x-coordinate.
     * @param py Position y-coordinate.
     * @param pz Position z-coordinate.
     * @param ox Orientation quaternion x-component.
     * @param oy Orientation quaternion y-component.
     * @param oz Orientation quaternion z-component.
     * @param ow Orientation quaternion w-component.
     * @param velocity_scaling Velocity scaling factor (default: 0.1).
     * @param acceleration_scaling Acceleration scaling factor (default: 0.1).
     */
    MoveToData(double px, double py, double pz, double ox, double oy, double oz, double ow,
              double velocity_scaling = 0.1, double acceleration_scaling = 0.1);

    StageType getType() const override { return StageType::MOVE_TO; }
};

/** 
 * @struct JointData
 * @brief Struct representing data for a joint-based stage.
 */
struct JointData : public StageData { 
    std::map<std::string, double> joint_positions;  // Map of joint names to their positions (in radians).
    double velocity_scaling_factor;  // Velocity scaling factor.
    double acceleration_scaling_factor;  // Acceleration scaling factor.

    /** 
     * @brief Default constructor.
     */
    JointData() = default;

    /**
     * @brief Constructs a JointData with the given joint angles and scaling factors.
     * @param joint1 Angle for joint 1 in degrees.
     * @param joint2 Angle for joint 2 in degrees.
     * @param joint3 Angle for joint 3 in degrees.
     * @param joint4 Angle for joint 4 in degrees.
     * @param joint5 Angle for joint 5 in degrees.
     * @param joint6 Angle for joint 6 in degrees.
     * @param velocity_scaling Velocity scaling factor (default: 0.1).
     * @param acceleration_scaling Acceleration scaling factor (default: 0.1).
     */
    JointData(double joint1, double joint2, double joint3, double joint4, double joint5, double joint6,
              double velocity_scaling = 0.1, double acceleration_scaling = 0.1);

    StageType getType() const override { return StageType::JOINT; }
};

/** 
 * @struct TaskData
 * @brief Struct representing a collection of stages that form a task.
 */
struct TaskData { 
    std::vector<std::shared_ptr<StageData>> stages;  // Vector of stages constituting the task.

    /** 
     * @brief Default constructor.
     */
    TaskData() = default;

    /**
     * @brief Constructs a TaskData with the given stage data map and stage names.
     * @param stage_data_map Map of stage names to StageData.
     * @param stage_names Initializer list of stage names to include in the task.
     * @throws std::invalid_argument If any stage name is not found in stage_data_map.
     */
    TaskData(const std::map<std::string, std::shared_ptr<StageData>>& stage_data_map,
             const std::initializer_list<std::string>& stage_names);
};

#endif  // TASK_DATA_STRUCTURE_HPP