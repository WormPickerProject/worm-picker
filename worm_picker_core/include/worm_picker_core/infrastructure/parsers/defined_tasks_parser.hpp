// defined_tasks_parser.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef DEFINED_TASKS_PARSER_HPP
#define DEFINED_TASKS_PARSER_HPP

#include <nlohmann/json.hpp>
#include "worm_picker_core/core/tasks/task_data.hpp"
#include "worm_picker_core/core/tasks/stages/stage_data.hpp"

class DefinedTasksGenerator {
public:
    using TaskDataMap = std::map<std::string, TaskData>;

    explicit DefinedTasksGenerator(const std::string& stages_file, const std::string& tasks_file);
    const TaskDataMap& getDefinedTasksMap() const;

private:
    using json = nlohmann::json;
    using StageDataPtr = std::shared_ptr<StageData>;
    using StageDataMap = std::unordered_map<std::string, StageDataPtr>;

    StageDataMap parseStages();
    TaskDataMap parseTasks(const StageDataMap& stage_data_map);
    static json parseJsonFile(const std::string& file_path);
    static StageDataPtr createStageData(const json& stage_entry);
    static StageDataPtr createJointStageData(const json& stage_entry, 
                                             double velocity_scaling,
                                             double acceleration_scaling);

    std::string stages_file_;
    std::string tasks_file_;
    TaskDataMap task_data_map_;
};

#endif // DEFINED_TASKS_PARSER_HPP
