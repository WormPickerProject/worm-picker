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

#include "worm_picker_core/exceptions/exceptions.hpp"

/** 
 * @enum StageType
 * @brief Enumerates the types of stages available.
 */
enum class StageType { MOVE_TO_POINT, MOVE_TO_JOINT, MOVE_RELATIVE };

/** 
 * @struct StageData
 * @brief Abstract base struct for different types of stage data.
 */
struct StageData { 
    virtual ~StageData() = default;

    /** 
     * @brief Retrieves the type of the stage.
     * @return StageType The type of the stage.
     */
    virtual StageType getType() const = 0;
};

/** 
 * @struct MoveToPointData
 * @brief Struct representing data for a point MoveTo-based stage.
 */
struct MoveToPointData : public StageData { 
    double x, y, z;  // Position coordinates.
    double qx, qy, qz, qw;  // Orientation as a quaternion.
    double velocity_scaling_factor;  // Velocity scaling factor.
    double acceleration_scaling_factor;  // Acceleration scaling factor.

    /** 
     * @brief Default constructor.
     */
    MoveToPointData() = default;

    /** 
     * @brief Constructs a MoveToPointData with the given parameters.
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
    MoveToPointData(double px, double py, double pz, double ox, double oy, double oz, double ow,
                    double velocity_scaling = 0.1, double acceleration_scaling = 0.1);

    StageType getType() const override { return StageType::MOVE_TO_POINT; }
};

/** 
 * @struct MoveToJointData
 * @brief Struct representing data for a joint MoveTo-based stage.
 */
struct MoveToJointData : public StageData { 
    std::map<std::string, double> joint_positions;  // Map of joint names to their positions (in radians).
    double velocity_scaling_factor;  // Velocity scaling factor.
    double acceleration_scaling_factor;  // Acceleration scaling factor.

    /** 
     * @brief Default constructor.
     */
    MoveToJointData() = default;

    /**
     * @brief Constructs a MoveToJointData with the given joint angles and scaling factors.
     * @param joint1 Angle for joint 1 in degrees.
     * @param joint2 Angle for joint 2 in degrees.
     * @param joint3 Angle for joint 3 in degrees.
     * @param joint4 Angle for joint 4 in degrees.
     * @param joint5 Angle for joint 5 in degrees.
     * @param joint6 Angle for joint 6 in degrees.
     * @param velocity_scaling Velocity scaling factor (default: 0.1).
     * @param acceleration_scaling Acceleration scaling factor (default: 0.1).
     */
    MoveToJointData(double joint1, double joint2, double joint3, double joint4, double joint5, double joint6,
                    double velocity_scaling = 0.1, double acceleration_scaling = 0.1);

    StageType getType() const override { return StageType::MOVE_TO_JOINT; }
};

/** 
 * @struct MoveRelativeData
 * @brief Struct representing data for a relative move stage.
 */
struct MoveRelativeData : public StageData { 
    double dx, dy, dz;  // Position deltas.
    double velocity_scaling_factor;      // Velocity scaling factor.
    double acceleration_scaling_factor;  // Acceleration scaling factor.

    /** 
     * @brief Default constructor.
     */
    MoveRelativeData() = default;

    /** 
     * @brief Constructs a MoveRelativeData with the given parameters.
     * @param delta_x Position delta x-coordinate.
     * @param delta_y Position delta y-coordinate.
     * @param delta_z Position delta z-coordinate.
     * @param velocity_scaling Velocity scaling factor (default: 0.1).
     * @param acceleration_scaling Acceleration scaling factor (default: 0.1).
     */
    MoveRelativeData(double delta_x, double delta_y, double delta_z,
                    double velocity_scaling = 0.1, double acceleration_scaling = 0.1);

    StageType getType() const override { return StageType::MOVE_RELATIVE; }
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
     * @throws StageNotFoundException If any stage name is not found in the stage_data_map.
     */
    TaskData(const std::map<std::string, std::shared_ptr<StageData>>& stage_data_map,
             const std::initializer_list<std::string>& stage_names);
};

/**
 * @brief Represents the coordinate data information of a workstation or hotel.
 */
struct Coordinate {
    double position_x; ///< X position of the workstation.
    double position_y; ///< Y position of the workstation.
    double position_z; ///< Z position of the workstation.
    double orientation_x; ///< X component of orientation quaternion.
    double orientation_y; ///< Y component of orientation quaternion.
    double orientation_z; ///< Z component of orientation quaternion.
    double orientation_w; ///< W component of orientation quaternion.
};

/**
 * @brief Contains coordinate data for the workstation.
 */
struct WorkstationData {
    Coordinate coordinate; ///< Coordinate data of the workstation.
};

/**
 * @brief Contains coordinate data for the hotels.
 */
struct HotelData {
    Coordinate coordinate; ///< Coordinate data of the hotels.
};

#endif  // TASK_DATA_STRUCTURE_HPP