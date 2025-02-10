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

class GenerateAbsoluteMovementTask {
public:
    using NodePtr = rclcpp::Node::SharedPtr;
    static Result<TaskData> parseCommand(const NodePtr& node, const CommandInfo& info);

private:
    using StageDataPtr = std::shared_ptr<StageData>;
    using StageDataVector = std::vector<std::shared_ptr<StageData>>; 
    
    static Result<geometry_msgs::msg::PoseStamped> extractCoordinates(const CommandInfo& info);
    static Result<geometry_msgs::msg::PoseStamped> parsePointStamped(const CommandInfo& info);
    static Result<geometry_msgs::msg::PoseStamped> parsePoseStamped(const CommandInfo& info);
    static Result<double> parseDouble(const std::string& value); 

    // New Helper Functions
    static Result<std::tuple<std::string>> parseMotionType(const CommandInfo& info);
    static Result<StageDataPtr> createStage(const geometry_msgs::msg::PoseStamped& pose,
                                            const std::string& motion_type,
                                            const NodePtr& node, 
                                            size_t base_args);
    static std::shared_ptr<MoveToPointData> createPointStage(
        const geometry_msgs::msg::PoseStamped& pose, 
        size_t base_args);
    static std::shared_ptr<MoveToCircleData> createCircleStage(
        const geometry_msgs::msg::PoseStamped& pose, 
        size_t base_args);
};