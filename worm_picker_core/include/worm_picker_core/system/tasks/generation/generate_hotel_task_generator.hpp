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

class GenerateHotelTaskGenerator : public GenericTaskGenerator<HotelData, std::pair<int, int>> {
public:
    using TaskType = hotel_config::TaskType;
    GenerateHotelTaskGenerator(const std::unordered_map<std::string, HotelData>& hotel_map, 
                               TaskType task_type);
    void generateTasks() override;

protected:
    std::pair<int, int> parseName(const std::string& name) const override;
    std::string generateTaskName(const std::pair<int, int>& parsed_name) const override;
    StageSequence createStagesForTask(const HotelData& data, 
                                      const std::pair<int, int>& parsed_name) const override;

private:
    bool shouldGenerateTaskForRoom(int room_number) const;
    Coordinate calculateDerivedPoint(const Coordinate& coord, int hotel_number) const;
    std::shared_ptr<StageData> createMoveToPointStage(const Coordinate& coord) const;

    TaskType task_type_;
};