// generate_workstation_task_generator.hpp
//
// Copyright (c)
// SPDX-License-Identifier: Apache-2.0

#ifndef GENERATE_WORKSTATION_TASK_GENERATOR_HPP
#define GENERATE_WORKSTATION_TASK_GENERATOR_HPP

#include "worm_picker_core/tasks/generation/generic_task_generator.hpp"
#include "worm_picker_core/common/data_types/coordinate.hpp"
#include "worm_picker_core/common/data_types/workstation_data.hpp"
#include "worm_picker_core/stages/move_relative_data.hpp"
#include "worm_picker_core/stages/move_to_joint_data.hpp"
#include "worm_picker_core/stages/move_to_point_data.hpp"

class GenerateWorkstationTaskGenerator : public GenericTaskGenerator<WorkstationData> {
public:
    enum class TaskType {
        PickPlate,
        PlacePlate,
        HoverWormPick
    };

    GenerateWorkstationTaskGenerator(const std::unordered_map<std::string, WorkstationData>& workstation_map, TaskType task_type);

protected:
    std::pair<char, int> parseName(const std::string& name) const override;
    std::string generateTaskName(char row_letter, int col_number) const override;
    std::vector<std::shared_ptr<StageData>> createStagesForTask(const WorkstationData& data, char row_letter) const override;

private:
    Coordinate calculateDerivedPoint(const Coordinate& coord, char row_letter) const;
    std::shared_ptr<StageData> createMoveToPointStage(const Coordinate& coord) const;

    TaskType task_type_;
};

#endif // GENERATE_WORKSTATION_TASK_GENERATOR_HPP
