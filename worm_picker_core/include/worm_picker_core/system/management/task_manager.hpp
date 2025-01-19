// task_manager.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <moveit_msgs/msg/move_it_error_codes.hpp>
#include "worm_picker_core/core/result.hpp"
#include "worm_picker_core/system/tasks/task_factory.hpp"
#include "worm_picker_core/system/tasks/task_validator.hpp"
#include "worm_picker_core/utils/scoped_timer.hpp"
#include "worm_picker_core/utils/timer_data_collector.hpp"

class TaskManager {
public:
    using NodePtr = rclcpp::Node::SharedPtr;
    using TaskFactoryPtr = std::shared_ptr<TaskFactory>;
    using TimerDataCollectorPtr = std::shared_ptr<TimerDataCollector>;

    TaskManager(const NodePtr& node,
                const TaskFactoryPtr& task_factory,
                const TimerDataCollectorPtr& timer_data_collector);
    Result<void> executeTask(const std::string& command) const;

private:
    using Task = moveit::task_constructor::Task;
    using MoveItErrorCodes = moveit_msgs::msg::MoveItErrorCodes;
    using ModeMap = std::unordered_map<std::string, std::string>;
    using TimerResults = std::vector<std::pair<std::string, double>>;
    using TaskValidatorPtr = std::shared_ptr<TaskValidator>;
    using SolutionPtr = moveit::task_constructor::SolutionBaseConstPtr;
    using OptionalSolutionRef = std::optional<std::reference_wrapper<const SolutionPtr>>;

    Result<void> planTask(Task& task) const;
    Result<void> executeSolution(Task& task, const std::string& command) const;
    OptionalSolutionRef findValidSolution(const Task& task, 
                                          const ordered<SolutionPtr>& solutions) const;
    Result<void> createExecutionError(const MoveItErrorCodes& result,
                                      const std::string& command) const;
    std::optional<std::string> isModeSwitch(const std::string& command) const;
    template <typename T, typename Func>
    Result<T> measureTime(const std::string& timer_name,
                          TimerResults& timer_results,
                          Func&& func) const {
        ScopedTimer timer(timer_name, timer_results);
        return func();
    }

    NodePtr node_;
    TaskFactoryPtr task_factory_;
    TimerDataCollectorPtr timer_data_collector_;
    TaskValidatorPtr task_validator_;
    ModeMap mode_map_;
};