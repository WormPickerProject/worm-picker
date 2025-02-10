// circular_constraint.hpp 
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <optional>

enum class CircularMotionType { CENTER, INTERIM };

struct CircularConstraint {
  CircularMotionType type;
  geometry_msgs::msg::PoseStamped aux_pose; 
};