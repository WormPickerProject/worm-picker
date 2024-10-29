// task_generator.cpp

#include "worm_picker_core/tasks/generation/task_generator.hpp"

TaskGenerator::TaskGenerator(const std::unordered_map<std::string, WorkstationData>& workstation_map,
                             const std::unordered_map<std::string, HotelData>& hotel_map)
{
    auto generators = initializeGenerators(workstation_map, hotel_map);
    generateAndAggregateTasks(generators);
}

const std::map<std::string, TaskData>& TaskGenerator::getGeneratedTaskPlans() const
{
    return task_data_map_;
}

std::vector<std::unique_ptr<BaseTaskGenerator>> TaskGenerator::initializeGenerators(const std::unordered_map<std::string, WorkstationData>& workstation_map,
                                                                                    const std::unordered_map<std::string, HotelData>& hotel_map) 
{
    std::vector<std::unique_ptr<BaseTaskGenerator>> generators;
    generators.emplace_back(std::make_unique<GenerateWorkstationPickPlateTask>(workstation_map));
    generators.emplace_back(std::make_unique<GenerateWorkstationPlacePlateTask>(workstation_map));
    generators.emplace_back(std::make_unique<GenerateHotelPickPlateTask>(hotel_map));
    generators.emplace_back(std::make_unique<GenerateHotelPlacePlateTask>(hotel_map));
    return generators;
}

void TaskGenerator::generateAndAggregateTasks(const std::vector<std::unique_ptr<BaseTaskGenerator>>& generators) 
{
    for (const auto& generator : generators) {
        generator->generateTasks();
        const auto& generated_tasks = generator->getTaskDataMap();
        task_data_map_.insert(generated_tasks.begin(), generated_tasks.end());
    }
}