// task_manager.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>

#include <moveit/task_constructor/stage.h>
#include <moveit/task_constructor/properties.h>
#include <moveit/planning_scene/planning_scene.h>
#include <moveit/robot_state/robot_state.h>
#include <moveit/task_constructor/storage.h>

#include "worm_picker_core/system/management/task_manager.hpp"
#include "worm_picker_core/utils/scoped_timer.hpp"
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
        ScopedTimer timer("Create Task Timer", timer_results);
        task = task_factory_->createTask(command);
    }

    const auto& status = performTask(task, command, timer_results);
    timer_data_collector_->recordTimerData(command, timer_results);
    
    return status;
}

TaskManager::TaskExecutionStatus TaskManager::performTask(Task& task,
                                                          const std::string& command,
                                                          TimerResults& timer_results) const 
{
    {
        ScopedTimer timer("Plan Task Timer", timer_results);
        if (auto status = planTask(task); status != TaskExecutionStatus::Success) {
            return status;
        }
    }
    {
        ScopedTimer timer("Execute Task Timer", timer_results);
        return executeTask(task, command);
    }
}

TaskManager::TaskExecutionStatus TaskManager::planTask(Task& task) const 
{
    task.enableIntrospection();
    task.init();
    
    auto planning_attempts = param_utils::getParameter<int>(node_, "settings.planning_attempts");
    if (!task.plan(*planning_attempts)) {
        return TaskExecutionStatus::PlanningFailed;
    }
    
    return TaskExecutionStatus::Success;
} 

TaskManager::TaskExecutionStatus TaskManager::executeTask(Task& task,
                                                          const std::string& command) const 
{
    const auto& solutions = task.solutions();
    if (solutions.empty()) {
        return TaskExecutionStatus::PlanningFailed;
    }
    auto valid_solution = findValidSolution(task, solutions);
    if (!valid_solution) {
        return TaskExecutionStatus::PlanningFailed;
    }
    task.introspection().publishSolution(*valid_solution->get());
    const auto result = task.execute(*valid_solution->get());
    
    return checkExecutionResult(result, command);
}

TaskManager::OptionalSolutionRef 
TaskManager::findValidSolution(const Task& task, const ordered<SolutionPtr>& solutions) const 
{
    if (auto it = std::find_if(solutions.begin(), solutions.end(), [&](const auto& solution) {
            return !solution->isFailure() && task_validator_->validateSolution(
                task,
                solution->start()->scene()->getCurrentState(),
                solution->end()->scene()->getCurrentState());
        }); it != solutions.end()) {
        return std::cref(*it);
    }
    return std::nullopt;
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
