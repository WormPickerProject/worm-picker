// hotel_data.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/common/data_types/hotel_data.hpp"

HotelData::HotelData(const Coordinate& coordinate)
    : coordinate_(coordinate) {}

const Coordinate& HotelData::getCoordinate() const 
{
    return coordinate_;
}
