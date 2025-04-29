// generate_absolute_movement_task.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <fmt/format.h>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/utils/circular_constraint_calculator.hpp"
#include "worm_picker_core/system/tasks/generation/generate_absolute_movement_task.hpp"

Result<TaskData> GenerateAbsoluteMovementTask::parseCommand(const NodePtr& node, 
                                                            const CommandInfo& info) 
{
    auto extractAndValidateCoordinates = [&]() -> Result<Pose> {
        return extractCoordinates(info);
    };
    
    auto extractMotionTypeWithPose = [&](const Pose& pose) -> Result<PoseMotionPair> {
        return parseMotionType(info)
            .map([&pose](const std::string& motion_type) {
                return PoseMotionPair(pose, motion_type);
            });
    };
    
    auto createStageFromParams = [&](const PoseMotionPair& pair) -> Result<StageDataPtr> {
        const auto& [pose, motion_type] = pair;
        return createStage(pose, motion_type, node, info.getBaseArgsAmount());
    };
    
    auto createTaskDataFromStage = [](const StageDataPtr& stage) -> TaskData {
        return TaskData({stage});
    };
    
    return extractAndValidateCoordinates()
        .flatMap(extractMotionTypeWithPose)
        .flatMap(createStageFromParams)
        .map(createTaskDataFromStage);
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
    const std::array<std::string_view, 2> valid_types = {"LIN", "CIRC"};
    const auto& args = info.getArgs();
    const size_t base_args = info.getBaseArgsAmount();

    if (args.empty() || args.size() < base_args) {
        return Result<std::string>::error(
            fmt::format("Expected {} arguments, got {}", base_args, args.size()));
    }

    const std::string& motion_type = args[base_args - 1];
    if (!std::any_of(valid_types.begin(), valid_types.end(),
                     [&](const auto& type) { return type == motion_type; })) {
        return Result<std::string>::error(fmt::format("Invalid motion type: '{}'", motion_type));
    }

    return Result<std::string>::success(motion_type);
}

Result<std::shared_ptr<StageData>> 
GenerateAbsoluteMovementTask::createStage(const Pose& goal_pose, const std::string& motion_type,
                                          const NodePtr& node, size_t base_args)
{
    if (motion_type == "LIN") {
        return Result<StageDataPtr>::success(createPointStage(goal_pose, base_args));
    }
    
    if (motion_type == "CIRC") {
        auto stage = createCircleStage(goal_pose, base_args);
        auto applyCircConstraint = [&, stage](const auto& current) -> Result<StageDataPtr> {
            auto constraint = CircularConstraintCalculator::calculate(node, current, goal_pose);
            constraint.header.frame_id = *param_utils::getParameter<std::string>(
                node, "frames.base_link"
            );
            
            stage->setCircularConstraint(circular_motion::makeCenterConstraint(constraint));
            return Result<StageDataPtr>::success(stage);
        };
        return getCurrentPose(node).flatMap(applyCircConstraint);
    }
    
    return Result<StageDataPtr>::error(
        fmt::format("Unsupported motion type: '{}'. Expected 'LIN' or 'CIRC'", motion_type));
}

std::shared_ptr<MoveToPointData>
GenerateAbsoluteMovementTask::createPointStage(const Pose& pose, size_t base_args)
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
GenerateAbsoluteMovementTask::createCircleStage(const Pose& pose, size_t base_args)
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

Result<geometry_msgs::msg::PoseStamped> 
GenerateAbsoluteMovementTask::getCurrentPose(rclcpp::Node::SharedPtr node) 
{
    using PoseResult = Result<geometry_msgs::msg::PoseStamped>;
    static tf2_ros::Buffer buffer(node->get_clock());
    static tf2_ros::TransformListener listener(buffer, node);

    geometry_msgs::msg::TransformStamped transform;
    try {
        transform = buffer.lookupTransform(
            *param_utils::getParameter<std::string>(node, "frames.base_link"),
            *param_utils::getParameter<std::string>(node, "end_effectors.current_factor"),
            tf2::TimePointZero,
            std::chrono::milliseconds(100)
        );
    } catch (const tf2::TransformException &ex) {
        throw std::runtime_error("TF2 lookup failed: " + std::string(ex.what()));
        return PoseResult::error(fmt::format("TF2 lookup failed: '{}'", std::string(ex.what())));
    }

    geometry_msgs::msg::PoseStamped pose;
    pose.header = transform.header;
    pose.pose.position.x = transform.transform.translation.x;
    pose.pose.position.y = transform.transform.translation.y;
    pose.pose.position.z = transform.transform.translation.z;
    pose.pose.orientation = transform.transform.rotation;

    return PoseResult::success(pose);
}