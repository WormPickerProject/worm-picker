// generate_hotel_task_generator.cpp
//
// Copyright (c)
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/system/tasks/generation/generate_hotel_task_generator.hpp"

GenerateHotelTaskGenerator::GenerateHotelTaskGenerator(const std::unordered_map<std::string, HotelData>& hotel_map, TaskType task_type)
    : GenericTaskGenerator(hotel_map), task_type_(task_type) {}

std::pair<char, int> GenerateHotelTaskGenerator::parseName(const std::string& name) const
{
    char row_letter = name[0];
    int col_number = std::stoi(name.substr(1));
    return {row_letter, col_number};
}

std::string GenerateHotelTaskGenerator::generateTaskName(char row_letter, int col_number) const
{
    const auto prefix = [this]() -> std::string {
        switch (task_type_) {
        case TaskType::PickPlate: return hotel_config::prefix::PICK;
        case TaskType::PlacePlate: return hotel_config::prefix::PLACE;
        default: throw std::runtime_error("Unknown task type");
        }
    }();

    return prefix + std::string(1, row_letter) + std::to_string(col_number);
}

std::vector<std::shared_ptr<StageData>> GenerateHotelTaskGenerator::createStagesForTask(const HotelData& data, char row_letter) const
{
    // TODO: Implement the creation of stages specific to hotel tasks
    (void)data;
    (void)row_letter;
    return std::vector<std::shared_ptr<StageData>>();
}

Coordinate GenerateHotelTaskGenerator::calculateDerivedPoint(const Coordinate& coord, char row_letter) const
{
    // TODO: Implement calculation specific to hotel tasks
    (void)row_letter;
    double adjusted_x = coord.getPositionX();
    double adjusted_y = coord.getPositionY();
    double adjusted_z = coord.getPositionZ();

    return {adjusted_x, adjusted_y, adjusted_z,
            coord.getOrientationX(), coord.getOrientationY(),
            coord.getOrientationZ(), coord.getOrientationW()};
}

std::shared_ptr<StageData> GenerateHotelTaskGenerator::createMoveToPointStage(const Coordinate& coord) const
{
    return std::make_shared<MoveToPointData>(
        coord.getPositionX(), coord.getPositionY(), coord.getPositionZ(),
        coord.getOrientationX(), coord.getOrientationY(),
        coord.getOrientationZ(), coord.getOrientationW());
}
