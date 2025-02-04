// generate_workstation_task_generator.cpp
//
// Copyright (c)
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/system/tasks/generation/generate_workstation_task_generator.hpp"

GenerateWorkstationTaskGenerator::GenerateWorkstationTaskGenerator(
    const std::unordered_map<std::string, WorkstationData>& workstation_map, TaskType task_type) 
    : GenericTaskGenerator(workstation_map), task_type_(task_type) 
{
}

std::pair<char, int> GenerateWorkstationTaskGenerator::parseName(const std::string& name) const
{
    char row_letter = name[0];
    int col_number = std::stoi(name.substr(1));
    return {row_letter, col_number};
}

std::string GenerateWorkstationTaskGenerator::generateTaskName(char row_letter, 
                                                               int col_number) const
{
    const auto prefix = [this]() -> std::string {
        switch (task_type_) {
            case TaskType::PickPlate: return workstation_config::prefix::PICK;
            case TaskType::PlacePlate: return workstation_config::prefix::PLACE;
            case TaskType::HoverWormPick: return workstation_config::prefix::HOVER;
            case TaskType::MoveToPoint: return workstation_config::prefix::POINT;
            default: throw std::runtime_error("Unknown task type");
        }
    }();

    return prefix + std::string(1, row_letter) + std::to_string(col_number);
}

GenerateWorkstationTaskGenerator::StageSequence 
GenerateWorkstationTaskGenerator::createStagesForTask(const WorkstationData& data, 
                                                      char row_letter) const
{
    Coordinate derived_position = calculateDerivedPoint(data.getCoordinate(), row_letter);
    StageSequence stages{ createMoveToPointStage(derived_position) };

    const auto motion_params = [this]() -> std::optional<workstation_config::MovementParams> {
        switch (task_type_) {
            case TaskType::PickPlate: return workstation_config::motion::PICK;
            case TaskType::PlacePlate: return workstation_config::motion::PLACE;
            case TaskType::HoverWormPick: return std::nullopt;
            case TaskType::MoveToPoint: return std::nullopt;
            default: throw std::runtime_error("Unknown task type");
        }
    }();

    if (motion_params) {
        stages.emplace_back(std::make_shared<MoveRelativeData>(
            0.0, 0.0, motion_params->vertical_approach));
        stages.emplace_back(std::make_shared<MoveRelativeData>(
            motion_params->horizontal_motion, 0.0, 0.0));
        stages.emplace_back(std::make_shared<MoveRelativeData>(
            0.0, 0.0, motion_params->vertical_retreat));
    }

    return stages;
}

Coordinate GenerateWorkstationTaskGenerator::calculateDerivedPoint(const Coordinate& coord, 
                                                                   char row_letter) const
{
    using namespace workstation_config;
    const auto offsets = [this]() -> workstation_config::OffsetXYZ {
        switch (task_type_) {
            case TaskType::PickPlate: return offset::PICK;
            case TaskType::PlacePlate: return offset::PLACE;
            case TaskType::HoverWormPick: return offset::HOVER;
            case TaskType::MoveToPoint: return offset::POINT;
            default: throw std::runtime_error("Unknown task type");
        }
    }();
    
    const double theta_rad = angle::THETA_STEP_RAD * (row_letter - angle::REFERENCE_ROW);
    const double cos_theta = std::cos(theta_rad);
    const double sin_theta = std::sin(theta_rad);

    return {
        coord.getPositionX() + (offsets.x * cos_theta) + (offsets.y * sin_theta),
        coord.getPositionY() + (offsets.x * sin_theta) + (offsets.y * cos_theta),
        coord.getPositionZ() + offsets.z,
        coord.getOrientationX(),
        coord.getOrientationY(),
        coord.getOrientationZ(),
        coord.getOrientationW()
    };
}

std::shared_ptr<StageData> 
GenerateWorkstationTaskGenerator::createMoveToPointStage(const Coordinate& coord) const
{
    return std::make_shared<MoveToPointData>(
        coord.getPositionX(), coord.getPositionY(), coord.getPositionZ(),
        coord.getOrientationX(), coord.getOrientationY(),
        coord.getOrientationZ(), coord.getOrientationW());
}