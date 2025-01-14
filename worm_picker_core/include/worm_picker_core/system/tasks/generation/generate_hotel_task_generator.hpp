// generate_hotel_task_generator.hpp
//
// Copyright (c)
// SPDX-License-Identifier: Apache-2.0

#ifndef GENERATE_HOTEL_TASK_GENERATOR_HPP
#define GENERATE_HOTEL_TASK_GENERATOR_HPP

#include "worm_picker_core/system/tasks/generation/generic_task_generator.hpp"
#include "worm_picker_core/core/geometry/coordinate.hpp"
#include "worm_picker_core/core/model/hotel_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_relative_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_joint_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_point_data.hpp"

class GenerateHotelTaskGenerator : public GenericTaskGenerator<HotelData> {
public:
    enum class TaskType {
        PickPlate,
        PlacePlate
    };

    GenerateHotelTaskGenerator(const std::unordered_map<std::string, 
                               HotelData>& hotel_map, 
                               TaskType task_type);

protected:
    std::pair<char, int> parseName(const std::string& name) const override;
    std::string generateTaskName(char row_letter, int col_number) const override;
    StageSequence createStagesForTask(const HotelData& data, char row_letter) const override;

private:
    Coordinate calculateDerivedPoint(const Coordinate& coord, char row_letter) const;
    std::shared_ptr<StageData> createMoveToPointStage(const Coordinate& coord) const;

    TaskType task_type_;
};

#endif // GENERATE_HOTEL_TASK_GENERATOR_HPP
