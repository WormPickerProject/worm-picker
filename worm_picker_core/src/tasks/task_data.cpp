// task_data.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
// Additional Contributions: Fang-Yen Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");

#include "worm_picker_core/tasks/task_data.hpp"
#include "worm_picker_core/exceptions/exceptions.hpp"

TaskData::TaskData(std::vector<std::shared_ptr<StageData>> stages)
    : stages_(std::move(stages))
{
}

TaskData::TaskData(const std::unordered_map<std::string, std::shared_ptr<StageData>>& stage_data_map,
                   const std::vector<std::string>& stage_names)
{
    for (const auto& name : stage_names) {
        auto it = stage_data_map.find(name);
        if (it != stage_data_map.end()) {
            stages_.emplace_back(it->second);
        } else {
            throw StageNotFoundException("TaskData::TaskData failed: Stage name '" + name + "' not found.");
        }
    }
}

const std::vector<std::shared_ptr<StageData>>& TaskData::getStages() const 
{
    return stages_;
}
