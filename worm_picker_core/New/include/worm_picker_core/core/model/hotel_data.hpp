// hotel_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef HOTEL_DATA_HPP
#define HOTEL_DATA_HPP

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

#endif // HOTEL_DATA_HPP
