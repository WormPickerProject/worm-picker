// task_manager.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>

#include "worm_picker_core/tasks/controllers/task_manager.hpp"
#include "worm_picker_core/tools/timing/execution_timer.hpp"

#include "worm_picker_core/tools/task_output.hpp" // Temp 

TaskManager::TaskManager(const NodePtr& node,
                         const TaskFactoryPtr& task_factory,
                         const TimerDataCollectorPtr& timer_data_collector)
    : node_{node}, 
      task_factory_{task_factory}, 
      timer_data_collector_{timer_data_collector}
{
    plate_mode_command_ = node_->get_parameter("plate_mode_command").as_string();
    worm_mode_command_ = node_->get_parameter("worm_mode_command").as_string();
    plate_end_effector_ = node_->get_parameter("plate_end_factor").as_string();
    worm_end_effector_ = node_->get_parameter("worm_end_factor").as_string();

    mode_map_ = {
        {plate_mode_command_, plate_end_effector_},
        {worm_mode_command_, worm_end_effector_}
    };
}

TaskManager::TaskExecutionStatus TaskManager::executeTask(std::string_view command) const 
{
    if (auto new_end_effector = isModeSwitch(command)) {
        const rclcpp::Parameter param("end_effector", *new_end_effector);
        node_->set_parameter(param);
        return TaskExecutionStatus::Success;
    }

    TimerResults timer_results;
    Task task;

    {
        ExecutionTimer create_timer{"Create Task Timer"};
        task = task_factory_->createTask(command);
        timer_results.emplace_back(create_timer.getName(), create_timer.stop());
    }

    const auto status = performTask(task, command, timer_results);
    timer_data_collector_->recordTimerData(std::string(command), timer_results);
    
    return status;
}

TaskManager::TaskExecutionStatus TaskManager::performTask(Task& task,
                                                          std::string_view command,
                                                          TimerResults& timer_results) const 
{
    const auto planning_attempts = node_->get_parameter("planning_attempts").as_int();

    {
        ExecutionTimer plan_timer{"Initialize and Plan Task Timer"};
        task.enableIntrospection();
        task.init();
        if (!task.plan(planning_attempts)) {
            return TaskExecutionStatus::PlanningFailed;
        }
        task_output::outputTaskDetails(task, node_); //Temp
        timer_results.emplace_back(plan_timer.getName(), plan_timer.stop());
    }

    {
        ExecutionTimer execute_timer{"Execute Task Timer"};
        if (task.solutions().empty()) {
            return TaskExecutionStatus::PlanningFailed;
        }

        const auto& solution = *task.solutions().front();
        task.introspection().publishSolution(solution);
        const auto result = task.execute(solution);
        timer_results.emplace_back(execute_timer.getName(), execute_timer.stop());

        return checkExecutionResult(result, command);
    }
}

std::optional<std::string> TaskManager::isModeSwitch(std::string_view command) const
{
    auto it = mode_map_.find(std::string(command));
    if (it != mode_map_.end()) {
        return it->second;
    }
    return std::nullopt;
}

TaskManager::TaskExecutionStatus TaskManager::checkExecutionResult(const MoveItErrorCodes& result,
                                                                   std::string_view command) const
{
    if (result.val != MoveItErrorCodes::SUCCESS) {
        RCLCPP_ERROR(
            node_->get_logger(),
            "Task execution failed: %s (code: %d)", command.data(), result.val
        );
        return TaskExecutionStatus::ExecutionFailed;
    }
    return TaskExecutionStatus::Success;
}
