// generate_absolute_movement_task.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <fmt/format.h>
#include "worm_picker_core/utils/circular_motion_utils.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_point_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_circle_data.hpp"
#include "worm_picker_core/system/tasks/generation/generate_absolute_movement_task.hpp"

Result<TaskData> GenerateAbsoluteMovementTask::parseCommand(const NodePtr& node, 
                                                            const CommandInfo& info) 
{
    auto coord_result = extractCoordinates(info);
    if (!coord_result) {
        return Result<TaskData>::error(coord_result.error());
    }
    auto pose = coord_result.value();

    auto motion_result = parseMotionType(info);
    if (!motion_result) {
        return Result<TaskData>::error(motion_result.error());
    }
    auto motion_type = motion_result.value();


}

Result<geometry_msgs::msg::PoseStamped>
GenerateAbsoluteMovementTask::extractCoordinates(const CommandInfo& info) 
{
    using PoseResult = Result<geometry_msgs::msg::PoseStamped>;

    if (info.getBaseArgsAmount() == 4) return parsePointStamped(info);
    if (info.getBaseArgsAmount() == 8) return parsePoseStamped(info);

    return PoseResult::error("Invalid number of arguments");
}

Result<geometry_msgs::msg::PoseStamped> 
GenerateAbsoluteMovementTask::parsePointStamped(const CommandInfo& info)
{
    using PoseResult = Result<geometry_msgs::msg::PoseStamped>;
    const auto& args = info.getArgs();

    auto handleParseError = [](const std::string& value, std::string_view coord) {
        return PoseResult::error(fmt::format("Failed to parse {} coordinate: {}", coord, value));
    };

    const auto x = parseDouble(args[0]);
    if (!x) return handleParseError(args[0], "X");

    const auto y = parseDouble(args[1]);
    if (!y) return handleParseError(args[1], "Y");

    const auto z = parseDouble(args[2]);
    if (!z) return handleParseError(args[2], "Z");

    geometry_msgs::msg::PoseStamped ps;
    ps.header.frame_id = "base_link"; 
    ps.pose.position.x = x.value();
    ps.pose.position.y = y.value();
    ps.pose.position.z = z.value();

    return PoseResult::success(std::move(ps));
}

Result<geometry_msgs::msg::PoseStamped> 
GenerateAbsoluteMovementTask::parsePoseStamped(const CommandInfo& info) 
{
    using PoseResult = Result<geometry_msgs::msg::PoseStamped>;
    const auto& args = info.getArgs();

    auto handleParseError = [](const std::string& value, std::string_view coord) {
        return PoseResult::error(fmt::format("Failed to parse {} coordinate: {}", coord, value));
    };

    const auto x = parseDouble(args[0]);
    if (!x) return handleParseError(args[0], "X");

    const auto y = parseDouble(args[1]);
    if (!y) return handleParseError(args[1], "Y");

    const auto z = parseDouble(args[2]);
    if (!z) return handleParseError(args[2], "Z");

    const auto qx = parseDouble(args[3]);
    if (!qx) return handleParseError(args[3], "quaternion X");

    const auto qy = parseDouble(args[4]);
    if (!qy) return handleParseError(args[4], "quaternion Y");

    const auto qz = parseDouble(args[5]);
    if (!qz) return handleParseError(args[5], "quaternion Z");

    const auto qw = parseDouble(args[6]);
    if (!qw) return handleParseError(args[6], "quaternion W");

    geometry_msgs::msg::PoseStamped ps;
    ps.header.frame_id = "base_link";
    ps.pose.position.x = x.value();
    ps.pose.position.y = y.value();
    ps.pose.position.z = z.value();
    ps.pose.orientation.x = qx.value();
    ps.pose.orientation.y = qy.value();
    ps.pose.orientation.z = qz.value();
    ps.pose.orientation.w = qw.value();

    return PoseResult::success(std::move(ps));
}

Result<double> GenerateAbsoluteMovementTask::parseDouble(const std::string& value) 
{
    try {
        return Result<double>::success(std::stod(std::string(value)));
    } catch (const std::exception&) {
        return Result<double>::error(fmt::format("Invalid numeric value: {}", value));
    }
}

Result<std::string> GenerateAbsoluteMovementTask::parseMotionType(const CommandInfo& info) 
{
    using StringResult = Result<std::string>;
    const auto& args = info.getArgs();
    const size_t base_args = info.getBaseArgsAmount();
    
    if (args.empty()) {
        return StringResult::error("No arguments provided");
    }
    if (args.size() < base_args) {
        return StringResult::error(
            fmt::format("Expected {} arguments, got {}", base_args, args.size()));
    }
    
    const std::string& motion_type = args[base_args - 1];
    const std::array<std::string_view, 2> valid_types = {"LIN", "CIRC"};
    if (!std::any_of(valid_types.begin(), valid_types.end(), 
                     [&](const auto& type) { return type == motion_type; })) {
        return StringResult::error(fmt::format("Invalid motion type: '{}'", motion_type));
    }
    
    return StringResult::success(motion_type);
}

Result<std::shared_ptr<StageData>> GenerateAbsoluteMovementTask::createStage(
    const geometry_msgs::msg::PoseStamped& pose,
    const std::string& motion_type,
    const NodePtr& node, 
    size_t base_args)
{
    if (motion_type == "LIN") {
        geometry_msgs::msg::PoseStamped modified_pose = pose;
        // For a "pos" command (base_args == 4), there is no orientation;
        // assign an identity quaternion.
        if (base_args == 4) {
            modified_pose.pose.orientation.x = 0.0;
            modified_pose.pose.orientation.y = 0.0;
            modified_pose.pose.orientation.z = 0.0;
            modified_pose.pose.orientation.w = 1.0;
        }
        auto stage = std::make_shared<MoveToPointData>(
            modified_pose.pose.position.x,
            modified_pose.pose.position.y,
            modified_pose.pose.position.z,
            modified_pose.pose.orientation.x,
            modified_pose.pose.orientation.y,
            modified_pose.pose.orientation.z,
            modified_pose.pose.orientation.w);
        return Result<std::shared_ptr<StageData>>::success(stage);
    }
    else if (motion_type == "CIRC") {
        auto stage = std::make_shared<MoveToCircleData>(
            pose.pose.position.x,
            pose.pose.position.y,
            pose.pose.position.z,
            pose.pose.orientation.x,
            pose.pose.orientation.y,
            pose.pose.orientation.z,
            pose.pose.orientation.w);
        
        // For now, use a placeholder to set the circular constraint.
        auto constraint = circular_motion::makeCenterConstraint(pose);
        stage->setCircularConstraint(constraint);
        return Result<std::shared_ptr<StageData>>::success(stage);
    }
    return Result<std::shared_ptr<StageData>>::error(
        fmt::format("Unknown motion type: {}", motion_type));
}
