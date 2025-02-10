// generate_absolute_movement_task.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <fmt/format.h>
#include "worm_picker_core/utils/circular_motion_utils.hpp"
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
    auto [motion_type] = motion_result.value();

    auto stage_result = createStage(pose, motion_type, node, info.getBaseArgsAmount());
    if (!stage_result) {
        return Result<TaskData>::error(stage_result.error());
    }
    TaskData::StageVector stages;
    stages.push_back(stage_result.value());

    TaskData task_data(stages);
    return Result<TaskData>::success(task_data);
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

Result<std::tuple<std::string>> 
GenerateAbsoluteMovementTask::parseMotionType(const CommandInfo& info) 
{
    // TODO: The use of this tuple is needed because of a type deduction issue with Result<T>. 
    //       This is because in Result<E>::error() the type E is a std::string and if we try to 
    //       asign a std::string to Result::success() it will cause the compiler to get confused. 
    //       This should be fixed in the future by allowing Result to have type T as a std:string. 
    using WrappedStringResult = Result<std::tuple<std::string>>;
    const auto& args = info.getArgs();
    const size_t base_args = info.getBaseArgsAmount();
    
    if (args.empty()) {
        return WrappedStringResult::error("No arguments provided");
    }
    if (args.size() < base_args) {
        return WrappedStringResult::error(
            fmt::format("Expected {} arguments, got {}", base_args, args.size()));
    }
    
    const std::string& motion_type = args[base_args - 1];
    const std::array<std::string_view, 2> valid_types = {"LIN", "CIRC"};
    if (!std::any_of(valid_types.begin(), valid_types.end(), 
                     [&](const auto& type) { return type == motion_type; })) {
        return WrappedStringResult::error(fmt::format("Invalid motion type: '{}'", motion_type));
    }
    
    return WrappedStringResult::success(std::make_tuple(motion_type));
}

Result<std::shared_ptr<StageData>> GenerateAbsoluteMovementTask::createStage(
    const geometry_msgs::msg::PoseStamped& pose,
    const std::string& motion_type,
    [[maybe_unused]] const NodePtr& node, 
    size_t base_args)
{
    using StageResult = Result<std::shared_ptr<StageData>>;
    if (motion_type == "LIN") {
        auto stage = createPointStage(pose, base_args);
        return StageResult::success(stage);
    }
    if (motion_type == "CIRC") {
        auto stage = createCircleStage(pose, base_args);
        
        // For now, use a placeholder to set the circular constraint.
        auto constraint = circular_motion::makeCenterConstraint(pose);

        stage->setCircularConstraint(constraint);
        return Result<std::shared_ptr<StageData>>::success(stage);
    }
    return StageResult::error("Unknown error occurred: GenerateAbsoluteMovementTask::createStage");
}

std::shared_ptr<MoveToPointData>
GenerateAbsoluteMovementTask::createPointStage(const geometry_msgs::msg::PoseStamped& pose, 
                                               size_t base_args)
{
    return base_args == 4 ?
        std::make_shared<MoveToPointData>(
            pose.pose.position.x,
            pose.pose.position.y,
            pose.pose.position.z) :
        std::make_shared<MoveToPointData>(
            pose.pose.position.x,
            pose.pose.position.y,
            pose.pose.position.z,
            pose.pose.orientation.x,
            pose.pose.orientation.y,
            pose.pose.orientation.z,
            pose.pose.orientation.w);
}

std::shared_ptr<MoveToCircleData>
GenerateAbsoluteMovementTask::createCircleStage(const geometry_msgs::msg::PoseStamped& pose, 
                                                size_t base_args)
{
    return base_args == 4 ?
        std::make_shared<MoveToCircleData>(
            pose.pose.position.x,
            pose.pose.position.y,
            pose.pose.position.z) :
        std::make_shared<MoveToCircleData>(
            pose.pose.position.x,
            pose.pose.position.y,
            pose.pose.position.z,
            pose.pose.orientation.x,
            pose.pose.orientation.y,
            pose.pose.orientation.z,
            pose.pose.orientation.w);
}
