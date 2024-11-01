// generate_workstation_pick_plate_task.hpp

#ifndef GENERATE_WORKSTATION_PICK_PLATE_TASK_HPP
#define GENERATE_WORKSTATION_PICK_PLATE_TASK_HPP

#include "worm_picker_core/tasks/generation/base_task_generator.hpp"

class GenerateWorkstationPickPlateTask : public BaseTaskGenerator
{
public:
    GenerateWorkstationPickPlateTask(const std::unordered_map<std::string, WorkstationData>& workstation_map);

    void generateTasks() override;
    const std::map<std::string, TaskData>& getTaskDataMap() const override;

private:
    Coordinate calculateDerivedPoint(const Coordinate& coord, char row_letter);
    std::string generateStageName(char row_letter, int col_number, int stage_number);
    std::string generateTaskName(char row_letter, int col_number);
    void addStageToTaskDataMap(const std::string& stage_name, const Coordinate& derived_position, const Coordinate& original_orientation);

    const std::unordered_map<std::string, WorkstationData>& workstation_data_map_;
    std::map<std::string, std::shared_ptr<StageData>> stage_data_map_;
    std::map<std::string, TaskData> task_data_map_;
};

#endif // GENERATE_WORKSTATION_PICK_PLATE_TASK_HPP
