// task_validator.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <moveit/task_constructor/task.h>
#include <moveit/robot_state/robot_state.h>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/vector3_stamped.hpp>
#include "worm_picker_core/core/tasks/stage_data.hpp"

class TaskValidator {
public:
    using NodePtr = rclcpp::Node::SharedPtr;
    using Task = moveit::task_constructor::Task;
    using RobotState = moveit::core::RobotState;

    explicit TaskValidator(const NodePtr& node); 
    bool validateSolution(const Task& task, 
                          const RobotState& initial_state, 
                          const RobotState& final_state) const;

private:
    using Pose = geometry_msgs::msg::PoseStamped;
    using JointMap = std::map<std::string, double>;
    using Vector3 = geometry_msgs::msg::Vector3Stamped;

    bool validatePoseGoal(const RobotState& state, const Pose& target) const;
    bool validateJointGoal(const RobotState& state, const JointMap& joint_goals) const;
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