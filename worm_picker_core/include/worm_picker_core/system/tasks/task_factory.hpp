// task_factory.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <fmt/format.h>
#include <rclcpp/rclcpp.hpp>
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/stages.h>
#include "worm_picker_core/core/result.hpp"
#include "worm_picker_core/core/tasks/task_data.hpp"
#include "worm_picker_core/core/commands/parser/control_command_parser.hpp"
#include "worm_picker_core/infrastructure/parsers/workstation_data_parser.hpp"
#include "worm_picker_core/infrastructure/parsers/hotel_data_parser.hpp"

class TaskFactory {
public:
    using Task = moveit::task_constructor::Task;
    using NodePtr = rclcpp::Node::SharedPtr;

    explicit TaskFactory(const NodePtr& node);
    Result<Task> createTask(const std::string& command);
    const std::unordered_map<std::string, TaskData>& getTaskDataMap() const;

private:
    using CurrentStateStage = moveit::task_constructor::stages::CurrentState;
    using TrajectoryExecutionInfo = moveit::task_constructor::TrajectoryExecutionInfo;
    using TaskDataMap = std::unordered_map<std::string, TaskData>;
    using SpeedOverride = std::pair<double, double>;
    using WorkstationDataMap = std::unordered_map<std::string, WorkstationData>;
    using HotelDataMap = std::unordered_map<std::string, HotelData>;

    void initializeTaskMap();
    WorkstationDataMap loadWorkstationData();
    HotelDataMap loadHotelData();
    void loadDefinedTasks(const WorkstationDataMap& workstation, const HotelDataMap& hotel);

    Task createBaseTask(const std::string& command);
    Result<TaskData> fetchTaskData(const CommandInfo& info);
    void applySpeedOverrides(TaskData& task_data, const SpeedOverride& override);
    Task configureTaskWithStages(Task task, const TaskData& task_data, const std::string& command);

    void logTaskMap();
    void logCreatedTask(const std::string& command, const TaskData& task_data);

    NodePtr node_;
    std::unique_ptr<ControlCommandParser> control_command_parser_;
    TaskDataMap task_data_map_;
};