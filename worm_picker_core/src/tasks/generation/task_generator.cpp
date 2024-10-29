// task_generator.cpp

#include "worm_picker_core/tasks/generation/task_generator.hpp"

TaskGenerator::TaskGenerator(const std::unordered_map<std::string, WorkstationData>& workstation_map,
                             const std::unordered_map<std::string, HotelData>& hotel_map)
{
    GenerateWorkstationPickPlateTask pick_plate_workstation(workstation_map);
    pick_plate_workstation.generateTasks();
    task_data_map_.insert(pick_plate_workstation.getTaskDataMap().begin(), pick_plate_workstation.getTaskDataMap().end());

    GenerateWorkstationPlacePlateTask place_plate_workstation(workstation_map);
    place_plate_workstation.generateTasks();
    task_data_map_.insert(place_plate_workstation.getTaskDataMap().begin(), place_plate_workstation.getTaskDataMap().end());

    GenerateHotelPickPlateTask pick_plate_hotel(hotel_map);
    pick_plate_hotel.generateTasks();
    task_data_map_.insert(pick_plate_hotel.getTaskDataMap().begin(), pick_plate_hotel.getTaskDataMap().end());

    GenerateHotelPlacePlateTask place_plate_hotel(hotel_map);
    place_plate_hotel.generateTasks();
    task_data_map_.insert(place_plate_hotel.getTaskDataMap().begin(), place_plate_hotel.getTaskDataMap().end());
}

std::map<std::string, TaskData> TaskGenerator::getGeneratedTaskPlans()
{
    return task_data_map_;
}
