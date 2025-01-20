// generate_workstation_task_generator.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "worm_picker_core/system/tasks/generation/generic_task_generator.hpp"
#include "worm_picker_core/core/geometry/coordinate.hpp"
#include "worm_picker_core/core/model/workstation_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_relative_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_joint_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_point_data.hpp"
#include "worm_picker_core/system/tasks/generation/workstation_task_config.hpp"

/// @brief Generator class for creating workstation-specific task sequences
class GenerateWorkstationTaskGenerator : public GenericTaskGenerator<WorkstationData> {
public:
    using TaskType = workstation_config::TaskType; 

    /// @brief Constructs a workstation task generator
    /// @param workstation_map Map of workstation locations and their data
    /// @param task_type Type of task to generate
    GenerateWorkstationTaskGenerator(const std::unordered_map<std::string, 
                                     WorkstationData>& workstation_map, 
                                     TaskType task_type);

protected:
    /// @brief Parses a workstation name into row and column components
    /// @param name Workstation identifier (e.g., "A1", "B2")
    /// @return Pair of row letter and column number
    std::pair<char, int> parseName(const std::string& name) const override;

    /// @brief Generates a task name based on location and type
    /// @param row_letter Row identifier (A-Z)
    /// @param col_number Column number
    /// @return Full task name including prefix and location
    std::string generateTaskName(char row_letter, int col_number) const override;

    /// @brief Creates a sequence of stages for executing a task
    /// @param data Workstation data including position and orientation
    /// @param row_letter Row identifier for angle calculations
    /// @return Sequence of stages comprising the task
    StageSequence createStagesForTask(const WorkstationData& data, char row_letter) const override;

private:
    /// @brief Calculates adjusted position based on workstation location
    /// @param coord Base coordinate of the workstation
    /// @param row_letter Row identifier for angle calculations
    /// @return Modified coordinate with appropriate offsets applied
    Coordinate calculateDerivedPoint(const Coordinate& coord, char row_letter) const;

    /// @brief Creates a movement stage to a specific point
    /// @param coord Target coordinate for movement
    /// @return Stage data for point-to-point movement
    std::shared_ptr<StageData> createMoveToPointStage(const Coordinate& coord) const;

    /// @brief Type of task this generator is configured to create
    TaskType task_type_;
};