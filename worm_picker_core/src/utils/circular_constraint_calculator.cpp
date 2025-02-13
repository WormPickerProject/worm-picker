// circular_constraint_calculator.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/utils/circular_constraint_calculator.hpp"

Eigen::Vector3d CircularConstraintCalculator::findRobustReference(
    const Eigen::Vector3d& chord_direction)
{
    const Eigen::Vector3d candidates[3] = {
        Eigen::Vector3d(1, 0, 0),
        Eigen::Vector3d(0, 1, 0),
        Eigen::Vector3d(0, 0, 1)
    };

    double min_alignment = 1.0;
    Eigen::Vector3d best_reference = candidates[0];

    for (const auto& candidate : candidates) {
        double alignment = std::abs(chord_direction.dot(candidate));
        // When nearly equal, prefer candidate with priority: Z > Y > X.
        if (alignment < min_alignment + 1e-2) {
            if (candidate.z() > best_reference.z() ||
                (candidate.z() == best_reference.z() && candidate.y() > best_reference.y())) {
                min_alignment = alignment;
                best_reference = candidate;
            }
        }
    }

    auto logger = rclcpp::get_logger("CircularConstraintCalculator");
    RCLCPP_DEBUG(logger, "Selected robust reference: [%.3f, %.3f, %.3f]",
                 best_reference.x(), best_reference.y(), best_reference.z());
    return best_reference;
}

Eigen::Vector3d CircularConstraintCalculator::computeConsistentPerpendicular(
    const Eigen::Vector3d &chord_direction,
    const Eigen::Vector3d &plane_normal,
    const Eigen::Vector3d &start_pos)
{
    const double EPSILON = 1e-10;

    Eigen::Vector3d chord_dir = chord_direction.normalized();
    Eigen::Vector3d plane_norm = plane_normal.normalized();

    Eigen::Vector3d initial_perpendicular = 
        computeInitialPerpendicular(chord_dir, plane_norm, EPSILON);

    Eigen::Vector3d final_perpendicular = 
        adjustPerpendicularOrientation(initial_perpendicular, start_pos, EPSILON);

    assert(std::abs(final_perpendicular.norm() - 1.0) < EPSILON);
    assert(std::abs(final_perpendicular.dot(chord_dir)) < EPSILON);
    return final_perpendicular;
}

Eigen::Vector3d CircularConstraintCalculator::computeInitialPerpendicular(
    const Eigen::Vector3d &chord_dir,
    const Eigen::Vector3d &plane_norm,
    const double epsilon)
{
    // Compute the perpendicular as the cross product of the plane normal and chord direction.
    Eigen::Vector3d perpendicular = plane_norm.cross(chord_dir);
    double perp_norm = perpendicular.norm();
    if (perp_norm < epsilon) {
        // Fallback for nearly parallel vectors.
        Eigen::Vector3d global_up(0, 0, 1);
        if (std::abs(chord_dir.dot(global_up)) > 1.0 - epsilon) {
            perpendicular = Eigen::Vector3d(1, 0, 0);
        } else {
            perpendicular = global_up.cross(chord_dir);
            perpendicular.normalize();
        }
    } else {
        perpendicular /= perp_norm;
    }
    return perpendicular;
}

Eigen::Vector3d CircularConstraintCalculator::adjustPerpendicularOrientation(
    const Eigen::Vector3d& perpendicular,
    const Eigen::Vector3d& start_pos,
    const double epsilon)
{
    Eigen::Vector3d adjusted = perpendicular;

    // If the perpendicular is nearly horizontal, use the start position's 
    // horizontal component for reference.
    if (std::abs(adjusted.z()) < epsilon) {
        Eigen::Vector3d start_horizontal(start_pos.x(), start_pos.y(), 0);
        if (start_horizontal.norm() > epsilon && (adjusted.dot(start_horizontal) < 0)) {
            adjusted = -adjusted;
        }
    } else if (adjusted.z() < 0) {
        adjusted = -adjusted;
    }

    return adjusted;
}

void CircularConstraintCalculator::computeConstraintPositionAndPerpendicular(
    const NodePtr& node,
    const Eigen::Vector3d& start_pos,
    const Eigen::Vector3d& goal_pos,
    Eigen::Vector3d& constraint_pos,
    Eigen::Vector3d& perpendicular)
{
    auto logger = rclcpp::get_logger("CircularConstraintCalculator");

    Eigen::Vector3d chord = goal_pos - start_pos;
    double chord_length = chord.norm();
    if (chord_length < 1e-6) {
        RCLCPP_ERROR(logger, "Start and Goal positions are too close together (distance: %.6f)", 
                     chord_length);
        throw std::runtime_error("Start and Goal positions are too close together");
    }

    Eigen::Vector3d chord_direction = chord.normalized();

    // Compute the robust reference and plane normal.
    Eigen::Vector3d reference_vector = findRobustReference(chord_direction);
    Eigen::Vector3d plane_normal = chord_direction.cross(reference_vector);
    plane_normal.normalize();

    perpendicular = computeConsistentPerpendicular(chord_direction, plane_normal, start_pos);

    // Retrieve the scaling factor.
    const double scale = *param_utils::getParameter<double>(node, "settings.circ_traj_height_scaler");
    perpendicular *= (chord_length * scale / 2.0);

    // Special handling for near-vertical movements.
    Eigen::Vector3d vertical_dir(0, 0, 1);
    if (chord_direction.isApprox(vertical_dir, 1e-6) ||
        chord_direction.isApprox(-vertical_dir, 1e-6)) {
        Eigen::Vector3d horizontal_start(start_pos.x(), start_pos.y(), 0);
        if (horizontal_start.norm() > 1e-6) {
            perpendicular = horizontal_start.normalized() * (chord_length * scale / 2.0);
        } else {
            perpendicular = Eigen::Vector3d(1, 0, 0) * (chord_length * scale / 2.0);
        }
    }

    // Compute the final constraint position.
    Eigen::Vector3d midpoint = (start_pos + goal_pos) / 2.0;
    constraint_pos = midpoint + perpendicular;
}

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
    // Compute edge vectors and the normal of the triangle.
    Eigen::Vector3d ab = b - a;
    Eigen::Vector3d ac = c - a;
    Eigen::Vector3d normal = ab.cross(ac);

    // Midpoints of AB and AC.
    Eigen::Vector3d midAB = (a + b) / 2.0;
    Eigen::Vector3d midAC = (a + c) / 2.0;

    // Compute perpendicular directions.
    Eigen::Vector3d perpAB = normal.cross(ab);
    Eigen::Vector3d perpAC = normal.cross(ac);

    double d1 = perpAB.dot(perpAB);
    double d2 = perpAB.dot(perpAC);
    double d3 = perpAC.dot(perpAC);
    Eigen::Vector3d diff = midAC - midAB;
    double d4 = perpAB.dot(diff);
    double d5 = perpAC.dot(diff);

    double denom = d1 * d3 - d2 * d2;
    double t = (d4 * d3 - d5 * d2) / denom;

    Eigen::Vector3d circumcenter = midAB + t * perpAB;
    return circumcenter;
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

    Eigen::Vector3d constraint_pos, perpendicular;
    computeConstraintPositionAndPerpendicular(
        node, start_pos, goal_pos, constraint_pos, perpendicular
    );

    Eigen::Vector3d circumcenter_pos = findCircumcenter(start_pos, goal_pos, constraint_pos);

    geometry_msgs::msg::PoseStamped constraint_pose;
    constraint_pose.pose.position.x = circumcenter_pos.x();
    constraint_pose.pose.position.y = circumcenter_pos.y();
    constraint_pose.pose.position.z = circumcenter_pos.z();

    Eigen::Quaterniond orientation = computeConstraintOrientation(
        start_pos, goal_pos, perpendicular
    );
    constraint_pose.pose.orientation.w = orientation.w();
    constraint_pose.pose.orientation.x = orientation.x();
    constraint_pose.pose.orientation.y = orientation.y();
    constraint_pose.pose.orientation.z = orientation.z();

    return constraint_pose;
}