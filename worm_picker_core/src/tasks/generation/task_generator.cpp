// task_generator.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/tasks/generation/task_generator.hpp"

TaskGenerator::TaskGenerator(const WorkstationMap& workstation_map, const HotelMap& hotel_map) 
    : task_data_map_{ generateTasks(initializeGenerators(workstation_map, hotel_map)) } 
{
}

const TaskGenerator::TaskMap& TaskGenerator::getGeneratedTaskPlans() const 
{
    return task_data_map_;
}

TaskGenerator::GeneratorList TaskGenerator::initializeGenerators(
    const WorkstationMap& workstation_map,
    const HotelMap& hotel_map) 
{
    GeneratorList generators;
    generators.emplace_back(std::make_unique<GenerateWorkstationPickPlateTask>(workstation_map));
    generators.emplace_back(std::make_unique<GenerateWorkstationPlacePlateTask>(workstation_map));
    generators.emplace_back(std::make_unique<GenerateHoverWormPickTask>(workstation_map));
    generators.emplace_back(std::make_unique<GenerateHotelPickPlateTask>(hotel_map));
    generators.emplace_back(std::make_unique<GenerateHotelPlacePlateTask>(hotel_map));
    return generators;
}

void TaskGenerator::aggregateTasksFromGenerator(TaskMap& task_map, const Generator& generator) 
{
    const auto& generated_tasks = generator->getTaskDataMap();
    task_map.insert(generated_tasks.begin(), generated_tasks.end());
}

TaskGenerator::TaskMap TaskGenerator::generateTasks(const GeneratorList& generators) 
{
    TaskMap task_map;

    std::ranges::for_each(generators, [&task_map](const auto& generator) {
        generator->generateTasks();
        aggregateTasksFromGenerator(task_map, generator);
    });

    return task_map;
}
