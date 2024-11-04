// task_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
// Additional Contributions: Fang-Yen Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");

#ifndef TASK_DATA_HPP
#define TASK_DATA_HPP

#include "worm_picker_core/stages/stage_data.hpp"
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

/**
 * @class TaskData
 * @brief Represents a collection of stages that form a task.
 */
class TaskData {
public:
    /**
     * @brief Default constructor.
     */
    TaskData() = default;

    /**
     * @brief Constructs a TaskData with a vector of stage pointers.
     * @param stages Vector of shared pointers to stages to include in the task.
     */
    explicit TaskData(std::vector<std::shared_ptr<StageData>> stages);

    /**
     * @brief Constructs a TaskData with the given stage data map and stage names.
     * @param stage_data_map Map of stage names to shared pointers of StageData.
     * @param stage_names List of stage names to include in the task.
     * @throws StageNotFoundException If any stage name is not found in the stage_data_map.
     */
    TaskData(const std::unordered_map<std::string, std::shared_ptr<StageData>>& stage_data_map,
             const std::vector<std::string>& stage_names);

    const std::vector<std::shared_ptr<StageData>>& getStages() const noexcept;

private:
    std::vector<std::shared_ptr<StageData>> stages_;
};

#endif // TASK_DATA_HPP
