// move_relative_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef MOVE_RELATIVE_DATA_HPP
#define MOVE_RELATIVE_DATA_HPP

#include "worm_picker_core/stages/stage_data.hpp"

/**
 * @class MoveRelativeData
 * @brief Represents data for a relative move stage.
 */
class MoveRelativeData : public StageData {
public:
    /**
     * @brief Default constructor.
     */
    MoveRelativeData() = default;

    /**
     * @brief Constructs a MoveRelativeData with the given parameters.
     * @param delta_x Position delta x-coordinate.
     * @param delta_y Position delta y-coordinate.
     * @param delta_z Position delta z-coordinate.
     * @param velocity_scaling Velocity scaling factor (default: 0.1).
     * @param acceleration_scaling Acceleration scaling factor (default: 0.1).
     */
    MoveRelativeData(double delta_x, double delta_y, double delta_z,
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

    double getDX() const noexcept;
    double getDY() const noexcept;
    double getDZ() const noexcept;
    double getVelocityScalingFactor() const noexcept;
    double getAccelerationScalingFactor() const noexcept;

private:
    double dx_;                            ///< Position delta x-coordinate
    double dy_;                            ///< Position delta y-coordinate
    double dz_;                            ///< Position delta z-coordinate
    double velocity_scaling_factor_;       ///< Velocity scaling factor
    double acceleration_scaling_factor_;   ///< Acceleration scaling factor

};

#endif // MOVE_RELATIVE_DATA_HPP
