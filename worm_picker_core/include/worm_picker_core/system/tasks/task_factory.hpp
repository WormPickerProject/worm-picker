// task_factory.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef TASK_FACTORY_HPP
#define TASK_FACTORY_HPP

#include <fmt/format.h>
#include <rclcpp/rclcpp.hpp>
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/stages.h>
#include "worm_picker_core/core/tasks/task_data.hpp"

class TaskFactory {
public:
   using Task = moveit::task_constructor::Task;
   using NodePtr = rclcpp::Node::SharedPtr;

    explicit TaskFactory(const NodePtr& node);
    Task createTask(const std::string& command);

private:
    using CurrentStateStage = moveit::task_constructor::stages::CurrentState;
    using TrajectoryExecutionInfo = moveit::task_constructor::TrajectoryExecutionInfo;
    using TaskDataMap = std::unordered_map<std::string, TaskData>;

    void initializeTaskMap();
    Task createBaseTask(const std::string& command);
    void logTaskMap();
    void logCreatedTask(const std::string& command, const TaskData& task_data);
 
    NodePtr node_;
    TaskDataMap task_data_map_;
};

#endif // TASK_FACTORY_HPP
