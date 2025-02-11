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

Result<std::shared_ptr<StageData>> 
GenerateAbsoluteMovementTask::createStage(const Pose& goal_pose, const std::string& motion_type,
                                          const NodePtr& node, size_t base_args)
{
    using StageResult = Result<std::shared_ptr<StageData>>;
    if (motion_type == "LIN") {
        ////////////////////////////////
        auto logger = rclcpp::get_logger("TaskFactory");
        RCLCPP_INFO(logger, "Creating Absolute LIN stage");
        ////////////////////////////////
        auto stage = createPointStage(goal_pose, base_args);
        return StageResult::success(stage);
    }
    if (motion_type == "CIRC") {
        ////////////////////////////////
        auto logger = rclcpp::get_logger("TaskFactory");
        RCLCPP_INFO(logger, "Creating Absolute CIRC stage");
        ////////////////////////////////
        auto stage = createCircleStage(goal_pose, base_args);
        
        auto pose_result = getCurrentPose(node);
        if (!pose_result) {
            return StageResult::error(pose_result.error());
        }
        auto current_pose = pose_result.value();

        auto constraint_pose = 
            CircularConstraintCalculator::calculate(node, current_pose, goal_pose);
        constraint_pose.header.frame_id = 
            *param_utils::getParameter<std::string>(node, "frames.base_link");
        ////////////////////////
        RCLCPP_INFO(logger, "Constraint pose: (%f, %f, %f)", 
            constraint_pose.pose.position.x, 
            constraint_pose.pose.position.y, 
            constraint_pose.pose.position.z);
        RCLCPP_INFO(logger, "Constraint orientation: (%f, %f, %f, %f)", 
            constraint_pose.pose.orientation.x, 
            constraint_pose.pose.orientation.y, 
            constraint_pose.pose.orientation.z, 
            constraint_pose.pose.orientation.w);
        /////////////////////////////////
        auto constraint = circular_motion::makeCenterConstraint(constraint_pose);

        stage->setCircularConstraint(constraint);
        return StageResult::success(stage);
    }
    return StageResult::error("Unknown error occurred: GenerateAbsoluteMovementTask::createStage");
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

// Result<CircularConstraint> 
// GenerateAbsoluteMovementTask::calculateCircularConstraint(const Pose& current_state,
//                                                           const Pose& goal_state) 
// {
//     // Calculate midpoint
//     Pose constraint_pose;
//     constraint_pose.header = current_state.header;
    
//     // Calculate chord midpoint
//     constraint_pose.pose.position.x = (current_state.pose.position.x + goal_state.pose.position.x) / 2.0;
//     constraint_pose.pose.position.y = (current_state.pose.position.y + goal_state.pose.position.y) / 2.0;
//     constraint_pose.pose.position.z = (current_state.pose.position.z + goal_state.pose.position.z) / 2.0;
    
//     // Calculate chord length
//     double dx = goal_state.pose.position.x - current_state.pose.position.x;
//     double dy = goal_state.pose.position.y - current_state.pose.position.y;
//     double dz = goal_state.pose.position.z - current_state.pose.position.z;
//     double chord_length = std::sqrt(dx*dx + dy*dy + dz*dz);
    
//     // Add vertical elevation
//     double elevation = chord_length / 2.0;
//     constraint_pose.pose.position.z += elevation;
    
//     // Use start state orientation
//     constraint_pose.pose.orientation = current_state.pose.orientation;
    
//     return Result<CircularConstraint>::success(
//         circular_motion::makeCenterConstraint(constraint_pose));
// }

// geometry_msgs::msg::PoseStamped 
// GenerateAbsoluteMovementTask::calculateCircumcircleCondition(const Pose& current_state,
//                                                              const Pose& goal_state) 
// {
//     geometry_msgs::msg::PoseStamped constraint_pose;
//     constraint_pose.header = current_state.header;

//     Eigen::Vector3d start_pos(
//         current_state.pose.position.x,
//         current_state.pose.position.y,
//         current_state.pose.position.z
//     );
    
//     Eigen::Vector3d goal_pos(
//         goal_state.pose.position.x,
//         goal_state.pose.position.y,
//         goal_state.pose.position.z
//     );
    
//     Eigen::Vector3d midpoint = (start_pos + goal_pos) / 2.0;

//     Eigen::Vector3d chord = goal_pos - start_pos;
//     double chord_length = chord.norm();
    
//     Eigen::Vector3d chord_direction = chord.normalized();

//     // Define a robust "up" reference vector
//     Eigen::Vector3d up_vector(0, 0, 1);

//     // Check if the chord is nearly vertical
//     if (std::fabs(chord_direction.dot(up_vector)) > 0.99) {  
//         up_vector = Eigen::Vector3d(1, 0, 0);  // Use X-axis as fallback if needed
//     }

//     // Compute a robust perpendicular vector
//     Eigen::Vector3d perpendicular = chord_direction.cross(up_vector).normalized();

//     // Compute elevation offset
//     double elevation = chord_length / 2.0;
//     Eigen::Vector3d constraint_pos = midpoint + perpendicular * elevation;

//     // Assign calculated position
//     constraint_pose.pose.position.x = constraint_pos.x();
//     constraint_pose.pose.position.y = constraint_pos.y();
//     constraint_pose.pose.position.z = constraint_pos.z();

//     // Use start state orientation
//     constraint_pose.pose.orientation = current_state.pose.orientation;

//     return constraint_pose;
// }

// geometry_msgs::msg::PoseStamped 
// GenerateAbsoluteMovementTask::calculateCircumcircleCondition(
//     const Pose& current_state,
//     const Pose& goal_state) 
// {
//     // Helper function to find robust reference vector
//     auto findRobustReference = [](const Eigen::Vector3d& chord_direction) -> Eigen::Vector3d {
//         Eigen::Vector3d candidates[3] = {
//             Eigen::Vector3d(1, 0, 0),
//             Eigen::Vector3d(0, 1, 0),
//             Eigen::Vector3d(0, 0, 1)
//         };
        
//         double min_alignment = 1.0;
//         Eigen::Vector3d best_reference = candidates[0];
        
//         for (const auto& candidate : candidates) {
//             double alignment = std::abs(chord_direction.dot(candidate));
//             if (alignment < min_alignment) {
//                 min_alignment = alignment;
//                 best_reference = candidate;
//             }
//         }
//         return best_reference;
//     };

//     // Helper function for consistent perpendicular computation
//     auto computeConsistentPerpendicular = [](
//         const Eigen::Vector3d& chord_direction,
//         const Eigen::Vector3d& plane_normal,
//         const Eigen::Vector3d& start_pos,
//         const Eigen::Vector3d& goal_pos) -> Eigen::Vector3d {
        
//         Eigen::Vector3d midpoint = (start_pos + goal_pos) / 2.0;
//         Eigen::Vector3d perpendicular = plane_normal.cross(chord_direction);
//         perpendicular.normalize();
        
//         // Use a consistent reference plane for direction
//         Eigen::Vector3d global_up(0, 0, 1);
//         Eigen::Vector3d reference_dir = global_up.cross(chord_direction);
        
//         if (reference_dir.norm() < 1e-6) {
//             // For vertical movements, use start position as reference
//             Eigen::Vector3d horizontal_start(start_pos.x(), start_pos.y(), 0);
//             if (horizontal_start.norm() > 1e-6) {
//                 reference_dir = horizontal_start.normalized();
//             } else {
//                 reference_dir = Eigen::Vector3d(1, 0, 0);
//             }
//         }
        
//         if (perpendicular.dot(reference_dir) < 0) {
//             perpendicular = -perpendicular;
//         }
        
//         return perpendicular;
//     };

//     // Convert positions to Eigen vectors
//     Eigen::Vector3d start_pos(
//         current_state.pose.position.x,
//         current_state.pose.position.y,
//         current_state.pose.position.z
//     );
    
//     Eigen::Vector3d goal_pos(
//         goal_state.pose.position.x,
//         goal_state.pose.position.y,
//         goal_state.pose.position.z
//     );

//     // Compute midpoint
//     Eigen::Vector3d midpoint = (start_pos + goal_pos) / 2.0;

//     // Compute chord vector and length
//     Eigen::Vector3d chord = goal_pos - start_pos;
//     double chord_length = chord.norm();

//     if (chord_length < 1e-6) {
//         throw std::runtime_error("Start and Goal positions are too close together");
//     }

//     // Get normalized chord direction
//     Eigen::Vector3d chord_direction = chord.normalized();

//     // Find robust reference vector
//     Eigen::Vector3d reference_vector = findRobustReference(chord_direction);

//     // Compute plane normal
//     Eigen::Vector3d plane_normal = chord_direction.cross(reference_vector);
//     plane_normal.normalize();

//     // Compute consistent perpendicular
//     Eigen::Vector3d perpendicular = computeConsistentPerpendicular(
//         chord_direction, plane_normal, start_pos, goal_pos);

//     // Scale perpendicular by chord length
//     perpendicular *= (chord_length / 4.0);

//     // Special handling for near-vertical movements
//     Eigen::Vector3d vertical_dir(0, 0, 1);
//     if (chord_direction.isApprox(vertical_dir, 1e-6) || 
//         chord_direction.isApprox(-vertical_dir, 1e-6)) {
//         // Project start position onto horizontal plane
//         Eigen::Vector3d horizontal_start(start_pos.x(), start_pos.y(), 0);
        
//         if (horizontal_start.norm() > 1e-6) {
//             // Use direction from origin to start, normalized and scaled
//             perpendicular = horizontal_start.normalized() * (chord_length / 4.0);
//         } else {
//             // If start is on vertical axis, use x-direction
//             perpendicular = Eigen::Vector3d(1, 0, 0) * (chord_length / 4.0);
//         }
//     }

//     // Compute final constraint position
//     Eigen::Vector3d constraint_pos = midpoint + perpendicular;

//     // Create and populate the PoseStamped message
//     geometry_msgs::msg::PoseStamped constraint_pose;
//     constraint_pose.header.frame_id = "world";
//     // constraint_pose.header.stamp = this->now();

//     // Set position
//     constraint_pose.pose.position.x = constraint_pos.x();
//     constraint_pose.pose.position.y = constraint_pos.y();
//     constraint_pose.pose.position.z = constraint_pos.z();

//     // Compute orientation based on movement direction
//     Eigen::Vector3d movement_dir = (goal_pos - start_pos).normalized();
//     Eigen::Vector3d up_dir = perpendicular.normalized();
//     Eigen::Vector3d right_dir = movement_dir.cross(up_dir);
    
//     // Convert to quaternion
//     Eigen::Matrix3d rotation;
//     rotation.col(0) = right_dir;
//     rotation.col(1) = movement_dir;
//     rotation.col(2) = up_dir;
    
//     Eigen::Quaterniond q(rotation);
//     q.normalize();

//     // Set orientation
//     constraint_pose.pose.orientation.w = q.w();
//     constraint_pose.pose.orientation.x = q.x();
//     constraint_pose.pose.orientation.y = q.y();
//     constraint_pose.pose.orientation.z = q.z();

//     return constraint_pose;
// }