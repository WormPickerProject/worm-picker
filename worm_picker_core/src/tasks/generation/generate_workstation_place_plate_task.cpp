// generate_workstation_place_plate_task.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tasks/generation/generate_workstation_place_plate_task.hpp"

GenerateWorkstationPlacePlateTask::GenerateWorkstationPlacePlateTask(const std::unordered_map<std::string, WorkstationData>& workstation_map)
    : workstation_data_map_(workstation_map)
{
}

void GenerateWorkstationPlacePlateTask::generateTasks()
{
    // Implement task generation logic for workstation pick plate tasks
}

const std::map<std::string, TaskData>& GenerateWorkstationPlacePlateTask::getTaskDataMap() const
{
    return task_data_map_;
}
