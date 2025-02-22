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

    static Pose calculate(const NodePtr& node, const Pose& current_state, const Pose& goal_state);

private:
    static constexpr double EPSILON = 1e-10;
    static constexpr double ALIGNMENT_TOLERANCE = 1e-2;

    static Eigen::Vector3d findRobustReference(const Eigen::Vector3d& chord_direction);

    static Eigen::Vector3d computePerpendicular(
        const Eigen::Vector3d& chord_direction,
        const Eigen::Vector3d& plane_normal,
        const Eigen::Vector3d& start_pos);

    static Eigen::Vector3d computeInitialPerpendicular(
        const Eigen::Vector3d &chord_dir,
        const Eigen::Vector3d &plane_norm);

    static Eigen::Vector3d adjustPerpendicularOrientation(
        const Eigen::Vector3d &perpendicular,
        const Eigen::Vector3d &start_pos);

    static std::pair<Eigen::Vector3d, Eigen::Vector3d> computeConstraintGeometry(
        const NodePtr& node,
        const Eigen::Vector3d& start_pos,
        const Eigen::Vector3d& goal_pos);

    static void validateInputPositions(
        const Eigen::Vector3d& start_pos,
        const Eigen::Vector3d& goal_pos);

    static Eigen::Vector3d computeScaledPerpendicular(
        const Eigen::Vector3d& chord_direction,
        const Eigen::Vector3d& start_pos,
        double chord_length,
        double scale);

    static Eigen::Vector3d computeVerticalCasePerpendicular(
        const Eigen::Vector3d& start_pos,
        double chord_length,
        double scale);
    
    static Eigen::Vector3d computeStandardCasePerpendicular(
        const Eigen::Vector3d& chord_direction,
        const Eigen::Vector3d& start_pos,
        double chord_length,
        double scale);

    static Eigen::Quaterniond computeConstraintOrientation(
        const Eigen::Vector3d& start_pos,
        const Eigen::Vector3d& goal_pos,
        const Eigen::Vector3d& perpendicular);

    static Eigen::Vector3d findCircumcenter(
        const Eigen::Vector3d& a,
        const Eigen::Vector3d& b,
        const Eigen::Vector3d& c);
};