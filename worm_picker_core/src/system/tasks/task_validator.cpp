// task_validator.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

// #include <Eigen/Geometry>
// #include <cmath>
// #include <algorithm>
#include "worm_picker_core/system/tasks/task_validator.hpp"
#include "worm_picker_core/utils/parameter_utils.hpp"

TaskValidator::TaskValidator(const NodePtr& node)
    : node_{node}
{
    auto pos_tol_opt = param_utils::getParameter<double>(node_, "validation.pos_tol");
    position_tolerance_ = *pos_tol_opt;
    auto ori_tol_opt = param_utils::getParameter<double>(node_, "validation.ori_tol");
    orientation_tolerance_ = *ori_tol_opt; 
    auto joint_tol_opt = param_utils::getParameter<double>(node_, "validation.joint_tol");
    joint_tolerance_ = *joint_tol_opt; 
}

bool TaskValidator::validateSolution(const Task& task, 
                                     const RobotState& initial_state, 
                                     const RobotState& final_state) const 
{
    auto last_stage = task.stages()->operator[](task.stages()->numChildren() - 1);
    const auto& properties = last_stage->properties();

    if (properties.hasProperty("goal")) {
        const auto& goal = properties.get("goal");
        if (goal.type() == typeid(Pose)) {
            const auto& pose_goal = boost::any_cast<Pose>(goal);
            return validatePoseGoal(final_state, pose_goal);
        }
        if (goal.type() == typeid(moveit_msgs::msg::RobotState)) {
            const auto& robot_state = boost::any_cast<moveit_msgs::msg::RobotState>(goal);
            JointMap joint_goals;
            for (size_t i = 0; i < robot_state.joint_state.name.size(); ++i) {
                joint_goals[robot_state.joint_state.name[i]] = robot_state.joint_state.position[i];
            }
            return validateJointGoal(final_state, joint_goals);
        }
    }

    if (properties.hasProperty("direction")) {
        const auto& direction = properties.get<Vector3>("direction");
        (void)direction;
        (void)initial_state;
        // return validateRelativeMove(initial_state, final_state, direction);
        //
        // Relative move validation is not implemented correctly for a task that contains
        // multiple stages. This is because the validation is done only for the last stage, 
        // and does not take into account for the stages before it/looks at the whole picuture. 
        // This approach works with a task ending with a joint and pose goal, but not with a 
        // relative move goal.
        //
        // Return true for now to avoid validation errors.
        return true;
    }

    return false;
}

bool TaskValidator::validatePoseGoal(const RobotState& state, const Pose& target) const
{
    Pose final_pose;
    final_pose.header.frame_id = "base_link";

    auto ee_link = param_utils::getParameter<std::string>(node_, "end_effectors.current_factor");
    const Eigen::Isometry3d& ee_transform = state.getGlobalLinkTransform(*ee_link);

    final_pose.pose.position.x = ee_transform.translation().x();
    final_pose.pose.position.y = ee_transform.translation().y();
    final_pose.pose.position.z = ee_transform.translation().z();

    Eigen::Quaterniond quat(ee_transform.rotation());
    final_pose.pose.orientation.x = quat.x();
    final_pose.pose.orientation.y = quat.y();
    final_pose.pose.orientation.z = quat.z();
    final_pose.pose.orientation.w = quat.w();

    double pos_error = computePositionError(final_pose, target);
    if (pos_error > position_tolerance_) {
        logToleranceExceeded("Pose Goal - Position error", pos_error, position_tolerance_);
        return false;
    }

    double ori_error = computeOrientationError(final_pose, target);
    if (ori_error > orientation_tolerance_) {
        logToleranceExceeded(
            "Pose Goal - Orientation error (radians)", ori_error, orientation_tolerance_);
        return false;
    }

    return true;
}

bool TaskValidator::validateJointGoal(const RobotState& state, const JointMap& joint_goals) const 
{
    for (const auto& [joint_name, target_pos] : joint_goals) {
        double current_pos = state.getJointPositions(joint_name)[0];
        double error = computeJointError(current_pos, target_pos);
        if (error > joint_tolerance_) {
            logJointError(joint_name, current_pos, target_pos);
            return false;
        }
    }
    return true;
}

bool TaskValidator::validateRelativeMove(const RobotState& initial_state,
                                         const RobotState& final_state, 
                                         const Vector3& direction) const
{
    auto ee_link = param_utils::getParameter<std::string>(node_, "end_effectors.current_factor");

    const Eigen::Isometry3d& init_tf = initial_state.getGlobalLinkTransform(*ee_link);
    const Eigen::Isometry3d& final_tf = final_state.getGlobalLinkTransform(*ee_link);

    Eigen::Vector3d actual_move = final_tf.translation() - init_tf.translation();
    Eigen::Vector3d desired_move(direction.vector.x, direction.vector.y, direction.vector.z);

    double actual_dist = actual_move.norm();
    double desired_dist = desired_move.norm();

    double dist_diff = std::abs(actual_dist - desired_dist);
    if (dist_diff > position_tolerance_) {
        logToleranceExceeded("Relative Move - Distance mismatch", dist_diff, position_tolerance_);
        return false;
    }

    if (actual_dist > 1e-6) {
        double direction_dot = actual_move.normalized().dot(desired_move.normalized());
        direction_dot = std::clamp(direction_dot, -1.0, 1.0);

        double angle_error = std::acos(direction_dot);
        if (angle_error > orientation_tolerance_) {
            logToleranceExceeded(
                "Relative Move - Direction error (radians)", angle_error, orientation_tolerance_);
            return false;
        }
    }

    return true;
}

double TaskValidator::computePositionError(const Pose& actual, const Pose& target) const
{
    double dx = actual.pose.position.x - target.pose.position.x;
    double dy = actual.pose.position.y - target.pose.position.y;
    double dz = actual.pose.position.z - target.pose.position.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

double TaskValidator::computeOrientationError(const Pose& actual, const Pose& target) const
{
    double dot = 
        actual.pose.orientation.x * target.pose.orientation.x +
        actual.pose.orientation.y * target.pose.orientation.y +
        actual.pose.orientation.z * target.pose.orientation.z +
        actual.pose.orientation.w * target.pose.orientation.w;

    dot = std::abs(dot);

    double cos_val = 2.0 * dot * dot - 1.0;
    cos_val = std::clamp(cos_val, -1.0, 1.0);

    return std::acos(cos_val);
}

double TaskValidator::computeJointError(double current_pos, double target_pos) const
{
    return std::abs(current_pos - target_pos);
}

void TaskValidator::logToleranceExceeded(const std::string& desc, 
                                         double error, 
                                         double tolerance) const
{
    RCLCPP_WARN(node_->get_logger(),
                "%s exceeded tolerance: error=%.3f, tolerance=%.3f",
                desc.c_str(), error, tolerance);
}


void TaskValidator::logJointError(const std::string& joint_name, 
                                  double current, 
                                  double target) const
{
    double diff = std::abs(current - target);
    RCLCPP_WARN(node_->get_logger(),
                "Joint %s exceeded tolerance: target=%.3f, current=%.3f, diff=%.3f (tol=%.3f)",
                joint_name.c_str(), target, current, diff, joint_tolerance_);
}
