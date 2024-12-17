// task_generator.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef TASK_GENERATOR_HPP
#define TASK_GENERATOR_HPP

#include "worm_picker_core/tasks/task_data.hpp"
#include "worm_picker_core/tasks/generation/generate_workstation_task_generator.hpp"
#include "worm_picker_core/tasks/generation/generate_hotel_task_generator.hpp"

/// @brief 
class TaskGenerator {
public:
    using WorkstationMap = std::unordered_map<std::string, WorkstationData>;
    using HotelMap = std::unordered_map<std::string, HotelData>;
    using TaskMap = std::unordered_map<std::string, TaskData>;

    /// @brief 
    /// @param workstation_map 
    /// @param hotel_map 
    explicit TaskGenerator(const WorkstationMap& workstation_map, const HotelMap& hotel_map);

    /// @brief 
    /// @return 
    const TaskMap& getGeneratedTaskPlans() const;

private:
    using GeneratorPtr = std::unique_ptr<BaseTaskGenerator>;
    using GeneratorList = std::vector<GeneratorPtr>;

    /// @brief 
    /// @param workstation_map 
    /// @param hotel_map 
    /// @return 
    static GeneratorList initializeGenerators(const WorkstationMap& workstation_map, 
                                              const HotelMap& hotel_map);
    
    /// @brief 
    /// @param task_map 
    /// @param generator 
    static void aggregateTasksFromGenerator(TaskMap& task_map, const GeneratorPtr& generator);

    /// @brief 
    /// @param generators 
    /// @return 
    static TaskMap generateTasks(const GeneratorList& generators);


    /// @brief 
    TaskMap task_data_map_;
};

#endif // TASK_GENERATOR_HPP
