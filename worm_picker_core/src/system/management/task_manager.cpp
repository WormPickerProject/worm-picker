// task_manager.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>

#include "worm_picker_core/system/management/task_manager.hpp"
#include "worm_picker_core/utils/execution_timer.hpp"
#include "worm_picker_core/utils/parameter_utils.hpp"

TaskManager::TaskManager(const NodePtr& node,
                         const TaskFactoryPtr& task_factory,
                         const TimerDataCollectorPtr& timer_data_collector)
    : node_{node}, 
      task_factory_{task_factory}, 
      timer_data_collector_{timer_data_collector},
      task_validator_{std::make_shared<TaskValidator>(node)}

{
    auto plate_mode = param_utils::getParameter<std::string>(node_, "operation_modes.plate");
    auto worm_mode = param_utils::getParameter<std::string>(node_, "operation_modes.worm");
    auto plate_factor = param_utils::getParameter<std::string>(node_, "end_effectors.plate_factor");
    auto worm_factor = param_utils::getParameter<std::string>(node_, "end_effectors.worm_factor");

    if (!plate_mode || !worm_mode || !plate_factor || !worm_factor) {
        throw std::runtime_error("Required parameters not found");
    }

    mode_map_ = {
        {*plate_mode, *plate_factor},
        {*worm_mode, *worm_factor}
    };
}

TaskManager::TaskExecutionStatus TaskManager::executeTask(const std::string& command) const 
{
    if (auto new_end_effector = isModeSwitch(command)) {
        if (!param_utils::setParameter(node_, "end_effectors.current_factor", *new_end_effector)) {
            return TaskExecutionStatus::ExecutionFailed;
        }
        return TaskExecutionStatus::Success;
    }

    TimerResults timer_results;
    Task task;

    {
        ExecutionTimer create_timer{"Create Task Timer"};
        task = task_factory_->createTask(command);
        timer_results.emplace_back(create_timer.getName(), create_timer.stop());
    }

    const auto& status = performTask(task, command, timer_results);
    timer_data_collector_->recordTimerData(command, timer_results);
    
    return status;
}

TaskManager::TaskExecutionStatus TaskManager::performTask(Task& task,
                                                          const std::string& command,
                                                          TimerResults& timer_results) const 
{
    auto planning_attempts = param_utils::getParameter<int>(node_, "settings.planning_attempts");

    {
        ExecutionTimer plan_timer{"Initialize and Plan Task Timer"};
        task.enableIntrospection();
        task.init();
        if (!task.plan(*planning_attempts)) {
            return TaskExecutionStatus::PlanningFailed;
        }
        timer_results.emplace_back(plan_timer.getName(), plan_timer.stop());
    }

    {
        ExecutionTimer execute_timer{"Execute Task Timer"};
        const auto& solutions = task.solutions();
        if (solutions.empty()) {
            return TaskExecutionStatus::PlanningFailed;
        }

        auto stage = task.stages().back();
        auto it = std::find_if(solutions.begin(), solutions.end(), 
            [this, &stage](const auto& solution) {
                if (solution->isFailure()) {
                    return false;
                }
                return task_validator_->validateSolution(
                    stage,
                    solution->trajectory()->getFirstWayPoint(),
                    solution->trajectory()->getLastWayPoint()
                );
            });

        if (it == solutions.end()) {
            return TaskExecutionStatus::PlanningFailed;
        }

        const auto& valid_solution = *it;
        task.introspection().publishSolution(valid_solution);
        const auto result = task.execute(valid_solution);

        timer_results.emplace_back(execute_timer.getName(), execute_timer.stop());
        return checkExecutionResult(result, command);
    }
}

std::optional<std::string> TaskManager::isModeSwitch(const std::string& command) const
{
    auto it = mode_map_.find(command);
    if (it != mode_map_.end()) {
        return it->second;
    }
    return std::nullopt;
}

TaskManager::TaskExecutionStatus TaskManager::checkExecutionResult(const MoveItErrorCodes& result,
                                                                   const std::string& command) const
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
