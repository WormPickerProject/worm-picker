// move_to_joint_data.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
// Additional Contributions: Fang-Yen Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");

#include "worm_picker_core/stages/move_to_joint_data.hpp"
#include <cmath>

MoveToJointData::MoveToJointData(double joint1, double joint2, double joint3, 
                                 double joint4, double joint5, double joint6,
                                 double velocity_scaling, double acceleration_scaling) 
    : velocity_scaling_factor_(velocity_scaling), 
      acceleration_scaling_factor_(acceleration_scaling)
{
    const double deg_to_rad = M_PI / 180.0;

    joint_positions_["joint_1"] = joint1 * deg_to_rad;
    joint_positions_["joint_2"] = joint2 * deg_to_rad;
    joint_positions_["joint_3"] = joint3 * deg_to_rad;
    joint_positions_["joint_4"] = joint4 * deg_to_rad;
    joint_positions_["joint_5"] = joint5 * deg_to_rad;
    joint_positions_["joint_6"] = joint6 * deg_to_rad;
}

StageType MoveToJointData::getType() const noexcept
{
    return StageType::MOVE_TO_JOINT;
}

const std::map<std::string, double>& MoveToJointData::getJointPositions() const noexcept 
{
    return joint_positions_;
}

double MoveToJointData::getVelocityScalingFactor() const noexcept 
{
    return velocity_scaling_factor_;
}

double MoveToJointData::getAccelerationScalingFactor() const noexcept 
{
    return acceleration_scaling_factor_;
}
