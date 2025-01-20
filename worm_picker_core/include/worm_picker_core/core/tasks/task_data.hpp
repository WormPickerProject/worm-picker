// task_data.hpp
//
// Copyright (c) 2025
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
    explicit TaskData(StageVector stages);
    TaskData(const TaskData& other);
    
    static std::optional<TaskData> create(const StageMap& stage_data_map,
                                          const std::vector<std::string>& stage_names);                           
    const StageVector& getStages() const;

private:
    StageVector stages_{};
};

#endif // TASK_DATA_HPP