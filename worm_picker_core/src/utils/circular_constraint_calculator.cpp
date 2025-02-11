// circular_constraint_calculator.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/utils/circular_constraint_calculator.hpp"

Eigen::Vector3d 
CircularConstraintCalculator::findRobustReference(const Eigen::Vector3d& chord_direction)
{
    Eigen::Vector3d candidates[3] = {
        Eigen::Vector3d(1, 0, 0),
        Eigen::Vector3d(0, 1, 0),
        Eigen::Vector3d(0, 0, 1)
    };

    double min_alignment = 1.0;
    Eigen::Vector3d best_reference = candidates[0];

    for (const auto& candidate : candidates) {
        double alignment = std::abs(chord_direction.dot(candidate));
        if (alignment < min_alignment) {
            min_alignment = alignment;
            best_reference = candidate;
        }
    }
    return best_reference;
}
  
Eigen::Vector3d CircularConstraintCalculator::computeConsistentPerpendicular(
    const Eigen::Vector3d& chord_direction,
    const Eigen::Vector3d& plane_normal,
    const Eigen::Vector3d& start_pos)
{
    // Compute the perpendicular as the cross product of the plane normal and chord direction.
    Eigen::Vector3d perpendicular = plane_normal.cross(chord_direction);
    perpendicular.normalize();

    // Use a reference direction based on the global up vector.
    Eigen::Vector3d global_up(0, 0, 1);
    Eigen::Vector3d reference_dir = global_up.cross(chord_direction);

    if (reference_dir.norm() < 1e-6) {
        // For near vertical movements, use the horizontal component of start.
        Eigen::Vector3d horizontal_start(start_pos.x(), start_pos.y(), 0);
        if (horizontal_start.norm() > 1e-6) {
            reference_dir = horizontal_start.normalized();
        } else {
            reference_dir = Eigen::Vector3d(1, 0, 0);
        }
    }

    if (perpendicular.dot(reference_dir) < 0) {
        perpendicular = -perpendicular;
    }

    return perpendicular;
}

void CircularConstraintCalculator::computeConstraintPositionAndPerpendicular(
    const NodePtr& node,
    const Eigen::Vector3d& start_pos,
    const Eigen::Vector3d& goal_pos,
    Eigen::Vector3d &constraint_pos,
    Eigen::Vector3d &perpendicular)
{
    // Compute chord vector and its length.
    Eigen::Vector3d chord = goal_pos - start_pos;
    double chord_length = chord.norm();
    if (chord_length < 1e-6) {
        throw std::runtime_error("Start and Goal positions are too close together");
    }
    Eigen::Vector3d chord_direction = chord.normalized();
    
    // Find a robust reference vector.
    Eigen::Vector3d reference_vector = findRobustReference(chord_direction);

    // Compute the plane normal.
    Eigen::Vector3d plane_normal = chord_direction.cross(reference_vector);
    plane_normal.normalize();

    // Compute a consistent perpendicular.
    perpendicular = 
        computeConsistentPerpendicular(chord_direction, plane_normal, start_pos);
    
    // Scale the perpendicular by the chord length.
    const auto scale = *param_utils::getParameter<double>(node, "settings.circ_traj_height_scaler"); 
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
    
    // Compute the midpoint between start and goal.
    Eigen::Vector3d midpoint = (start_pos + goal_pos) / 2.0;
    // Final constraint position is the midpoint offset by the perpendicular.
    constraint_pos = midpoint + perpendicular;
}

Eigen::Quaterniond CircularConstraintCalculator::computeConstraintOrientation(
    const Eigen::Vector3d& start_pos,
    const Eigen::Vector3d& goal_pos,
    const Eigen::Vector3d& perpendicular)
{
    // Determine the movement direction.
    Eigen::Vector3d movement_dir = (goal_pos - start_pos).normalized();
    Eigen::Vector3d up_dir = perpendicular.normalized();
    Eigen::Vector3d right_dir = movement_dir.cross(up_dir);

    // Build the rotation matrix.
    Eigen::Matrix3d rotation;
    rotation.col(0) = right_dir;
    rotation.col(1) = movement_dir;
    rotation.col(2) = up_dir;

    // Convert the rotation matrix to a quaternion.
    Eigen::Quaterniond q(rotation);
    q.normalize();
    return q;
}

Eigen::Vector3d CircularConstraintCalculator::findCircumcenter(
    const Eigen::Vector3d& a, 
    const Eigen::Vector3d& b, 
    const Eigen::Vector3d& c) 
{
    ///////////////////////////
    auto logger = rclcpp::get_logger("TaskFactory");
    RCLCPP_INFO(logger, 
        "Finding circumcenter for triangle with vertices: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)",
        a.x(), a.y(), a.z(), b.x(), b.y(), b.z(), c.x(), c.y(), c.z());
    ///////////////////////////
    // Compute edge vectors
    Eigen::Vector3d ab = b - a;
    Eigen::Vector3d ac = c - a;

    // Compute the normal to the plane of the triangle
    Eigen::Vector3d normal = ab.cross(ac);

    // Compute midpoints
    Eigen::Vector3d midAB = (a + b) / 2.0;
    Eigen::Vector3d midAC = (a + c) / 2.0;

    // Compute perpendicular vectors
    Eigen::Vector3d perpAB = normal.cross(ab);
    Eigen::Vector3d perpAC = normal.cross(ac);

    // Set up the system of equations
    double d1 = perpAB.dot(perpAB);
    double d2 = perpAB.dot(perpAC);
    double d3 = perpAC.dot(perpAC);
    Eigen::Vector3d diff = midAC - midAB;
    double d4 = perpAB.dot(diff);
    double d5 = perpAC.dot(diff);

    // Solve for intersection
    double denom = d1 * d3 - d2 * d2;
    // if (std::abs(denom) < 1e-9) {
    //     throw std::runtime_error("The points are collinear; circumcenter is undefined.");
    // }

    double t = (d4 * d3 - d5 * d2) / denom;

    // Compute circumcenter
    Eigen::Vector3d circumcenter = midAB + t * perpAB;
    return circumcenter;
}

geometry_msgs::msg::PoseStamped CircularConstraintCalculator::calculate(
    const NodePtr& node,
    const Pose& current_state,
    const Pose& goal_state)
{
    // Convert input poses to Eigen vectors.
    Eigen::Vector3d start_pos(
        current_state.pose.position.x,
        current_state.pose.position.y,
        current_state.pose.position.z);
        
    Eigen::Vector3d goal_pos(
        goal_state.pose.position.x,
        goal_state.pose.position.y,
        goal_state.pose.position.z);
    
    // Compute both the final constraint position and the perpendicular offset.
    Eigen::Vector3d constraint_pos;
    Eigen::Vector3d perpendicular;
    computeConstraintPositionAndPerpendicular(
        node, start_pos, goal_pos, constraint_pos, perpendicular);
    
    const auto circumcenter_pos = findCircumcenter(start_pos, goal_pos, constraint_pos);

    // Create the PoseStamped message for the constraint.
    geometry_msgs::msg::PoseStamped constraint_pose;
    constraint_pose.pose.position.x = circumcenter_pos.x();
    constraint_pose.pose.position.y = circumcenter_pos.y();
    constraint_pose.pose.position.z = circumcenter_pos.z();
    // constraint_pose.pose.orientation = current_state.pose.orientation;
    
    // Compute the orientation based on the movement direction and perpendicular offset.
    Eigen::Quaterniond orientation = 
        computeConstraintOrientation(start_pos, goal_pos, perpendicular);
    constraint_pose.pose.orientation.w = orientation.w();
    constraint_pose.pose.orientation.x = orientation.x();
    constraint_pose.pose.orientation.y = orientation.y();
    constraint_pose.pose.orientation.z = orientation.z();

    return constraint_pose;
}