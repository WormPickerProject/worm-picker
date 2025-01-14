// workstation_task_config.hpp
//
// Copyright (c)
// SPDX-License-Identifier: Apache-2.0

#ifndef WORKSTATION_TASK_CONFIG_HPP
#define WORKSTATION_TASK_CONFIG_HPP

/// @brief Configuration namespace for workstation task generation parameters and constants
namespace workstation_config {

/// @brief Types of tasks that can be performed at a workstation
enum class TaskType {
    /// @brief Task to pick up a plate from workstation
    PickPlate,
    /// @brief Task to place a plate at workstation
    PlacePlate,
    /// @brief Task to hover worm pick over workstation
    HoverWormPick,
    /// @brief Task to move to a specific point at workstation
    MoveToPoint
};

/// @brief Parameters defining a sequence of movements for task execution
struct MovementParams {
    /// @brief Distance to move vertically when approaching (meters)
    double vertical_approach;
    /// @brief Distance to move horizontally during task (meters)
    double horizontal_motion;
    /// @brief Distance to move vertically when retreating (meters)
    double vertical_retreat;
};

/// @brief Offset parameters for position calculations
struct PositionOffset {
    /// @brief Offset in the XY plane (meters)
    double xy;
    /// @brief Offset in the Z direction (meters)
    double z;
};

/// @brief Motion parameters for different task types
namespace motion {
    static constexpr MovementParams PICK{-0.025, 0.045, 0.025};
    static constexpr MovementParams PLACE{-0.025, -0.045, 0.025};
}

/// @brief Position offsets for different task types
namespace offset {
    static constexpr PositionOffset PICK{-0.045, 0.0125};
    static constexpr PositionOffset PLACE{0.0, 0.0125};
    static constexpr PositionOffset HOVER{0.035, 0.022};
    static constexpr PositionOffset POINT{0.0, 0.01};
}

/// @brief Task name prefixes for different task types
namespace prefix {
    static constexpr const char* PICK = "pickPlateWorkStation:";
    static constexpr const char* PLACE = "placePlateWorkStation:";
    static constexpr const char* HOVER = "hoverWormPick:";
    static constexpr const char* POINT = "moveToPoint:";
}

/// @brief Angular calculations and reference points
namespace angle {
    static constexpr double PI = 3.14159265358979323846;
    static constexpr double THETA_STEP_RAD = 8.4274 * PI / 180.0;
    static constexpr char REFERENCE_ROW = 'G';
}

} // namespace workstation_config

#endif // WORKSTATION_TASK_CONFIG_HPP