// workstation_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef WORKSTATION_DATA_HPP
#define WORKSTATION_DATA_HPP

#include "worm_picker_core/core/geometry/coordinate.hpp"

class WorkstationData {
public:
    WorkstationData() = default;
    
    constexpr explicit WorkstationData(const Coordinate& coordinate) 
        : coordinate_(coordinate) {}

    constexpr const Coordinate& getCoordinate() const { return coordinate_; }
    constexpr void setCoordinate(const Coordinate& coordinate) { coordinate_ = coordinate; }

private:
    Coordinate coordinate_{};
};

#endif // WORKSTATION_DATA_HPP
