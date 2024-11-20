// generate_hotel_place_plate_task.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef GENERATE_HOTEL_PLACE_PLATE_TASK_HPP
#define GENERATE_HOTEL_PLACE_PLATE_TASK_HPP

#include "worm_picker_core/tasks/generation/base_task_generator.hpp"
#include "worm_picker_core/common/coordinate.hpp"

class GenerateHotelPlacePlateTask : public BaseTaskGenerator
{
public:
    GenerateHotelPlacePlateTask(const std::unordered_map<std::string, HotelData>& hotel_map);

    void generateTasks() override;
    const std::unordered_map<std::string, TaskData>& getTaskDataMap() const override;

private:
    const std::unordered_map<std::string, HotelData>& hotel_data_map_;
    std::unordered_map<std::string, TaskData> task_data_map_;
};

#endif // GENERATE_HOTEL_PLACE_PLATE_TASK_HPP
