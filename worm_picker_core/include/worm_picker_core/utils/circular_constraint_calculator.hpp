// circular_constraint_calculator.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <Eigen/Dense>
#include <geometry_msgs/msg/pose_stamped.hpp>

class CircularConstraintCalculator {
public:
    using Pose = geometry_msgs::msg::PoseStamped;
    using NodePtr = rclcpp::Node::SharedPtr;

    CircularConstraintCalculator() = default;

    /**
     * @brief Computes the constraint pose given the current and goal states.
     * 
     * @param node The ROS node pointer (used to access parameters).
     * @param current_state The current pose.
     * @param goal_state The target pose.
     * @return PoseStamped The computed constraint pose.
     */
    static Pose calculate(const NodePtr& node, 
                         const Pose& current_state, 
                         const Pose& goal_state);

private:
    static Eigen::Vector3d findRobustReference(const Eigen::Vector3d& chord_direction);

    static Eigen::Vector3d computeConsistentPerpendicular(
        const Eigen::Vector3d& chord_direction,
        const Eigen::Vector3d& plane_normal,
        const Eigen::Vector3d& start_pos);

    static Eigen::Vector3d computeInitialPerpendicular(
        const Eigen::Vector3d &chord_dir,
        const Eigen::Vector3d &plane_norm,
        const double epsilon);

    static Eigen::Vector3d adjustPerpendicularOrientation(
        const Eigen::Vector3d &perpendicular,
        const Eigen::Vector3d &start_pos,
        const double epsilon);

    static void computeConstraintPositionAndPerpendicular(
        const NodePtr& node,
        const Eigen::Vector3d& start_pos,
        const Eigen::Vector3d& goal_pos,
        Eigen::Vector3d& constraint_pos,
        Eigen::Vector3d& perpendicular);

    static Eigen::Quaterniond computeConstraintOrientation(
        const Eigen::Vector3d& start_pos,
        const Eigen::Vector3d& goal_pos,
        const Eigen::Vector3d& perpendicular);

    static Eigen::Vector3d findCircumcenter(
        const Eigen::Vector3d& a,
        const Eigen::Vector3d& b,
        const Eigen::Vector3d& c);
};