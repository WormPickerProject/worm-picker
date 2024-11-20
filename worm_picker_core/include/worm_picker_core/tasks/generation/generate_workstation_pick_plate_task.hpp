// generate_workstation_pick_plate_task.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef GENERATE_WORKSTATION_PICK_PLATE_TASK_HPP
#define GENERATE_WORKSTATION_PICK_PLATE_TASK_HPP

#include "worm_picker_core/tasks/generation/base_task_generator.hpp"
#include "worm_picker_core/common/coordinate.hpp"

/** 
 * @class GenerateWorkstationPickPlateTask
 * @brief Generates tasks for picking plates from workstations in a robotic system.
 *
 * This class processes workstation data, calculates derived positions,
 * creates movement stages, and compiles task data for execution.
 */
class GenerateWorkstationPickPlateTask : public BaseTaskGenerator
{
public:
    /** 
     * @brief Constructs a GenerateWorkstationPickPlateTask object.
     * @param workstation_data_map A map containing workstation names and their associated data.
     */
    explicit GenerateWorkstationPickPlateTask(const std::unordered_map<std::string, WorkstationData>& workstation_data_map);
    
    /** 
     * @brief Generates tasks based on the provided workstation data.
     *
     * Processes each workstation, calculates derived points, creates movement stages,
     * and stores the resulting tasks in the task data map.
     */
    void generateTasks() override;

    /** 
     * @brief Retrieves the map of generated task data.
     * @return A constant reference to the map containing task names and their associated data.
     */
    const std::unordered_map<std::string, TaskData>& getTaskDataMap() const override;

private:
    /** 
     * @brief Parses a workstation name into a row letter and column number.
     * @param name The workstation name in the format "<RowLetter><ColumnNumber>" (e.g., "A1").
     * @return A pair containing the row letter and column number.
     */
    std::pair<char, int> parseWorkstationName(const std::string& name) const;

    /**
     * @brief Generates a task name based on the row letter and column number.
     * @param row_letter The row letter of the workstation (e.g., 'A').
     * @param col_number The column number of the workstation.
     * @return A string representing the generated task name.
     */
    std::string generateTaskName(char row_letter, int col_number) const;

    /**
     * @brief Creates the sequence of stages for a given workstation task.
     * @param data The workstation data containing coordinates and other relevant information.
     * @param row_letter The row letter of the workstation.
     * @return A vector of shared pointers to StageData objects representing the task stages.
     */
    std::vector<std::shared_ptr<StageData>> createStagesForTask(const WorkstationData& data, char row_letter) const;
    
    /** 
     * @brief Calculates a derived coordinate point based on the original coordinate and row letter.
     * @param coord The original coordinate from the workstation data.
     * @param row_letter The row letter of the workstation.
     * @return A Coordinate object representing the calculated derived point.
     */
    Coordinate calculateDerivedPoint(const Coordinate& coord, char row_letter) const;
    
    /** 
     * @brief Creates a MoveToPoint stage data object for moving to a specific coordinate.
     * @param coord The coordinate to move to.
     * @return A shared pointer to a MoveToPointData object representing the movement stage.
     */
    std::shared_ptr<StageData> createMoveToPointStage(const Coordinate& coord) const;

    std::unordered_map<std::string, WorkstationData> workstation_data_map_; ///< Map of workstation names to their corresponding data.
    std::unordered_map<std::string, TaskData> task_data_map_; ///< Map of generated task names to their corresponding task data.
};

#endif // GENERATE_WORKSTATION_PICK_PLATE_TASK_HPP
