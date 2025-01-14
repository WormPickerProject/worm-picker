// task_manager.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

#include <rclcpp/rclcpp.hpp>
#include <moveit_msgs/msg/move_it_error_codes.hpp>
#include "worm_picker_core/system/tasks/task_factory.hpp"
#include "worm_picker_core/utils/timer_data_collector.hpp"
#include "worm_picker_core/system/tasks/task_validator.hpp"

class TaskManager {
public:
    using NodePtr = rclcpp::Node::SharedPtr;
    using TaskFactoryPtr = std::shared_ptr<TaskFactory>;
    using TimerDataCollectorPtr = std::shared_ptr<TimerDataCollector>;

    enum class TaskExecutionStatus {
        Success,
        PlanningFailed,
        ExecutionFailed
    };

    TaskManager(const NodePtr& node,
                const TaskFactoryPtr& task_factory,
                const TimerDataCollectorPtr& timer_data_collector);
    TaskExecutionStatus executeTask(const std::string& command) const;

private:
    using Task = moveit::task_constructor::Task;
    using MoveItErrorCodes = moveit_msgs::msg::MoveItErrorCodes;
    using ModeMap = std::unordered_map<std::string, std::string>;
    using TimerResults = std::vector<std::pair<std::string, double>>;
    using TaskValidatorPtr = std::shared_ptr<TaskValidator>;

    TaskExecutionStatus performTask(Task& task,
                                    const std::string& command,
                                    TimerResults& timer_results) const;
    std::optional<std::string> isModeSwitch(const std::string& command) const;
    TaskExecutionStatus checkExecutionResult(const MoveItErrorCodes& result,
                                             const std::string& command) const;

    NodePtr node_;
    TaskFactoryPtr task_factory_;
    TimerDataCollectorPtr timer_data_collector_;
    TaskValidatorPtr task_validator_;
    ModeMap mode_map_;
};

#endif // TASK_MANAGER_HPP
