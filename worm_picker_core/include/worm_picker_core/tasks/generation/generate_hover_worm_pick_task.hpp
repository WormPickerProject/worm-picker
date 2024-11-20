// generate_hover_worm_pick_task.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef GENERATE_HOVER_WORM_PICK_TASK_HPP
#define GENERATE_HOVER_WORM_PICK_TASK_HPP

#include "worm_picker_core/tasks/generation/base_task_generator.hpp"
#include "worm_picker_core/common/coordinate.hpp"


class GenerateHoverWormPickTask : public BaseTaskGenerator 
{
public:
    explicit GenerateHoverWormPickTask(const std::unordered_map<std::string, WorkstationData>& workstation_map);
    void generateTasks() override;
    const std::unordered_map<std::string, TaskData>& getTaskDataMap() const override;

private:
    std::pair<char, int> parseWorkstationName(const std::string& name) const;
    std::string generateTaskName(char row_letter, int col_number) const;
    std::vector<std::shared_ptr<StageData>> createStagesForTask(const WorkstationData& data, char row_letter) const;
    Coordinate calculateDerivedPoint(const Coordinate& coord, char row_letter) const;
    std::shared_ptr<StageData> createMoveToPointStage(const Coordinate& coord) const;

    const std::unordered_map<std::string, WorkstationData>& workstation_data_map_;
    std::unordered_map<std::string, TaskData> task_data_map_;
};

#endif // GENERATE_HOVER_WORM_PICK_TASK_HPP