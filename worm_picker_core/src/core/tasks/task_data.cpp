// task_data.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/core/tasks/task_data.hpp"

TaskData::TaskData(StageVector stages) 
    : stages_(std::move(stages)) {}

TaskData::TaskData(const TaskData& other) 
{
    stages_.reserve(other.stages_.size());
    for (const auto& stage_ptr : other.stages_) {
        stages_.push_back(std::shared_ptr<StageData>(stage_ptr->clone())); 
    }
}

std::optional<TaskData> TaskData::create(const StageMap& stage_data_map,
                                       const std::vector<std::string>& stage_names) 
{
    TaskData new_task;
    new_task.stages_.reserve(stage_names.size());

    for (const auto& name : stage_names) {
        auto it = stage_data_map.find(name);
        if (it == stage_data_map.end()) {
            return std::nullopt;
        }
        new_task.stages_.emplace_back(it->second->clone());
    }
    return std::optional<TaskData>(new_task);
}

const TaskData::StageVector& TaskData::getStages() const 
{ 
    return stages_; 
}