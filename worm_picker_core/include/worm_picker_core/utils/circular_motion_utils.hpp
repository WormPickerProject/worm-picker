// circular_motion_utils.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "worm_picker_core/core/tasks/stages/circular_constraint.hpp"

namespace circular_motion {

CircularConstraint makeCenterConstraint(const geometry_msgs::msg::PoseStamped& center_pose);
CircularConstraint makeInterimConstraint(const geometry_msgs::msg::PoseStamped& interim_pose);

} // namespace circular_motion