// task_validator.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef TASK_VALIDATOR_HPP
#define TASK_VALIDATOR_HPP

#include <rclcpp/rclcpp.hpp>
#include <moveit/robot_state/robot_state.h>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/vector3_stamped.hpp>
#include "worm_picker_core/core/tasks/stages/stage_data.hpp"

class TaskValidator {
public:
    using NodePtr = rclcpp::Node::SharedPtr;
    using Stage = moveit::task_constructor::Stage;
    using RobotState = moveit::core::RobotState;

    explicit TaskValidator(const NodePtr& node); 
    bool validateSolution(const Stage* stage, 
                          const RobotState& initial_state, 
                          const RobotState& final_state) const;

private:
    using Pose = geometry_msgs::msg::PoseStamped;
    using JointMap = std::map<std::string, double>;
    using Vector3 = geometry_msgs::msg::Vector3Stamped;

    bool validatePoseGoal(const RobotState& state, const Pose& target) const;
    bool validateJointGoal(const RobobState& state, const JointMap& joint_goals) const;
    bool validateRelativeMove(const RobotState& initial_state,
                              const RobotState& final_state, 
                              const Vector3& direction) const;
    double computePositionError(const Pose& actual, const Pose& target) const;
    double computeOrientationError(const Pose& actual, const Pose& target) const;
    double computeJointError(double current_pos, double target_pos) const;
    void logToleranceExceeded(const std::string& desc, double error, double tolerance) const;
    void logJointError(const std::string& joint_name, double current, double target) const;

    NodePtr node_;
    double position_tolerance_;
    double orientation_tolerance_;
    double joint_tolerance_;
};

#endif // TASK_VALIDATOR_HPP
