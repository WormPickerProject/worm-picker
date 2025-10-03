// workstation_task_config.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

/// @brief Configuration namespace for workstation task generation parameters and constants
namespace workstation_config {

enum class TaskType {
    PickPlate,
    PlacePlate,
    HoverWormPick,
    MoveToPoint
};

struct OffsetXYZ {
    double x;
    double y; 
    double z;
};

namespace offset {
    static constexpr OffsetXYZ PICK {-0.045, 0.000, 0.0175};
    static constexpr OffsetXYZ PLACE{ 0.000, 0.000, 0.0175};
    static constexpr OffsetXYZ HOVER{ 0.000, 0.000, 0.0440};
    static constexpr OffsetXYZ POINT{ 0.000, 0.000, 0.0100};
}

struct MovementParams {
    double vertical_approach;
    double horizontal_motion;
    double vertical_retreat;
};

namespace motion {
    //static constexpr MovementParams PICK{ -0.03,  0.045, 0.03};
    static constexpr MovementParams PICK{ -0.025, 0.045, 0.025}; // {dig amount, sliding amount, raiseamount} Testing with compact WP2
    //static constexpr MovementParams PLACE{-0.03, -0.045, 0.03};
    static constexpr MovementParams PLACE{-0.025, -0.045, 0.025}; // Testing with compact WP2
}

namespace prefix {
    static constexpr const char* PICK = "pickPlateWorkStation:";
    static constexpr const char* PLACE = "placePlateWorkStation:";
    static constexpr const char* HOVER = "hoverWormPick:";
    static constexpr const char* POINT = "moveToPoint:";
}

namespace angle {
    static constexpr double PI = 3.14159265358979323846;
    static constexpr double THETA_STEP_RAD = 7.6 * PI / 180.0; // Adjusted for compact WP2
    static constexpr char REFERENCE_ROW = 'C'; // Adjusted for compact WP2
    static constexpr double REFERENCE_THETA_RAD = -40.6 * PI / 180.0; // The theta angle (rad) for the reference row
}

} // namespace workstation_config