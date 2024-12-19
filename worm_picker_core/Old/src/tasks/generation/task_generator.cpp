// task_generator.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tasks/generation/task_generator.hpp"
#include "worm_picker_core/tasks/generation/workstation_task_config.hpp"

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

    generators.emplace_back(std::make_unique<GenerateWorkstationTaskGenerator>(
        workstation_map, workstation_config::TaskType::PickPlate));

    generators.emplace_back(std::make_unique<GenerateWorkstationTaskGenerator>(
        workstation_map, workstation_config::TaskType::PlacePlate));

    generators.emplace_back(std::make_unique<GenerateWorkstationTaskGenerator>(
        workstation_map, workstation_config::TaskType::HoverWormPick));

    generators.emplace_back(std::make_unique<GenerateWorkstationTaskGenerator>(
        workstation_map, workstation_config::TaskType::MoveToPoint));

    generators.emplace_back(std::make_unique<GenerateHotelTaskGenerator>(
        hotel_map, GenerateHotelTaskGenerator::TaskType::PickPlate));

    generators.emplace_back(std::make_unique<GenerateHotelTaskGenerator>(
        hotel_map, GenerateHotelTaskGenerator::TaskType::PlacePlate));

    return generators;
}

void TaskGenerator::aggregateTasksFromGenerator(TaskMap& task_map, const GeneratorPtr& generator)
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
