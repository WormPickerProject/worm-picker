// move_relative_data.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
// Additional Contributions: Fang-Yen Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");

#include "worm_picker_core/stages/move_relative_data.hpp"

MoveRelativeData::MoveRelativeData(double delta_x, double delta_y, double delta_z,
                                   double velocity_scaling, double acceleration_scaling)
    : dx_(delta_x), dy_(delta_y), dz_(delta_z),
      velocity_scaling_factor_(velocity_scaling),
      acceleration_scaling_factor_(acceleration_scaling) 
{
}

StageType MoveRelativeData::getType() const {
    return StageType::MOVE_RELATIVE;
}

double MoveRelativeData::getDX() const {
    return dx_;
}

double MoveRelativeData::getDY() const {
    return dy_;
}

double MoveRelativeData::getDZ() const {
    return dz_;
}

double MoveRelativeData::getVelocityScalingFactor() const {
    return velocity_scaling_factor_;
}

double MoveRelativeData::getAccelerationScalingFactor() const {
    return acceleration_scaling_factor_;
}
