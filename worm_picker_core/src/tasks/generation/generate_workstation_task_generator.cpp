// generate_workstation_task_generator.cpp
//
// Copyright (c)
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tasks/generation/generate_workstation_task_generator.hpp"

GenerateWorkstationTaskGenerator::GenerateWorkstationTaskGenerator(const std::unordered_map<std::string, WorkstationData>& workstation_map, TaskType task_type)
    : GenericTaskGenerator(workstation_map), task_type_(task_type) {}

std::pair<char, int> GenerateWorkstationTaskGenerator::parseName(const std::string& name) const
{
    char row_letter = name[0];
    int col_number = std::stoi(name.substr(1));
    return {row_letter, col_number};
}

std::string GenerateWorkstationTaskGenerator::generateTaskName(char row_letter, int col_number) const
{
    std::string prefix;
    switch (task_type_) {
    case TaskType::PickPlate:
        prefix = "pickPlateWorkStation:";
        break;
    case TaskType::PlacePlate:
        prefix = "placePlateWorkStation:";
        break;
    case TaskType::HoverWormPick:
        prefix = "hoverWormPick:";
        break;
    }
    return prefix + std::string(1, row_letter) + std::to_string(col_number);
}

std::vector<std::shared_ptr<StageData>> GenerateWorkstationTaskGenerator::createStagesForTask(const WorkstationData& data, char row_letter) const
{
    double MOVE_DOWN, MOVE_FORWARD, MOVE_UP;
    switch (task_type_) {
    case TaskType::PickPlate:
        MOVE_DOWN = -0.03;
        MOVE_FORWARD = 0.04;
        MOVE_UP = 0.03;
        break;
    case TaskType::PlacePlate:
        MOVE_DOWN = -0.03;
        MOVE_FORWARD = -0.04;
        MOVE_UP = 0.03;
        break;
    case TaskType::HoverWormPick:
        // To be implemented, needs to be reviewed
        // MOVE_DOWN = MOVE_FORWARD = MOVE_UP = 0.0;
        break;
    }

    Coordinate derived_position = calculateDerivedPoint(data.getCoordinate(), row_letter);

    std::vector<std::shared_ptr<StageData>> stages;
    stages.reserve(4);

    stages.emplace_back(createMoveToPointStage(derived_position));

    if (task_type_ != TaskType::HoverWormPick) {
        stages.emplace_back(std::make_shared<MoveRelativeData>(MOVE_DOWN, 0.0, 0.0));
        stages.emplace_back(std::make_shared<MoveRelativeData>(0.0, 0.0, MOVE_FORWARD));
        stages.emplace_back(std::make_shared<MoveRelativeData>(MOVE_UP, 0.0, 0.0));
    }

    return stages;
}

Coordinate GenerateWorkstationTaskGenerator::calculateDerivedPoint(const Coordinate& coord, char row_letter) const
{
    double XY_OFFSET, Z_OFFSET;
    switch (task_type_) {
    case TaskType::PickPlate:
        XY_OFFSET = 0.048;
        Z_OFFSET = 0.02;
        break;
    case TaskType::PlacePlate:
        XY_OFFSET = -0.008;
        Z_OFFSET = -0.02;
        break;
    case TaskType::HoverWormPick:
        XY_OFFSET = 0.035;
        Z_OFFSET = 0.022;
        break;
    }

    constexpr double THETA_INCREMENT_DEG = 8.381;
    constexpr double DEGREES_TO_RADIANS = M_PI / 180.0;
    constexpr int REFERENCE_ROW_INDEX = 6;

    const int row_index = static_cast<int>(row_letter - 'A');
    const double theta_rad = (THETA_INCREMENT_DEG * (row_index - REFERENCE_ROW_INDEX)) * DEGREES_TO_RADIANS;

    const double adjusted_x = coord.getPositionX() + (XY_OFFSET * std::cos(theta_rad));
    const double adjusted_y = coord.getPositionY() + (XY_OFFSET * std::sin(theta_rad));
    const double adjusted_z = coord.getPositionZ() + Z_OFFSET;

    return {adjusted_x, adjusted_y, adjusted_z,
            coord.getOrientationX(), coord.getOrientationY(),
            coord.getOrientationZ(), coord.getOrientationW()};
}

std::shared_ptr<StageData> GenerateWorkstationTaskGenerator::createMoveToPointStage(const Coordinate& coord) const
{
    return std::make_shared<MoveToPointData>(
        coord.getPositionX(), coord.getPositionY(), coord.getPositionZ(),
        coord.getOrientationX(), coord.getOrientationY(),
        coord.getOrientationZ(), coord.getOrientationW());
}
