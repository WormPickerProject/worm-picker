// generate_workstation_pick_plate_task.cpp

#include "worm_picker_core/tasks/generation/generate_workstation_pick_plate_task.hpp"

GenerateWorkstationPickPlateTask::GenerateWorkstationPickPlateTask(const std::unordered_map<std::string, WorkstationData>& workstation_map)
    : workstation_data_map_(workstation_map)
{
}

void GenerateWorkstationPickPlateTask::generateTasks()
{
    for (const auto& workstation_entry : workstation_data_map_) {
        const std::string& workstation_name = workstation_entry.first;
        const WorkstationData& workstation_data = workstation_entry.second;

        char row_letter = workstation_name[0];
        int col_number = std::stoi(workstation_name.substr(1));

        Coordinate derived_position = calculateDerivedPoint(workstation_data.coordinate, row_letter);

        std::string stage_name = generateStageName(row_letter, col_number, 1);

        std::string task_name = generateTaskName(row_letter, col_number);
        addStageToTaskDataMap(stage_name, derived_position, workstation_data.coordinate);

        // For future: add more stages if needed, each stage could follow a similar pattern
    }
}

Coordinate GenerateWorkstationPickPlateTask::calculateDerivedPoint(const Coordinate& coord, 
                                                                   char row_letter)
{
    const double OFFSET = 0.046; 
    const double Z_OFFSET = 0.02;  
    const double THETA_INCREMENT_DEG = 8.381;

    int row_index = row_letter - 'A'; 
    double theta_deg = THETA_INCREMENT_DEG * (row_index - 6); 
    double theta_rad = theta_deg * M_PI / 180.0;

    double x = coord.position_x - (OFFSET * std::cos(theta_rad));
    double y = coord.position_y - (OFFSET * std::sin(theta_rad));
    double z = coord.position_z + Z_OFFSET;

    return { x, y, z, coord.orientation_x, coord.orientation_y, coord.orientation_z, coord.orientation_w };
}

std::string GenerateWorkstationPickPlateTask::generateStageName(char row_letter, int col_number, int stage_number)
{
    return std::string(1, row_letter) + std::to_string(col_number) + ":" + std::to_string(stage_number);
}

std::string GenerateWorkstationPickPlateTask::generateTaskName(char row_letter, int col_number)
{
    std::string task_name = "pickPlateWorkStation:R" + std::string(1, row_letter) + ":" + std::to_string(col_number);
    return task_name;
}

void GenerateWorkstationPickPlateTask::addStageToTaskDataMap(const std::string& stage_name, 
                                                             const Coordinate& derived_position, 
                                                             const Coordinate& original_orientation)
{
    auto stage = std::make_shared<MoveToPointData>(
        derived_position.position_x,
        derived_position.position_y,
        derived_position.position_z,
        original_orientation.orientation_x,
        original_orientation.orientation_y,
        original_orientation.orientation_z,
        original_orientation.orientation_w);

    stage_data_map_[stage_name] = stage;

    TaskData task_data;
    task_data.stages.push_back(stage);

    task_data_map_[stage_name] = task_data;
}

const std::map<std::string, TaskData>& GenerateWorkstationPickPlateTask::getTaskDataMap() const
{
    return task_data_map_;
}
