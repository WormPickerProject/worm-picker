// generate_hotel_task_generator.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "worm_picker_core/system/tasks/generation/generic_task_generator.hpp"
#include "worm_picker_core/core/geometry/coordinate.hpp"
#include "worm_picker_core/core/model/hotel_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_relative_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_joint_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_point_data.hpp"
#include "worm_picker_core/system/tasks/generation/hotel_task_config.hpp"

class GenerateHotelTaskGenerator : public GenericTaskGenerator<HotelData> {
public:
    using TaskType = hotel_config::TaskType;
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