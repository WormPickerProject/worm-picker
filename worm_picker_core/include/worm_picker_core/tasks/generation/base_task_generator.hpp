// base_task_generator.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef BASE_TASK_GENERATOR_HPP
#define BASE_TASK_GENERATOR_HPP

#include "worm_picker_core/tasks/task_data.hpp"

class BaseTaskGenerator {
public:
    virtual ~BaseTaskGenerator() = default;
    void generateTasks();
    const std::unordered_map<std::string, TaskData>& getTaskDataMap() const;

protected:
    virtual std::pair<char, int> parseName(const std::string& name) const = 0;
    virtual std::string generateTaskName(char row_letter, int col_number) const = 0;
    virtual std::vector<std::shared_ptr<StageData>> createStagesForTaskImpl(const std::string& name, char row_letter) const = 0;
    virtual std::vector<std::string> getDataMapKeys() const = 0;

    std::unordered_map<std::string, TaskData> task_data_map_;
};

#endif // BASE_TASK_GENERATOR_HPP
