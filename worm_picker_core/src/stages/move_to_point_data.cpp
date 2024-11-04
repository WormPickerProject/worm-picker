// move_to_point_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
// Additional Contributions: Fang-Yen Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");

#include "worm_picker_core/stages/move_to_point_data.hpp"
#include <tf2/LinearMath/Quaternion.h>

MoveToPointData::MoveToPointData(double px, double py, double pz,
                                 double ox, double oy, double oz, double ow,
                                 double velocity_scaling,
                                 double acceleration_scaling)
    : x_(px), y_(py), z_(pz),
      qx_(ox), qy_(oy), qz_(oz), qw_(ow),
      velocity_scaling_factor_(velocity_scaling),
      acceleration_scaling_factor_(acceleration_scaling)
{
    tf2::Quaternion q(qx_, qy_, qz_, qw_);
    q.normalize();
    qx_ = q.x();
    qy_ = q.y();
    qz_ = q.z();
    qw_ = q.w();
}

StageType MoveToPointData::getType() const noexcept
{
    return StageType::MOVE_TO_POINT;
}

double MoveToPointData::getX() const noexcept
{
    return x_;
}

double MoveToPointData::getY() const noexcept
{
    return y_;
}

double MoveToPointData::getZ() const noexcept
{
    return z_;
}

double MoveToPointData::getQX() const noexcept
{
    return qx_;
}

double MoveToPointData::getQY() const noexcept
{
    return qy_;
}

double MoveToPointData::getQZ() const noexcept
{
    return qz_;
}

double MoveToPointData::getQW() const noexcept
{
    return qw_;
}

double MoveToPointData::getVelocityScalingFactor() const noexcept
{
    return velocity_scaling_factor_;
}

double MoveToPointData::getAccelerationScalingFactor() const noexcept
{
    return acceleration_scaling_factor_;
}
