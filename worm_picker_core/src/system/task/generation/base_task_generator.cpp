// base_task_generator.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/system/tasks/generation/base_task_generator.hpp"

void BaseTaskGenerator::generateTasks() 
{
    for (const auto& name : getDataMapKeys()) {
        auto [row_letter, col_number] = parseName(name);
        std::string task_name = generateTaskName(row_letter, col_number);
        auto stages = createStagesForTaskImpl(name, row_letter);
        auto task_data = TaskData(std::move(stages));
        task_data_map_.emplace(std::move(task_name), std::move(task_data));
    }
}

const std::unordered_map<std::string, TaskData>& BaseTaskGenerator::getTaskDataMap() const 
{
    return task_data_map_;
}
