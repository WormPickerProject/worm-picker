// defined_tasks_parser.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tools/parsers/defined_tasks_parser.hpp"
#include <fstream>

DefinedTasksGenerator::DefinedTasksGenerator(std::string stages_file, std::string tasks_file)
    : stages_file_(std::move(std::filesystem::current_path().string() + stages_file))
    , tasks_file_(std::move(std::filesystem::current_path().string() + tasks_file)) {

    if (stages_file_.empty() || tasks_file_.empty()) {
        throw std::invalid_argument("File paths cannot be empty");
    }

    auto stages = parseStages();
    task_data_map_ = parseTasks(stages);
}

const DefinedTasksGenerator::TaskDataMap& DefinedTasksGenerator::getDefinedTasksMap() const 
{
    return task_data_map_;
}

DefinedTasksGenerator::StageDataMap DefinedTasksGenerator::parseStages() 
{
    StageDataMap stage_data_map;
    json stages_json = parseJsonFile(stages_file_);

    for (const auto& stage_entry : stages_json) {
        const auto& name = stage_entry["name"].get<std::string>();

        auto stage_data = createStageData(stage_entry);
        stage_data_map.emplace(name, std::move(stage_data));
    }

    return stage_data_map;
}

DefinedTasksGenerator::TaskDataMap DefinedTasksGenerator::parseTasks(
    const StageDataMap& stage_data_map) 
{
    TaskDataMap task_data_map;
    json tasks_json = parseJsonFile(tasks_file_);

    for (const auto& task_entry : tasks_json) {
        const auto& name = task_entry["name"].get<std::string>();
        auto stages = task_entry["stages"].get<std::vector<std::string>>();

        auto maybe_task = TaskData::create(stage_data_map, stages);
        if (!maybe_task) {
            throw std::runtime_error(
                "Failed to create task: " + name + " - Invalid stage name in configuration");
        }

        task_data_map.emplace(name, std::move(maybe_task.value()));
    }

    return task_data_map;
}

DefinedTasksGenerator::json DefinedTasksGenerator::parseJsonFile(const std::string& file_path) 
{
    std::ifstream file(file_path);
    return json::parse(file);
}

DefinedTasksGenerator::StageDataPtr DefinedTasksGenerator::createStageData(const json& stage_entry) 
{
    const auto& type = stage_entry["type"].get<std::string>();
    const auto& parameters = stage_entry["parameters"].get<std::vector<double>>();
    double velocity_scaling = stage_entry["velocity_scaling"].get<double>();
    double acceleration_scaling = stage_entry["acceleration_scaling"].get<double>();

    if (type == "JOINT") {
        return std::make_shared<MoveToJointData>(
            parameters[0], parameters[1], parameters[2], 
            parameters[3], parameters[4], parameters[5],
            velocity_scaling, acceleration_scaling
        );
    }
    
    if (type == "POINT") {
        return std::make_shared<MoveToPointData>(
            parameters[0], parameters[1], parameters[2],
            parameters[3], parameters[4], parameters[5], parameters[6],
            velocity_scaling, acceleration_scaling
        );
    }
    
    if (type == "RELATIVE") {
        return std::make_shared<MoveRelativeData>(
            parameters[0], parameters[1], parameters[2],
            velocity_scaling, acceleration_scaling
        );
    }

    return nullptr;
}