// workstation_task_config.hpp
//
// Copyright (c)
// SPDX-License-Identifier: Apache-2.0

#ifndef WORKSTATION_TASK_CONFIG_HPP
#define WORKSTATION_TASK_CONFIG_HPP

/// @brief Configuration namespace for workstation task generation parameters and constants
namespace workstation_config {

enum class TaskType {
    PickPlate,
    PlacePlate,
    HoverWormPick,
    MoveToPoint
};

struct PositionOffset {
    double xy;
    double z;
};

namespace offset {
    static constexpr PositionOffset PICK{ -0.045, 0.0125};
    static constexpr PositionOffset PLACE{ 0.000, 0.0125};
    static constexpr PositionOffset HOVER{ 0.035, 0.0220};
    static constexpr PositionOffset POINT{ 0.000, 0.0100};
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

#endif // WORKSTATION_TASK_CONFIG_HPP