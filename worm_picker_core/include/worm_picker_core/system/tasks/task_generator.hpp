// task_generator.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "worm_picker_core/core/tasks/task_data.hpp"
#include "worm_picker_core/system/tasks/generation/generate_workstation_task_generator.hpp"
#include "worm_picker_core/system/tasks/generation/generate_hotel_task_generator.hpp"
#include "worm_picker_core/system/tasks/generation/generate_transfer_task_generator.hpp"

class TaskGenerator {
public:
    using WorkstationMap = std::unordered_map<std::string, WorkstationData>;
    using HotelMap = std::unordered_map<std::string, HotelData>;
    using TaskMap = std::unordered_map<std::string, TaskData>;

    explicit TaskGenerator(const WorkstationMap& workstation_map, const HotelMap& hotel_map);
    const TaskMap& getGeneratedTaskPlans() const;

private:
    using GeneratorPtr = std::unique_ptr<BaseTaskGenerator>;
    using GeneratorList = std::vector<GeneratorPtr>;

    static GeneratorList initializeGenerators(const WorkstationMap& workstation_map, 
                                              const HotelMap& hotel_map);
    static void aggregateTasksFromGenerator(TaskMap& task_map, const GeneratorPtr& generator);
    static TaskMap generateTasks(const GeneratorList& generators);

    TaskMap task_data_map_;
};