// base_task_generator.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "worm_picker_core/core/tasks/task_data.hpp"

class BaseTaskGenerator {
public:
    virtual ~BaseTaskGenerator() = default;
    virtual void generateTasks() = 0;
    const std::unordered_map<std::string, TaskData>& getTaskDataMap() const {
        return task_data_map_;
    }

protected:
    std::unordered_map<std::string, TaskData> task_data_map_;
};