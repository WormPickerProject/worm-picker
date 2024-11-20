// base_task_generator.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tasks/generation/base_task_generator.hpp"

void BaseTaskGenerator::generateTasks() 
{
    for (const auto& name : getDataMapKeys()) {
        auto [row_letter, col_number] = parseName(name);
        std::string task_name = generateTaskName(row_letter, col_number);
        auto stages = createStagesForTaskImpl(name, row_letter);
        task_data_map_.emplace(std::move(task_name), TaskData(std::move(stages)));
    }
}

const std::unordered_map<std::string, TaskData>& BaseTaskGenerator::getTaskDataMap() const 
{
    return task_data_map_;
}
