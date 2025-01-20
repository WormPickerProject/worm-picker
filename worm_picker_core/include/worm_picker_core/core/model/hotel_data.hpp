// hotel_data.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "worm_picker_core/core/geometry/coordinate.hpp"

class HotelData {
public:
    HotelData() = default;
    
    constexpr explicit HotelData(const Coordinate& coordinate) 
        : coordinate_(coordinate) {}

    constexpr const Coordinate& getCoordinate() const { return coordinate_; }
    constexpr void setCoordinate(const Coordinate& coordinate) { coordinate_ = coordinate; }

private:
    Coordinate coordinate_{};
};