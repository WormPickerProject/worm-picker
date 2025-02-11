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
    // Helper to choose a reference vector that is least aligned with the chord.
    static Eigen::Vector3d findRobustReference(const Eigen::Vector3d& chord_direction);

    // Helper to compute a consistent perpendicular direction.
    static Eigen::Vector3d computeConsistentPerpendicular(
        const Eigen::Vector3d& chord_direction,
        const Eigen::Vector3d& plane_normal,
        const Eigen::Vector3d& start_pos);

    /**
     * @brief Computes the constraint position and the corresponding perpendicular offset.
     * 
     * This function calculates the chord between start and goal, finds a robust
     * reference, computes the perpendicular (with any special handling for vertical
     * movements), and then computes the final constraint position.
     * 
     * @param start_pos The starting position.
     * @param goal_pos The goal position.
     * @param constraint_pos [out] The computed constraint position.
     * @param perpendicular [out] The computed (and scaled) perpendicular offset.
     * @throws std::runtime_error if the start and goal positions are too close.
     */
    static void computeConstraintPositionAndPerpendicular(
        const NodePtr& node,
        const Eigen::Vector3d& start_pos,
        const Eigen::Vector3d& goal_pos,
        Eigen::Vector3d &constraint_pos,
        Eigen::Vector3d &perpendicular);

    /**
     * @brief Computes the orientation (as a quaternion) based on the movement direction 
     *        and the perpendicular offset.
     * 
     * @param start_pos The starting position.
     * @param goal_pos The goal position.
     * @param perpendicular The perpendicular offset used in computing the final pose.
     * @return Eigen::Quaterniond The computed orientation.
     */
    static Eigen::Quaterniond computeConstraintOrientation(
        const Eigen::Vector3d& start_pos,
        const Eigen::Vector3d& goal_pos,
        const Eigen::Vector3d& perpendicular);
    
    static Eigen::Vector3d findCircumcenter(
        const Eigen::Vector3d& A, 
        const Eigen::Vector3d& B, 
        const Eigen::Vector3d& C);
};