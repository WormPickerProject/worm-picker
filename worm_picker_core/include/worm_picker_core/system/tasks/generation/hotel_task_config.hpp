// hotel_task_config.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

/// @brief Configuration namespace for workstation task generation parameters and constants
namespace hotel_config {

enum class TaskType {
    PickPlate,
    PlacePlate
};

namespace prefix {
    static constexpr const char* PICK = "pickPlateHotel:";
    static constexpr const char* PLACE = "placePlateHotel:";
}

} // namespace workstation_config