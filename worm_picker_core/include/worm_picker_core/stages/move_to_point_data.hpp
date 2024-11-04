// move_to_point_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
// Additional Contributions: Fang-Yen Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");

#ifndef MOVE_TO_POINT_DATA_HPP
#define MOVE_TO_POINT_DATA_HPP

#include "worm_picker_core/stages/stage_data.hpp"

/**
 * @class MoveToPointData
 * @brief Represents data for a point MoveTo-based stage.
 */
class MoveToPointData : public StageData 
{
public:
    /**
     * @brief Default constructor.
     */
    MoveToPointData() = default;

    /**
     * @brief Constructs a MoveToPointData with the given parameters.
     * @param px Position x-coordinate.
     * @param py Position y-coordinate.
     * @param pz Position z-coordinate.
     * @param ox Orientation quaternion x-component.
     * @param oy Orientation quaternion y-component.
     * @param oz Orientation quaternion z-component.
     * @param ow Orientation quaternion w-component.
     * @param velocity_scaling Velocity scaling factor (default: 0.1).
     * @param acceleration_scaling Acceleration scaling factor (default: 0.1).
     */
    MoveToPointData(double px, double py, double pz,
                    double ox, double oy, double oz, double ow,
                    double velocity_scaling = 0.1,
                    double acceleration_scaling = 0.1);

    StageType getType() const override;

    double getX() const;
    double getY() const;
    double getZ() const;
    double getQX() const;
    double getQY() const;
    double getQZ() const; 
    double getQW() const;
    double getVelocityScalingFactor() const; 
    double getAccelerationScalingFactor() const;

private:
    double x_;                            ///< Position x-coordinate
    double y_;                            ///< Position y-coordinate
    double z_;                            ///< Position z-coordinate
    double qx_;                           ///< Orientation quaternion x-component
    double qy_;                           ///< Orientation quaternion y-component
    double qz_;                           ///< Orientation quaternion z-component
    double qw_;                           ///< Orientation quaternion w-component
    double velocity_scaling_factor_;      ///< Velocity scaling factor
    double acceleration_scaling_factor_;  ///< Acceleration scaling factor
};

#endif // MOVE_TO_POINT_DATA_HPP
