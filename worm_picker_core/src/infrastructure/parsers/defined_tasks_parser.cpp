// defined_tasks_parser.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <fstream>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include "worm_picker_core/core/tasks/stages/move_relative_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_joint_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_point_data.hpp"
#include "worm_picker_core/infrastructure/parsers/defined_tasks_parser.hpp"

DefinedTasksGenerator::DefinedTasksGenerator(const std::string& stages_file, 
                                           const std::string& tasks_file)
    : stages_file_(stages_file), 
      tasks_file_(tasks_file) 
{
    if (stages_file_.empty() || tasks_file_.empty()) {
        throw std::invalid_argument("File paths cannot be empty");
    }

    auto stages = parseStages();
    task_data_map_ = parseTasks(stages);
}

DefinedTasksGenerator::StageDataMap DefinedTasksGenerator::parseStages() 
{
    StageDataMap stage_data_map;
    json stages_json = parseJsonFile(stages_file_);

    for (const auto& stage_entry : stages_json) {
        const auto& name = stage_entry.at("name").get<std::string>();

        if (auto stage_data = createStageData(stage_entry)) {
            stage_data_map.emplace(name, std::move(stage_data));
        }
    }

    return stage_data_map;
}

DefinedTasksGenerator::json DefinedTasksGenerator::parseJsonFile(const std::string& file_path) 
{
    const auto package_share_dir = ament_index_cpp::get_package_share_directory("worm_picker_core");
    std::ifstream file(package_share_dir + file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + package_share_dir + file_path);
    }

    return json::parse(file);
}

DefinedTasksGenerator::StageDataPtr DefinedTasksGenerator::createStageData(const json& stage_entry) 
{
    const auto& type = stage_entry.at("type").get<std::string>();
    const auto& velocity_scaling = stage_entry.at("velocity_scaling").get<double>();
    const auto& acceleration_scaling = stage_entry.at("acceleration_scaling").get<double>();

    if (type == "JOINT") {
        return createJointStageData(stage_entry, velocity_scaling, acceleration_scaling);
    }
    
    if (type == "POINT") {
        const auto& params = stage_entry.at("parameters").get<std::vector<double>>();
        return std::make_shared<MoveToPointData>(
            params[0], params[1], params[2],
            params[3], params[4], params[5], params[6],
            velocity_scaling, acceleration_scaling
        );
    }
    
    if (type == "RELATIVE") {
        const auto& params = stage_entry.at("parameters").get<std::vector<double>>();
        return std::make_shared<MoveRelativeData>(
            params[0], params[1], params[2],
            velocity_scaling, acceleration_scaling
        );
    }

    return nullptr;
}

DefinedTasksGenerator::StageDataPtr DefinedTasksGenerator::createJointStageData(
    const json& stage_entry,
    double velocity_scaling,
    double acceleration_scaling)
{
    const auto& params = stage_entry.at("parameters").get<std::vector<double>>();

    if (stage_entry.contains("joints_to_move")) {
        const auto& joints_to_move = stage_entry.at("joints_to_move").get<std::vector<int>>();
        
        std::map<std::string, double> joint_targets;
        for (const auto joint_num : joints_to_move) {
            joint_targets.emplace("joint_" + std::to_string(joint_num), params[joint_num - 1]);
        }
        return std::make_shared<MoveToJointData>(
            joint_targets, velocity_scaling, acceleration_scaling
        );
    } 
    
    return std::make_shared<MoveToJointData>(
        params[0], params[1], params[2], 
        params[3], params[4], params[5],
        velocity_scaling, acceleration_scaling
    );
}

DefinedTasksGenerator::TaskDataMap DefinedTasksGenerator::parseTasks(
    const StageDataMap& stage_data_map) 
{
    TaskDataMap task_data_map;
    json tasks_json = parseJsonFile(tasks_file_);

    for (const auto& task_entry : tasks_json) {
        const auto& name = task_entry.at("name").get<std::string>();
        const auto& stages = task_entry.at("stages").get<std::vector<std::string>>();

        auto maybe_task = TaskData::create(stage_data_map, stages);
        if (!maybe_task) {
            throw std::runtime_error(
                "Failed to create task: " + name + " - Invalid stage name in configuration");
        }

        task_data_map.emplace(name, std::move(*maybe_task));
    }

    return task_data_map;
}

const DefinedTasksGenerator::TaskDataMap& DefinedTasksGenerator::getDefinedTasksMap() const 
{
    return task_data_map_;
}