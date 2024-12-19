// workstation_geometry.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef WORKSTATION_GEOMETRY_HPP
#define WORKSTATION_GEOMETRY_HPP

#include <vector>
#include "worm_picker_core/core/geometry/fixed_point.hpp"

class WorkstationGeometry {
public:
    WorkstationGeometry() = default;
    
    WorkstationGeometry(double angle, const std::vector<FixedPoint>& points)
        : ray_separation_angle_(angle), fixed_points_(points) {}
    
    double getRaySeparationAngle() const { return ray_separation_angle_; }
    const std::vector<FixedPoint>& getFixedPoints() const { return fixed_points_; }

    void setRaySeparationAngle(double angle) { ray_separation_angle_ = angle; }
    void setFixedPoints(const std::vector<FixedPoint>& points) { fixed_points_ = points; }

private:
    double ray_separation_angle_{};
    std::vector<FixedPoint> fixed_points_{};
};

#endif // WORKSTATION_GEOMETRY_HPP
