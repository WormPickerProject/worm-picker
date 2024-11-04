// task_generator.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef TASK_GENERATOR_HPP
#define TASK_GENERATOR_HPP

#include "worm_picker_core/tasks/task_data.hpp"
#include "worm_picker_core/stages/move_relative_data.hpp"
#include "worm_picker_core/stages/move_to_joint_data.hpp"
#include "worm_picker_core/stages/move_to_point_data.hpp"
#include "worm_picker_core/tasks/generation/base_task_generator.hpp"
#include "worm_picker_core/tasks/generation/generate_workstation_pick_plate_task.hpp"
#include "worm_picker_core/tasks/generation/generate_workstation_place_plate_task.hpp"
#include "worm_picker_core/tasks/generation/generate_hotel_pick_plate_task.hpp"
#include "worm_picker_core/tasks/generation/generate_hotel_place_plate_task.hpp"

class TaskGenerator
{
public:
    TaskGenerator(const std::unordered_map<std::string, WorkstationData>& workstation_data_map,
                  const std::unordered_map<std::string, HotelData>& hotel_data_map);

    const std::map<std::string, TaskData>& getGeneratedTaskPlans() const;

private:
    std::vector<std::unique_ptr<BaseTaskGenerator>> initializeGenerators(const std::unordered_map<std::string, WorkstationData>& workstation_map,
                                                                         const std::unordered_map<std::string, HotelData>& hotel_map);
    
    void generateAndAggregateTasks(const std::vector<std::unique_ptr<BaseTaskGenerator>>& generators); 

    std::map<std::string, TaskData> task_data_map_;

    // Temporary Functions:
    void logDataMap() const;
};

#endif // TASK_GENERATOR_HPP
