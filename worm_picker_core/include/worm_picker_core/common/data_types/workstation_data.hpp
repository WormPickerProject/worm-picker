// workstation_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef WORKSTATION_DATA_HPP
#define WORKSTATION_DATA_HPP

#include "worm_picker_core/common/data_types/coordinate.hpp"

class WorkstationData {
public:
    WorkstationData() = default;
    explicit WorkstationData(const Coordinate& coordinate);
    const Coordinate& getCoordinate() const;

private:
    Coordinate coordinate_;
};

#endif // WORKSTATION_DATA_HPP