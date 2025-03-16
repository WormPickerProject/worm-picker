// circular_motion_utils.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/utils/circular_motion_utils.hpp"

namespace circular_motion {
CircularConstraint makeCenterConstraint(const geometry_msgs::msg::PoseStamped& center_pose) 
{
    CircularConstraint c;
    c.type = CircularMotionType::CENTER;
    c.aux_pose = center_pose;
    return c;
}

CircularConstraint makeInterimConstraint(const geometry_msgs::msg::PoseStamped& interim_pose) 
{
    CircularConstraint c;
    c.type = CircularMotionType::INTERIM;
    c.aux_pose = interim_pose;
    return c;
}

}