// robot_utilities.cpp

#include "worm_picker_core/tools/robot_utilities.hpp"
#include <vector> 
#include <stdexcept>

/** 
 * @brief This does a thing. 
 */
bool isAtPosition(const StageData& current_position, const StageData& target_position, double tolerance)
{
    if (current_position.getType() != target_position.getType()) {
        throw std::runtime_error("Error: Current and target positions are of different types.");
    }

    if (const MoveToJointData* current_joint_data = dynamic_cast<const MoveToJointData*>(&current_position)) {
        const MoveToJointData* target_joint_data = dynamic_cast<const MoveToJointData*>(&target_position);
        // Check joint positions
        for (const auto& [joint_name, target_value] : target_joint_data->joint_positions) {
            if (std::abs(current_joint_data->joint_positions.at(joint_name) - target_value) > tolerance) {
                return false; // Position exceeds tolerance
            }
        }
        return true;
    } 
    else {
        const MoveToPointData* current_point_data = dynamic_cast<const MoveToPointData*>(&current_position);
        const MoveToPointData* target_point_data = dynamic_cast<const MoveToPointData*>(&target_position);
        
        // Check point positions
        return (std::abs(current_point_data->x - target_point_data->x) <= tolerance &&
                std::abs(current_point_data->y - target_point_data->y) <= tolerance &&
                std::abs(current_point_data->z - target_point_data->z) <= tolerance &&
                std::abs(current_point_data->qx - target_point_data->qx) <= tolerance &&
                std::abs(current_point_data->qy - target_point_data->qy) <= tolerance &&
                std::abs(current_point_data->qz - target_point_data->qz) <= tolerance &&
                std::abs(current_point_data->qw - target_point_data->qw) <= tolerance);
    }
}