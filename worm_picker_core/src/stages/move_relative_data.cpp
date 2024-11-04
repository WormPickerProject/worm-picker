// move_relative_data.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
// Additional Contributions: Fang-Yen Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");

#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
#include "worm_picker_core/stages/move_relative_data.hpp"

MoveRelativeData::MoveRelativeData(double delta_x, double delta_y, double delta_z,
                                   double velocity_scaling, double acceleration_scaling)
    : dx_(delta_x), dy_(delta_y), dz_(delta_z),
      velocity_scaling_factor_(velocity_scaling),
      acceleration_scaling_factor_(acceleration_scaling) 
{
}

std::unique_ptr<moveit::task_constructor::Stage> MoveRelativeData::createStage(const std::string& name,
                                                                               const rclcpp::Node::SharedPtr& node) const
{
    geometry_msgs::msg::Vector3Stamped direction_vector;
    direction_vector.header.frame_id = "eoat_tcp";
    direction_vector.header.stamp = node->now();
    direction_vector.vector.x = dx_;
    direction_vector.vector.y = dy_;
    direction_vector.vector.z = dz_;

    auto cartesian_planner = std::make_shared<moveit::task_constructor::solvers::CartesianPath>();
    cartesian_planner->setMaxVelocityScalingFactor(velocity_scaling_factor_);
    cartesian_planner->setMaxAccelerationScalingFactor(acceleration_scaling_factor_);
    cartesian_planner->setStepSize(.01);
    cartesian_planner->setMinFraction(0.0);

    auto stage = std::make_unique<moveit::task_constructor::stages::MoveRelative>(name, cartesian_planner);
    stage->setDirection(direction_vector);
    stage->setGroup("gp4_arm");
    stage->setIKFrame("eoat_tcp");

    moveit::task_constructor::TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {"follow_joint_trajectory"};
    stage->setProperty("trajectory_execution_info", execution_info);

    return stage;
}

StageType MoveRelativeData::getType() const noexcept 
{
    return StageType::MOVE_RELATIVE;
}

double MoveRelativeData::getDX() const noexcept 
{
    return dx_;
}

double MoveRelativeData::getDY() const noexcept 
{
    return dy_;
}

double MoveRelativeData::getDZ() const noexcept 
{
    return dz_;
}

double MoveRelativeData::getVelocityScalingFactor() const noexcept 
{
    return velocity_scaling_factor_;
}

double MoveRelativeData::getAccelerationScalingFactor() const noexcept 
{
    return acceleration_scaling_factor_;
}
