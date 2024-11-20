// workstation_data.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/common/data_types/workstation_data.hpp"

WorkstationData::WorkstationData(const Coordinate& coordinate)
    : coordinate_(coordinate) {}

const Coordinate& WorkstationData::getCoordinate() const 
{
    return coordinate_;
}
