// circular_constraint_calculator.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/utils/circular_constraint_calculator.hpp"

Eigen::Vector3d 
CircularConstraintCalculator::findRobustReference(const Eigen::Vector3d& chord_direction)
{
    auto logger = rclcpp::get_logger("findRobustReference");
    RCLCPP_INFO(logger, "Chord direction: [%.3f, %.3f, %.3f]", 
                chord_direction.x(), chord_direction.y(), chord_direction.z());

    Eigen::Vector3d candidates[3] = {
        Eigen::Vector3d(1, 0, 0),
        Eigen::Vector3d(0, 1, 0),
        Eigen::Vector3d(0, 0, 1)
    };

    double min_alignment = 1.0;
    Eigen::Vector3d best_reference = candidates[0];

    for (const auto& candidate : candidates) {
        double alignment = std::abs(chord_direction.dot(candidate));
        if (alignment < min_alignment + 1e-2) {
            // Prefer Z axis over Y axis over X axis
            if (candidate.z() > best_reference.z() ||
                (candidate.z() == best_reference.z() && candidate.y() > best_reference.y())) {
                min_alignment = alignment;
                best_reference = candidate;
            }
        }
    }

    RCLCPP_INFO(logger, "Selected reference: [%.3f, %.3f, %.3f]", 
        best_reference.x(), best_reference.y(), best_reference.z());

    return best_reference;
}
  
// Eigen::Vector3d CircularConstraintCalculator::computeConsistentPerpendicular(
//     const Eigen::Vector3d& chord_direction,
//     const Eigen::Vector3d& plane_normal,
//     const Eigen::Vector3d& start_pos)
// {
//     // Compute the perpendicular as the cross product of the plane normal and chord direction.
//     Eigen::Vector3d perpendicular = plane_normal.cross(chord_direction);
//     perpendicular.normalize();

//     // Use a reference direction based on the global up vector.
//     Eigen::Vector3d global_up(0, 0, 1);
//     Eigen::Vector3d reference_dir = global_up.cross(chord_direction);
//     Eigen::Vector3d neg_reference_dir = global_up.cross(-chord_direction);

//     ///////////////////////////
//     auto logger = rclcpp::get_logger("TaskFactory");
//     RCLCPP_INFO(logger, "Reference direction: (%f, %f, %f)", 
//         reference_dir.x(), reference_dir.y(), reference_dir.z());
//     RCLCPP_INFO(logger, "Negative reference direction: (%f, %f, %f)",
//         neg_reference_dir.x(), neg_reference_dir.y(), neg_reference_dir.z());
//     ///////////////////////////

//     if (reference_dir.norm() < 1e-6) {
//         // For near vertical movements, use the horizontal component of start.
//         Eigen::Vector3d horizontal_start(start_pos.x(), start_pos.y(), 0);
//         if (horizontal_start.norm() > 1e-6) {
//             reference_dir = horizontal_start.normalized();
//         } else {
//             reference_dir = Eigen::Vector3d(1, 0, 0);
//         }
//     }

//     if (perpendicular.dot(reference_dir) < 0) {
//         perpendicular = -perpendicular;
//     }

//     return perpendicular;
// }

Eigen::Vector3d CircularConstraintCalculator::computeConsistentPerpendicular(
    const Eigen::Vector3d& chord_direction,
    const Eigen::Vector3d& plane_normal,
    const Eigen::Vector3d& start_pos)
{
    auto logger = rclcpp::get_logger("computeConsistentPerpendicular");
    RCLCPP_INFO(logger, "Input vectors:");
    RCLCPP_INFO(logger, "  chord_direction: [%.6f, %.6f, %.6f]", 
                chord_direction.x(), chord_direction.y(), chord_direction.z());
    RCLCPP_INFO(logger, "  plane_normal: [%.6f, %.6f, %.6f]", 
                plane_normal.x(), plane_normal.y(), plane_normal.z());
    RCLCPP_INFO(logger, "  start_pos: [%.6f, %.6f, %.6f]", 
                start_pos.x(), start_pos.y(), start_pos.z());

    const double EPSILON = 1e-10;

    // Ensure input vectors are properly normalized
    Eigen::Vector3d chord_dir = chord_direction;
    Eigen::Vector3d plane_norm = plane_normal;
    
    if (std::abs(chord_dir.norm() - 1.0) > EPSILON) {
        RCLCPP_INFO(logger, "Normalizing chord_dir (norm: %.6f)", chord_dir.norm());
        chord_dir.normalize();
    }
    if (std::abs(plane_norm.norm() - 1.0) > EPSILON) {
        RCLCPP_INFO(logger, "Normalizing plane_norm (norm: %.6f)", plane_norm.norm());
        plane_norm.normalize();
    }

    // Compute initial perpendicular
    Eigen::Vector3d perpendicular = plane_norm.cross(chord_dir);
    RCLCPP_INFO(logger, "Initial perpendicular: [%.6f, %.6f, %.6f]", 
                perpendicular.x(), perpendicular.y(), perpendicular.z());
    
    // Check if perpendicular is well-defined
    double perp_norm = perpendicular.norm();
    RCLCPP_INFO(logger, "Perpendicular norm: %.6f", perp_norm);

    if (perp_norm < EPSILON) {
        RCLCPP_INFO(logger, "Vectors nearly parallel, using fallback");
        Eigen::Vector3d global_up(0, 0, 1);
        double up_alignment = std::abs(chord_dir.dot(global_up));
        RCLCPP_INFO(logger, "Up alignment: %.6f", up_alignment);
        
        if (up_alignment > 1.0 - EPSILON) {
            RCLCPP_INFO(logger, "Nearly vertical, using X axis as reference");
            perpendicular = Eigen::Vector3d(1, 0, 0);
        } else {
            RCLCPP_INFO(logger, "Using cross product with global up");
            perpendicular = global_up.cross(chord_dir);
            perpendicular.normalize();
        }
    } else {
        perpendicular /= perp_norm;
    }

    RCLCPP_INFO(logger, "Perpendicular after normalization: [%.6f, %.6f, %.6f]", 
                perpendicular.x(), perpendicular.y(), perpendicular.z());

    // Ensure consistent orientation
    Eigen::Vector3d global_up(0, 0, 1);
    double z_component = perpendicular.z();
    RCLCPP_INFO(logger, "Z component: %.6f", z_component);
    
    if (std::abs(z_component) < EPSILON) {
        RCLCPP_INFO(logger, "Perpendicular is horizontal, using start position as reference");
        Eigen::Vector3d start_horizontal(start_pos.x(), start_pos.y(), 0);
        if (start_horizontal.norm() > EPSILON) {
            if (perpendicular.dot(start_horizontal) < 0) {
                RCLCPP_INFO(logger, "Flipping perpendicular based on start position");
                perpendicular = -perpendicular;
            }
        }
    } else if (z_component < 0) {
        RCLCPP_INFO(logger, "Flipping perpendicular due to negative Z");
        perpendicular = -perpendicular;
    }

    RCLCPP_INFO(logger, "Final perpendicular: [%.6f, %.6f, %.6f]", 
                perpendicular.x(), perpendicular.y(), perpendicular.z());

    // Final sanity check
    assert(std::abs(perpendicular.norm() - 1.0) < EPSILON);
    assert(std::abs(perpendicular.dot(chord_dir)) < EPSILON);

    return perpendicular;
}

void CircularConstraintCalculator::computeConstraintPositionAndPerpendicular(
    const NodePtr& node,
    const Eigen::Vector3d& start_pos,
    const Eigen::Vector3d& goal_pos,
    Eigen::Vector3d &constraint_pos,
    Eigen::Vector3d &perpendicular)
{
    auto logger = rclcpp::get_logger("computeConstraintPosition");
    RCLCPP_INFO(logger, "Computing constraint for movement:");
    RCLCPP_INFO(logger, "  Start: [%.3f, %.3f, %.3f]", 
                start_pos.x(), start_pos.y(), start_pos.z());
    RCLCPP_INFO(logger, "  Goal:  [%.3f, %.3f, %.3f]", 
                goal_pos.x(), goal_pos.y(), goal_pos.z());

    // Compute chord vector and its length
    Eigen::Vector3d chord = goal_pos - start_pos;
    double chord_length = chord.norm();
    if (chord_length < 1e-6) {
        RCLCPP_ERROR(logger, "Start and Goal positions are too close together (distance: %.6f)", 
                     chord_length);
        throw std::runtime_error("Start and Goal positions are too close together");
    }

    Eigen::Vector3d chord_direction = chord.normalized();
    RCLCPP_INFO(logger, "Chord direction: [%.3f, %.3f, %.3f] (length: %.3f)", 
                chord_direction.x(), chord_direction.y(), chord_direction.z(), chord_length);
    
    // Find a robust reference vector
    Eigen::Vector3d reference_vector = findRobustReference(chord_direction);
    RCLCPP_INFO(logger, "Reference vector: [%.3f, %.3f, %.3f]", 
                reference_vector.x(), reference_vector.y(), reference_vector.z());

    // Compute the plane normal
    Eigen::Vector3d plane_normal = chord_direction.cross(reference_vector);
    plane_normal.normalize();
    RCLCPP_INFO(logger, "Plane normal: [%.3f, %.3f, %.3f]", 
                plane_normal.x(), plane_normal.y(), plane_normal.z());

    // Compute a consistent perpendicular
    perpendicular = computeConsistentPerpendicular(chord_direction, plane_normal, start_pos);
    RCLCPP_INFO(logger, "Initial perpendicular: [%.3f, %.3f, %.3f]", 
                perpendicular.x(), perpendicular.y(), perpendicular.z());
    
    // Scale the perpendicular by the chord length
    const auto scale = *param_utils::getParameter<double>(node, "settings.circ_traj_height_scaler"); 
    perpendicular *= (chord_length * scale / 2.0);
    RCLCPP_INFO(logger, "Scaled perpendicular (scale: %.3f): [%.3f, %.3f, %.3f]", 
                scale, perpendicular.x(), perpendicular.y(), perpendicular.z());

    // Special handling for near-vertical movements
    Eigen::Vector3d vertical_dir(0, 0, 1);
    if (chord_direction.isApprox(vertical_dir, 1e-6) ||
        chord_direction.isApprox(-vertical_dir, 1e-6)) {
        RCLCPP_INFO(logger, "Detected near-vertical movement");
        
        Eigen::Vector3d horizontal_start(start_pos.x(), start_pos.y(), 0);
        double horiz_norm = horizontal_start.norm();
        RCLCPP_INFO(logger, "Horizontal start norm: %.6f", horiz_norm);
        
        if (horiz_norm > 1e-6) {
            RCLCPP_INFO(logger, "Using horizontal start direction");
            perpendicular = horizontal_start.normalized() * (chord_length * scale / 2.0);
        } else {
            RCLCPP_INFO(logger, "Using default X-axis direction");
            perpendicular = Eigen::Vector3d(1, 0, 0) * (chord_length * scale / 2.0);
        }
        RCLCPP_INFO(logger, "Adjusted perpendicular: [%.3f, %.3f, %.3f]", 
                    perpendicular.x(), perpendicular.y(), perpendicular.z());
    }
    
    // Compute the midpoint and final constraint position
    Eigen::Vector3d midpoint = (start_pos + goal_pos) / 2.0;
    constraint_pos = midpoint + perpendicular;
    
    RCLCPP_INFO(logger, "Final positions:");
    RCLCPP_INFO(logger, "  Midpoint: [%.3f, %.3f, %.3f]", 
                midpoint.x(), midpoint.y(), midpoint.z());
    RCLCPP_INFO(logger, "  Constraint: [%.3f, %.3f, %.3f]", 
                constraint_pos.x(), constraint_pos.y(), constraint_pos.z());
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