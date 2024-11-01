// generate_hotel_pick_plate_task.cpp 

#include "worm_picker_core/tasks/generation/generate_hotel_pick_plate_task.hpp"

GenerateHotelPickPlateTask::GenerateHotelPickPlateTask(const std::unordered_map<std::string, HotelData>& hotel_map)
    : hotel_data_map_(hotel_map)
{
}

void GenerateHotelPickPlateTask::generateTasks()
{
    // Implement task generation logic for hotel pick plate tasks
}

const std::map<std::string, TaskData>& GenerateHotelPickPlateTask::getTaskDataMap() const
{
    return task_data_map_;
}
