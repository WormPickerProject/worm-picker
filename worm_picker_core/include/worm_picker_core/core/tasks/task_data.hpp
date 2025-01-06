// task_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef TASK_DATA_HPP
#define TASK_DATA_HPP

#include "worm_picker_core/core/tasks/stage_data.hpp"

class TaskData {
public:
    using StageDataPtr = std::shared_ptr<StageData>;
    using StageVector = std::vector<StageDataPtr>;
    using StageMap = std::unordered_map<std::string, StageDataPtr>;

    TaskData() = default;
    explicit TaskData(StageVector stages) : stages_(std::move(stages)) {}
    TaskData(const TaskData& other);
    
    static std::optional<TaskData> create(const StageMap& stage_data_map,
                                          const std::vector<std::string>& stage_names);
    constexpr const StageVector& getStages() const { return stages_; }

private:
    StageVector stages_{};
};

inline TaskData::TaskData(const TaskData& other) 
{
    stages_.reserve(other.stages_.size());
    for (const auto& stage_ptr : other.stages_) {
        stages_.push_back(std::shared_ptr<StageData>(stage_ptr->clone())); 
    }
}

inline std::optional<TaskData> TaskData::create(const StageMap& stage_data_map,
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

#endif // TASK_DATA_HPP
