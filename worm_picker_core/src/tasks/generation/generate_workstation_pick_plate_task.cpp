// generate_workstation_pick_plate_task.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tasks/generation/generate_workstation_pick_plate_task.hpp"
#include <cmath>

GenerateWorkstationPickPlateTask::GenerateWorkstationPickPlateTask(
    const std::unordered_map<std::string, WorkstationData>& workstation_data_map)
    : workstation_data_map_(workstation_data_map) 
{
}

void GenerateWorkstationPickPlateTask::generateTasks() 
{
    for (const auto& [workstation_name, workstation_data] : workstation_data_map_) {
        auto [row_letter, col_number] = parseWorkstationName(workstation_name);
        
        std::string task_name = generateTaskName(row_letter, col_number);
        auto stages = createStagesForTask(workstation_data, row_letter);

        task_data_map_.emplace(std::move(task_name), TaskData{std::move(stages)});
    }
}

const std::map<std::string, TaskData>& GenerateWorkstationPickPlateTask::getTaskDataMap() const 
{
    return task_data_map_;
}

std::pair<char, int> GenerateWorkstationPickPlateTask::parseWorkstationName(const std::string& name) const 
{
    char row_letter = name[0];
    int col_number = std::stoi(name.substr(1));
    return { row_letter, col_number };
}

std::string GenerateWorkstationPickPlateTask::generateTaskName(char row_letter, int col_number) const
{
    constexpr char prefix[] = "pickPlateWorkStation:";
    return prefix + std::string(1, row_letter) + std::to_string(col_number);
}

std::vector<std::shared_ptr<StageData>> GenerateWorkstationPickPlateTask::createStagesForTask(
    const WorkstationData& data, char row_letter) const
{
    constexpr double MOVE_DOWN = -0.03;
    constexpr double MOVE_FORWARD = 0.04;
    constexpr double MOVE_UP = 0.03;

    Coordinate derived_position = calculateDerivedPoint(data.getCoordinate(), row_letter);

    std::vector<std::shared_ptr<StageData>> stages;
    stages.reserve(4); 

    stages.emplace_back(createMoveToPointStage(derived_position));
    stages.emplace_back(std::make_shared<MoveRelativeData>(MOVE_DOWN, 0.0, 0.0));
    stages.emplace_back(std::make_shared<MoveRelativeData>(0.0, 0.0, MOVE_FORWARD));
    stages.emplace_back(std::make_shared<MoveRelativeData>(MOVE_UP, 0.0, 0.0));

    return stages;
}

Coordinate GenerateWorkstationPickPlateTask::calculateDerivedPoint(const Coordinate& coord, char row_letter) const
{
    constexpr double XY_OFFSET = 0.048;
    constexpr double Z_OFFSET = 0.02;
    constexpr double THETA_INCREMENT_DEG = 8.381;
    constexpr double DEGREES_TO_RADIANS = M_PI / 180.0;
    constexpr int REFERENCE_ROW_INDEX = 6; 

    int row_index = static_cast<int>(row_letter - 'A');
    double theta_rad = (THETA_INCREMENT_DEG * (row_index - REFERENCE_ROW_INDEX)) * DEGREES_TO_RADIANS;

    double adjusted_x = coord.getPositionX() - (XY_OFFSET * std::cos(theta_rad));
    double adjusted_y = coord.getPositionY() - (XY_OFFSET * std::sin(theta_rad));
    double adjusted_z = coord.getPositionZ() + Z_OFFSET;

    return { adjusted_x, adjusted_y, adjusted_z, 
             coord.getOrientationX(), coord.getOrientationY(), 
             coord.getOrientationZ(), coord.getOrientationW() };
}

std::shared_ptr<StageData> GenerateWorkstationPickPlateTask::createMoveToPointStage(const Coordinate& coord) const
{
    return std::make_shared<MoveToPointData>(
        coord.getPositionX(), coord.getPositionY(), coord.getPositionZ(),
        coord.getOrientationX(), coord.getOrientationY(), 
        coord.getOrientationZ(), coord.getOrientationW()
    );
}
