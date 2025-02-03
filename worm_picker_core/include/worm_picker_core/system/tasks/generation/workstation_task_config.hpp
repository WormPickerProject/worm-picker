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

struct OffsetPosition {
    double xy;
    double z;
};

struct OffsetXYZ {
    double x;
    double y; 
    double z;
};

struct CombinedOffset {
    OffsetPosition position;
    OffsetXYZ xyz;
};

namespace offset {
    static constexpr CombinedOffset PICK{ 
        OffsetPosition{-0.045, 0.0125},
        OffsetXYZ{0, 0, 0}
    };
    static constexpr CombinedOffset PLACE{
        OffsetPosition{0.000, 0.0125},
        OffsetXYZ{0, 0, 0}
    };
    static constexpr CombinedOffset HOVER{
        OffsetPosition{0.015, 0.023},
        OffsetXYZ{0, 0.01, 0}
    };
    static constexpr CombinedOffset POINT{
        OffsetPosition{0.000, 0.0100},
        OffsetXYZ{0, 0, 0}
    };
}

struct MovementParams {
    double vertical_approach;
    double horizontal_motion;
    double vertical_retreat;
};

namespace motion {
    static constexpr MovementParams PICK{ -0.025,  0.045, 0.025};
    static constexpr MovementParams PLACE{-0.025, -0.045, 0.025};
}

namespace prefix {
    static constexpr const char* PICK = "pickPlateWorkStation:";
    static constexpr const char* PLACE = "placePlateWorkStation:";
    static constexpr const char* HOVER = "hoverWormPick:";
    static constexpr const char* POINT = "moveToPoint:";
}

namespace angle {
    static constexpr double PI = 3.14159265358979323846;
    static constexpr double THETA_STEP_RAD = 8.4274 * PI / 180.0;
    static constexpr char REFERENCE_ROW = 'G';
}

} // namespace workstation_config