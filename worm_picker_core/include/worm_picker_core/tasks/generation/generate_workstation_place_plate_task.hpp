// generate_workstation_place_plate_task.hpp 

#ifndef GENERATE_WORKSTATION_PLACE_PLATE_TASK_HPP
#define GENERATE_WORKSTATION_PLACE_PLATE_TASK_HPP

#include "worm_picker_core/tasks/task_data_structure.hpp"

class GenerateWorkstationPlacePlateTask 
{
public:
    GenerateWorkstationPlacePlateTask(const std::unordered_map<std::string, WorkstationData>& workstation_map);

    void generateTasks();
    const std::map<std::string, TaskData>& getTaskDataMap() const;

private:
    const std::unordered_map<std::string, WorkstationData>& workstation_data_map_;
    std::map<std::string, TaskData> task_data_map_;
};

#endif // GENERATE_WORKSTATION_PLACE_PLATE_TASK_HPP
