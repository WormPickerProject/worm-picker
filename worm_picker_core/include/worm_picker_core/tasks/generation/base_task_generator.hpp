// base_task_generator.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef BASE_TASK_GENERATOR_HPP
#define BASE_TASK_GENERATOR_HPP

#include "worm_picker_core/tasks/task_data.hpp"
#include "worm_picker_core/stages/move_relative_data.hpp"
#include "worm_picker_core/stages/move_to_joint_data.hpp"
#include "worm_picker_core/stages/move_to_point_data.hpp"

/** 
 * @class BaseTaskGenerator
 * @brief Abstract base class for task generators.
 */
class BaseTaskGenerator 
{
public:
    virtual ~BaseTaskGenerator() = default;

    /**
     * @brief Generates tasks.
     */
    virtual void generateTasks() = 0;

    /**
     * @brief Retrieves the generated task data map.
     * @return Const reference to the task data map.
     */
    virtual const std::unordered_map<std::string, TaskData>& getTaskDataMap() const = 0;
};

#endif // BASE_TASK_GENERATOR_HPP