// task_generator.hpp

#ifndef TASK_GENERATOR_HPP
#define TASK_GENERATOR_HPP

#include "worm_picker_core/tasks/task_data_structure.hpp"
#include "worm_picker_core/tasks/generation/generate_workstation_pick_plate_task.hpp"
#include "worm_picker_core/tasks/generation/generate_workstation_place_plate_task.hpp"
#include "worm_picker_core/tasks/generation/generate_hotel_pick_plate_task.hpp"
#include "worm_picker_core/tasks/generation/generate_hotel_place_plate_task.hpp"

class TaskGenerator
{
public:
    TaskGenerator(const std::unordered_map<std::string, WorkstationData>& workstation_data_map,
                  const std::unordered_map<std::string, HotelData>& hotel_data_map);

    std::map<std::string, TaskData> getGeneratedTaskPlans();

private:
    std::map<std::string, TaskData> task_data_map_;
};

#endif // TASK_GENERATOR_HPP
