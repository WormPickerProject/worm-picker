// transfer_task_config.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

namespace transfer_config {

enum class TaskType {
    ToHotel,
    ToWorkstation
};

struct OffsetXYZ {
    double x;
    double y; 
    double z;
};

namespace offset {
    static constexpr OffsetXYZ POSITION_OFFSET {-0.10, 0.00, 0.00}; 
}

namespace prefix {
    static constexpr const char* WORKSTATION_TO_HOTEL = "workStationToHotel:";
    static constexpr const char* HOTEL_TO_WORKSTATION = "hotelToWorkStation:";
    static constexpr const char* HOTEL_TO_HOTEL = "hotelToHotel:";
}

namespace rooms {
    static constexpr int TARGET_ROOM = 17;
    static constexpr int HOTEL_ROOM_DIVISOR = 100;
}

namespace joint_1 {
    //static constexpr double TO_WORKSTATION = 0.0;
    static constexpr double PI = 3.14159265358979323846;
    static constexpr double TO_WORKSTATION = -40.6 * PI / 180.0; // -40.6 deg in radiance Testing with compact WP2
    static constexpr double TO_WORKSTATION_deg = -40.6; // -40.6 deg in degrees
}

} // namespace transfer_task_config