// generate_absolute_movement_task.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <geometry_msgs/msg/pose_stamped.hpp>
#include "worm_picker_core/core/result.hpp"
#include "worm_picker_core/core/tasks/task_data.hpp"
#include "worm_picker_core/core/commands/command_info.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_point_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_circle_data.hpp"
#include "worm_picker_core/utils/circular_motion_utils.hpp"

class GenerateAbsoluteMovementTask {
public:
    using NodePtr = rclcpp::Node::SharedPtr;
    static Result<TaskData> parseCommand(const NodePtr& node, const CommandInfo& info);

private:
    using StageDataPtr = std::shared_ptr<StageData>;
    using Pose = geometry_msgs::msg::PoseStamped; 
    
    static Result<Pose> extractCoordinates(const CommandInfo& info);
    static Result<Pose> parsePointStamped(const CommandInfo& info);
    static Result<Pose> parsePoseStamped(const CommandInfo& info);
    static Result<double> parseDouble(const std::string& value); 
    static Result<std::string> parseMotionType(const CommandInfo& info);
    static Result<StageDataPtr> createStage(const Pose& pose, const std::string& motion_type,
                                            const NodePtr& node, size_t base_args);
    static std::shared_ptr<MoveToPointData> createPointStage(const Pose& pose, size_t base_args);
    static std::shared_ptr<MoveToCircleData> createCircleStage(const Pose& pose, size_t base_args);
    static Result<Pose> getCurrentPose(rclcpp::Node::SharedPtr node);
    // static Result<CircularConstraint> calculateCircularConstraint(const Pose& current_state,
    //                                                               const Pose& goal_state);
    // static Pose calculateCircumcircleCondition(const Pose& current_state,
    //                                            const Pose& goal_state);
};