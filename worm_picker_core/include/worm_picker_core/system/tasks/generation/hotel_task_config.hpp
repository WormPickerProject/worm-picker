// hotel_task_config.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

/// @brief Configuration namespace for workstation task generation parameters and constants
namespace hotel_config {

enum class TaskType {
    PickPlate,
    PlacePlate,
    PickLid,
    PlaceLid,
    MoveToPoint
};

struct MovementParams {
    double horizontal_approach;
    double vertical_motion;
    double horizontal_retreat;
};

namespace motion {
    static constexpr MovementParams PICK {0.064, 0.012, -0.064};
    static constexpr MovementParams PLACE{0.064, -0.012, -0.064};
    static constexpr MovementParams PICK_LID {0.064, 0.025, -0.064};
    static constexpr MovementParams PLACE_LID{0.064, -0.025, -0.064};
}

struct OffsetXYZ {
    double x;
    double y; 
    double z;
};

namespace offset {
    // START: 65 mm in front of and 10 mm below hotel room
    static constexpr OffsetXYZ PICK {-0.065, 0.00, -0.01}; 

    // START: 65 mm in front of and 2 mm above hotel room
    static constexpr OffsetXYZ PLACE{-0.065, 0.00, 0.002};

    // START: 65 mm in front of and 23 mm below hotel room
    static constexpr OffsetXYZ PICK_LID {-0.065, 0.00, -0.023};

    // START: 65 mm in front of and 2 mm above hotel room
    static constexpr OffsetXYZ PLACE_LID{-0.065, 0.00, 0.002};

    static constexpr OffsetXYZ POINT{ 0.000, 0.000, 0.00};
}

namespace prefix {
    static constexpr const char* PICK = "pickPlateHotel:";
    static constexpr const char* PLACE = "placePlateHotel:";
    static constexpr const char* PICK_LID = "pickLidHotel:";
    static constexpr const char* PLACE_LID = "placeLidHotel:";
    static constexpr const char* POINT = "moveToPoint:";
}

} // namespace workstation_config