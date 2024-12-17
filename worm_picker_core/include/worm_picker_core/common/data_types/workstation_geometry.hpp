// worstation_geometry.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef WORKSTATION_GEOMETRY_HPP
#define WORKSTATION_GEOMETRY_HPP

#include <vector>
#include "worm_picker_core/common/data_types/fixed_point.hpp"

struct WorkstationGeometry {
    double ray_separation_angle;
    std::vector<FixedPoint> fixed_points;
};

#endif // WORKSTATION_GEOMETRY_HPP