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
    static constexpr OffsetXYZ POSITION_OFFSET {-0.15, 0.00, 0.00}; 
}

namespace prefix {
    static constexpr const char* WORKSTATION_TO_HOTEL = "workStationToHotel:";
    static constexpr const char* HOTEL_TO_WORKSTATION = "hotelToWorkStation:";
}

namespace rooms {
    static constexpr int TARGET_ROOM = 17;
    static constexpr int HOTEL_ROOM_DIVISOR = 100;
}

namespace joint_1 {
    static constexpr double TO_WORKSTATION = 0.0;
}

} // namespace transfer_task_config