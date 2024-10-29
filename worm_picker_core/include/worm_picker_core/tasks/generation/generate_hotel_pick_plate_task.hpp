// generate_hotel_pick_plate_task.hpp 

#ifndef GENERATE_HOTEL_PICK_PLATE_TASK_HPP
#define GENERATE_HOTEL_PICK_PLATE_TASK_HPP

#include "worm_picker_core/tasks/task_data_structure.hpp"

class GenerateHotelPickPlateTask
{
public:
    GenerateHotelPickPlateTask(const std::unordered_map<std::string, HotelData>& hotel_map);

    void generateTasks();
    const std::map<std::string, TaskData>& getTaskDataMap() const;

private:
    const std::unordered_map<std::string, HotelData>& hotel_data_map_;
    std::map<std::string, TaskData> task_data_map_;
};

#endif // GENERATE_HOTEL_PICK_PLATE_TASK_HPP
