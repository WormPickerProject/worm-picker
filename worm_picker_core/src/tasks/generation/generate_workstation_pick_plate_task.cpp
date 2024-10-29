// generate_workstation_pick_plate_task.cpp

#include "worm_picker_core/tasks/generation/generate_workstation_pick_plate_task.hpp"

GenerateWorkstationPickPlateTask::GenerateWorkstationPickPlateTask(const std::unordered_map<std::string, WorkstationData>& workstation_map)
    : workstation_data_map_(workstation_map)
{
}

void GenerateWorkstationPickPlateTask::generateTasks()
{
    // Implement task generation logic for workstation pick plate tasks
}

const std::map<std::string, TaskData>& GenerateWorkstationPickPlateTask::getTaskDataMap() const
{
    return task_data_map_;
}
