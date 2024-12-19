// hotel_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef HOTEL_DATA_HPP
#define HOTEL_DATA_HPP

#include "worm_picker_core/common/data_types/coordinate.hpp"

class HotelData {
public:
    HotelData() = default;
    explicit HotelData(const Coordinate& coordinate);
    const Coordinate& getCoordinate() const;

private:
    Coordinate coordinate_;
};

#endif // HOTEL_DATA_HPP
