// circular_constraint_calculator.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/utils/circular_constraint_calculator.hpp"

std::pair<Eigen::Vector3d, Eigen::Vector3d> CircularConstraintCalculator::computeConstraintGeometry(
    const NodePtr& node,
    const Eigen::Vector3d& start_pos,
    const Eigen::Vector3d& goal_pos)
{
    validateInputPositions(start_pos, goal_pos);
    
    const Eigen::Vector3d chord = goal_pos - start_pos;
    const Eigen::Vector3d chord_dir = chord.normalized();
    double chord_length = chord.norm();
    
    double scale = *param_utils::getParameter<double>(node, "settings.circ_height_scaler");
    const auto scaled_perp = computeScaledPerpendicular(chord_dir, start_pos, chord_length, scale);
    
    const Eigen::Vector3d midpoint = (start_pos + goal_pos) / 2.0;
    return std::make_pair(midpoint + scaled_perp, scaled_perp);
}

Eigen::Vector3d CircularConstraintCalculator::computeScaledPerpendicular(
    const Eigen::Vector3d& chord_direction,
    const Eigen::Vector3d& start_pos,
    double chord_length,
    double scale)
{
    auto logger = rclcpp::get_logger("CircularConstraintCalculator");
    RCLCPP_INFO(logger, "Chord direction: [%.3f, %.3f, %.3f]",
        chord_direction.x(), chord_direction.y(), chord_direction.z());

    const Eigen::Vector3d vertical_dir(0, 0, 1);
    const double vertical_tolerance = 1e-3;
    
    bool is_positive_vertical = chord_direction.isApprox(vertical_dir, vertical_tolerance);
    bool is_negative_vertical = chord_direction.isApprox(-vertical_dir, vertical_tolerance);

    if (is_positive_vertical || is_negative_vertical) {
        RCLCPP_INFO(logger, "Vertical movement detected: %s",
            is_positive_vertical ? "moving up" : "moving down");
        return computeVerticalCasePerpendicular(start_pos, chord_length, scale);
    }

    // if (chord_direction.isApprox(vertical_dir, vertical_tolerance) ||
    //     chord_direction.isApprox(-vertical_dir, vertical_tolerance)) {
    //     return computeVerticalCasePerpendicular(start_pos, chord_length, scale);
    // }
    
    return computeStandardCasePerpendicular(chord_direction, start_pos, chord_length, scale);
}

Eigen::Vector3d CircularConstraintCalculator::computeVerticalCasePerpendicular(
    const Eigen::Vector3d& start_pos,
    double chord_length,
    double scale)
{
    (void) start_pos;
    const double scaled_length = chord_length * scale / 2.0;
    
    // Eigen::Vector3d horizontal_start(start_pos.x(), start_pos.y(), 0);
    // if (horizontal_start.norm() > 1e-6) {
    //     return horizontal_start.normalized() * scaled_length;
    // }
    
    return Eigen::Vector3d(1, 0, 0) * scaled_length;
}

Eigen::Vector3d CircularConstraintCalculator::computeStandardCasePerpendicular(
    const Eigen::Vector3d& chord_direction,
    const Eigen::Vector3d& start_pos,
    double chord_length,
    double scale)
{
    const auto reference_vector = findRobustReference(chord_direction);
    const auto plane_normal = chord_direction.cross(reference_vector).normalized();
    const auto perpendicular = computePerpendicular(chord_direction, plane_normal, start_pos);
    
    return perpendicular * (chord_length * scale / 2.0);
}

Eigen::Vector3d CircularConstraintCalculator::findRobustReference(
    const Eigen::Vector3d& chord_direction)
{
    const std::array<std::pair<Eigen::Vector3d, int>, 1> candidates = {{
        // {Eigen::Vector3d(1, 0, 0), 1},
        // {Eigen::Vector3d(0, 1, 0), 1},
        {Eigen::Vector3d(0, 0, 1), 2}
    }};

    double best_alignment = 1.0;
    auto best_reference = candidates[0];

    for (const auto &cand : candidates) {
        int current_best_priority = best_reference.second;
        double alignment = std::abs(chord_direction.dot(cand.first));
        bool alignments_nearly_equal = std::abs(alignment - best_alignment) <= ALIGNMENT_TOLERANCE;
        bool has_better_alignment = alignment < best_alignment - ALIGNMENT_TOLERANCE;
        bool has_higher_priority = alignments_nearly_equal && cand.second > current_best_priority;

        if (has_better_alignment || has_higher_priority) {
            best_alignment = alignment;
            best_reference = cand;
        }
    }

    auto logger = rclcpp::get_logger("CircularConstraintCalculator");
    RCLCPP_INFO(logger, "Selected robust reference: [%.3f, %.3f, %.3f]",
                best_reference.first.x(), best_reference.first.y(), best_reference.first.z());
    return best_reference.first;

}

Eigen::Vector3d CircularConstraintCalculator::computePerpendicular(
    const Eigen::Vector3d &chord_direction,
    const Eigen::Vector3d &plane_normal,
    const Eigen::Vector3d &start_pos)
{
    (void) start_pos;
    Eigen::Vector3d chord_dir = chord_direction.normalized();
    Eigen::Vector3d plane_norm = plane_normal.normalized();

    // const auto perpendicular = computeInitialPerpendicular(chord_dir, plane_norm);
    // auto final_perpendicular = adjustPerpendicularOrientation(initial_perpendicular, start_pos);

    Eigen::Vector3d perpendicular = plane_norm.cross(chord_dir).normalized();
    perpendicular = perpendicular.z() < 0 ? -perpendicular : perpendicular;

    assert(std::abs(perpendicular.norm() - 1.0) < EPSILON);
    assert(std::abs(perpendicular.dot(chord_dir)) < EPSILON);

    RCLCPP_INFO(rclcpp::get_logger("CircularConstraintCalculator"),
                "Computed perpendicular: [%.3f, %.3f, %.3f]",
                perpendicular.x(), perpendicular.y(), perpendicular.z());
    return perpendicular;
}

// Eigen::Vector3d CircularConstraintCalculator::computeInitialPerpendicular(
//     const Eigen::Vector3d &chord_dir,
//     const Eigen::Vector3d &plane_norm)
// {
    // Eigen::Vector3d perpendicular = plane_norm.cross(chord_dir).normalized();
    // double perp_norm = perpendicular.norm();

    // Main: The plane normal and chord direction are not parallel
    // if (perp_norm >= EPSILON) {
        // perpendicular /= perp_norm;
        // return perpendicular.z() < 0 ? -perpendicular : perpendicular;;
    // }

    // MAYBE REMOVE THIS
    // Fallback 1: The chord is nearly vertical (parallel to Z-axis), use X-axis as perpendicular
    // const Eigen::Vector3d global_up(0, 0, 1);
    // bool is_vertical = std::abs(chord_dir.dot(global_up)) > 1.0 - EPSILON;
    // if (is_vertical) {
    //     return Eigen::Vector3d(1, 0, 0);
    // }

    // MAYBE REMOVE THIS
    // Fallback 2: chord_dir and plane_norm vectors are parallel but not vertical, use global up
    // perpendicular = global_up.cross(chord_dir);
    // perpendicular.normalize();
    // return perpendicular;
// }

// Eigen::Vector3d CircularConstraintCalculator::adjustPerpendicularOrientation(
//     const Eigen::Vector3d& perpendicular,
//     const Eigen::Vector3d& start_pos)
// {
    // Case 1: Vector has vertical component - ensure it points up
    // if (std::abs(perpendicular.z()) >= EPSILON) {
        // return perpendicular.z() < 0 ? -perpendicular : perpendicular;
    // }

    // MAYBE REMOVE THIS
    // Case 2: Horizontal vector - check start position reference
    // Eigen::Vector3d start_horizontal(start_pos.x(), start_pos.y(), 0);
    // double horizontal_norm = start_horizontal.norm();
    
    // MAYBE REMOVE THIS
    // No clear horizontal reference - keep original orientation
    // if (horizontal_norm <= EPSILON) {
    //     return perpendicular;
    // }

    // MAYBE REMOVE THIS
    // Case 3: Align with start position's horizontal direction
    // return perpendicular.dot(start_horizontal) < 0 ? -perpendicular : perpendicular;
// }

Eigen::Quaterniond CircularConstraintCalculator::computeConstraintOrientation(
    const Eigen::Vector3d& start_pos,
    const Eigen::Vector3d& goal_pos,
    const Eigen::Vector3d& perpendicular)
{
    // Compute the movement and up directions.
    Eigen::Vector3d movement_dir = (goal_pos - start_pos).normalized();
    Eigen::Vector3d up_dir = perpendicular.normalized();
    Eigen::Vector3d right_dir = movement_dir.cross(up_dir);

    // Build the rotation matrix.
    Eigen::Matrix3d rotation;
    rotation.col(0) = right_dir;
    rotation.col(1) = movement_dir;
    rotation.col(2) = up_dir;

    Eigen::Quaterniond q(rotation);
    q.normalize();
    return q;
}

Eigen::Vector3d CircularConstraintCalculator::findCircumcenter(
    const Eigen::Vector3d& a,
    const Eigen::Vector3d& b,
    const Eigen::Vector3d& c)
{
    Eigen::Vector3d ab = b - a;
    Eigen::Vector3d ac = c - a;
    Eigen::Vector3d normal = ab.cross(ac);

    Eigen::Vector3d midAB = (a + b) / 2.0;
    Eigen::Vector3d midAC = (a + c) / 2.0;

    Eigen::Vector3d perpAB = normal.cross(ab);
    Eigen::Vector3d perpAC = normal.cross(ac);

    Eigen::Vector3d diff = midAC - midAB;

    double d1 = perpAB.dot(perpAB);
    double d2 = perpAB.dot(perpAC);
    double d3 = perpAC.dot(perpAC);
    double d4 = perpAB.dot(diff);
    double d5 = perpAC.dot(diff);

    double denom = d1 * d3 - d2 * d2;
    double t = (d4 * d3 - d5 * d2) / denom;

    return midAB + t * perpAB;
}

void CircularConstraintCalculator::validateInputPositions(
    const Eigen::Vector3d& start_pos,
    const Eigen::Vector3d& goal_pos)
{
    auto logger = rclcpp::get_logger("CircularConstraintCalculator");
    double chord_length = (goal_pos - start_pos).norm();
    
    if (chord_length < 1e-6) {
        RCLCPP_ERROR(logger, "Start and Goal positions are too close (distance: %.6f)", 
                     chord_length);
        throw std::runtime_error("Start and Goal positions are too close together");
    }
}

geometry_msgs::msg::PoseStamped CircularConstraintCalculator::calculate(
    const NodePtr& node,
    const Pose& current_state,
    const Pose& goal_state)
{
    Eigen::Vector3d start_pos(current_state.pose.position.x,
                              current_state.pose.position.y,
                              current_state.pose.position.z);
    Eigen::Vector3d goal_pos(goal_state.pose.position.x,
                             goal_state.pose.position.y,
                             goal_state.pose.position.z);

    const auto [constraint_pos, perp] = computeConstraintGeometry(node, start_pos, goal_pos);
    const auto circumcenter_pos = findCircumcenter(start_pos, goal_pos, constraint_pos);

    geometry_msgs::msg::PoseStamped constraint_pose;
    constraint_pose.pose.position.x = circumcenter_pos.x();
    constraint_pose.pose.position.y = circumcenter_pos.y();
    constraint_pose.pose.position.z = circumcenter_pos.z();

    Eigen::Quaterniond orientation = computeConstraintOrientation(start_pos, goal_pos, perp);
    constraint_pose.pose.orientation.w = orientation.w();
    constraint_pose.pose.orientation.x = orientation.x();
    constraint_pose.pose.orientation.y = orientation.y();
    constraint_pose.pose.orientation.z = orientation.z();

    return constraint_pose;
}