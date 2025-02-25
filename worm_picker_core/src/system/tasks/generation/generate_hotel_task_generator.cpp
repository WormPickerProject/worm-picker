// generate_hotel_task_generator.cpp
//
// Copyright (c)
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/system/tasks/generation/generate_hotel_task_generator.hpp"

GenerateHotelTaskGenerator::GenerateHotelTaskGenerator(
    const std::unordered_map<std::string, HotelData>& hotel_map, TaskType task_type)
  : GenericTaskGenerator(hotel_map), task_type_(task_type) {}

std::pair<int, int> GenerateHotelTaskGenerator::parseName(const std::string& name) const
{
    int num = std::stoi(name);
    int hotel_number = num / 100;
    int room_number = num % 100; 
    return {hotel_number, room_number};
}

std::string 
GenerateHotelTaskGenerator::generateTaskName(const std::pair<int, int>& parsed_name) const
{
    const auto prefix = [this]() -> std::string {
        switch (task_type_) {
        case TaskType::PickPlate: return hotel_config::prefix::PICK;
        case TaskType::PlacePlate: return hotel_config::prefix::PLACE;
        case TaskType::PickLid: return hotel_config::prefix::PICK_LID;
        case TaskType::PlaceLid: return hotel_config::prefix::PLACE_LID;
        case TaskType::MoveToPoint: return hotel_config::prefix::POINT;
        default: throw std::runtime_error("Unknown task type");
        }
    }();

    std::ostringstream key;
    key << parsed_name.first << std::setw(2) << std::setfill('0') << parsed_name.second;
    return prefix + key.str();
}

std::vector<std::shared_ptr<StageData>> 
GenerateHotelTaskGenerator::createStagesForTask(const HotelData& data, 
                                                const std::pair<int, int>& parsed_name) const
{
    Coordinate derived_position = calculateDerivedPoint(data.getCoordinate(), parsed_name.first);
    StageSequence stages{ createMoveToPointStage(derived_position) };


    const auto motion_params = [this]() -> std::optional<hotel_config::MovementParams> {
        switch (task_type_) {
            case TaskType::PickPlate: return hotel_config::motion::PICK;
            case TaskType::PlacePlate: return hotel_config::motion::PLACE;
            case TaskType::PickLid: return hotel_config::motion::PICK_LID;
            case TaskType::PlaceLid: return hotel_config::motion::PLACE_LID;
            case TaskType::MoveToPoint: return std::nullopt;
            default: throw std::runtime_error("Unknown task type");
        }
    }();

    if (motion_params) {
        stages.emplace_back(std::make_shared<MoveRelativeData>(
            motion_params->horizontal_approach, 0.0, 0.0));
        stages.emplace_back(std::make_shared<MoveRelativeData>(
            0.0, 0.0, motion_params->vertical_motion));
        stages.emplace_back(std::make_shared<MoveRelativeData>(
            motion_params->horizontal_retreat, 0.0, 0.0));
    }

    return stages;
}

Coordinate GenerateHotelTaskGenerator::calculateDerivedPoint(const Coordinate& coord, 
                                                             int hotel_number) const
{
    (void)hotel_number;
    const auto offsets = [this]() -> hotel_config::OffsetXYZ {
        switch (task_type_) {
            case TaskType::PickPlate: return hotel_config::offset::PICK;
            case TaskType::PlacePlate: return hotel_config::offset::PLACE;
            case TaskType::PickLid: return hotel_config::offset::PICK_LID;
            case TaskType::PlaceLid: return hotel_config::offset::PLACE_LID;
            case TaskType::MoveToPoint: return hotel_config::offset::POINT;
            default: throw std::runtime_error("Unknown task type");
        }
    }();
    
    // TODO: Implement more robust orientation calculation
    const auto& [x, y, z, w] = coord.getOrientation();
    const double theta_rad = std::atan2(2 * (w * z + x * y), 1 - 2 * (y * y + z * z));

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
GenerateHotelTaskGenerator::createMoveToPointStage(const Coordinate& coord) const
{
    return std::make_shared<MoveToPointData>(
        coord.getPositionX(), coord.getPositionY(), coord.getPositionZ(),
        coord.getOrientationX(), coord.getOrientationY(),
        coord.getOrientationZ(), coord.getOrientationW());
}
