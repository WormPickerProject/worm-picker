// move_to_joint_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef MOVE_TO_JOINT_DATA_HPP
#define MOVE_TO_JOINT_DATA_HPP

#include "worm_picker_core/stages/stage_data.hpp"
#include <map>
#include <string>

/**
 * @class MoveToJointData
 * @brief Represents data for a joint MoveTo-based stage.
 */
class MoveToJointData : public StageData 
{
public:
    /**
     * @brief Default constructor.
     */
    MoveToJointData() = default;

    /**
     * @brief Constructs a MoveToJointData with the given joint angles and scaling factors.
     * @param joint1 Angle for joint 1 in degrees.
     * @param joint2 Angle for joint 2 in degrees.
     * @param joint3 Angle for joint 3 in degrees.
     * @param joint4 Angle for joint 4 in degrees.
     * @param joint5 Angle for joint 5 in degrees.
     * @param joint6 Angle for joint 6 in degrees.
     * @param velocity_scaling Velocity scaling factor (default: 0.1).
     * @param acceleration_scaling Acceleration scaling factor (default: 0.1).
     */
    MoveToJointData(double joint1, double joint2, double joint3, 
                    double joint4, double joint5, double joint6,
                    double velocity_scaling = 0.1, double acceleration_scaling = 0.1);
    
    /**
     * @brief Creates a MoveIt stage based on the data.
     * @param name The name of the stage.
     * @param node Shared pointer to the ROS2 node.
     * 
     * @return A unique pointer to the created stage.
     */
    std::unique_ptr<moveit::task_constructor::Stage> createStage(const std::string& name,
                                                                 const rclcpp::Node::SharedPtr& node) const override;

    StageType getType() const noexcept override;

    const std::map<std::string, double>& getJointPositions() const noexcept;
    double getVelocityScalingFactor() const noexcept;
    double getAccelerationScalingFactor() const noexcept;

private:
    std::map<std::string, double> joint_positions_;  ///< Map of joint names to their positions (in radians).
    double velocity_scaling_factor_;                           ///< Velocity scaling factor.
    double acceleration_scaling_factor_;                       ///< Acceleration scaling factor.
};

#endif // MOVE_TO_JOINT_DATA_HPP
