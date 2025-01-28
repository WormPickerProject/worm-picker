// task_manager.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <moveit/planning_scene/planning_scene.h>
#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
#include <moveit/task_constructor/task.h>
#include "worm_picker_core/system/management/task_manager.hpp"
#include "worm_picker_core/utils/parameter_utils.hpp"

TaskManager::TaskManager(const NodePtr& node,
                         const TaskFactoryPtr& task_factory,
                         const TimerDataCollectorPtr& timer_data_collector)
  : node_{node},
    task_factory_{task_factory},
    timer_data_collector_{timer_data_collector},
    task_validator_{std::make_shared<TaskValidator>(node)}
{
    auto plate_mode   = param_utils::getParameter<std::string>(node_, "operation_modes.plate");
    auto worm_mode    = param_utils::getParameter<std::string>(node_, "operation_modes.worm");
    auto plate_factor = param_utils::getParameter<std::string>(node_, "end_effectors.plate_factor");
    auto worm_factor  = param_utils::getParameter<std::string>(node_, "end_effectors.worm_factor");

    mode_map_ = {
        { *plate_mode, *plate_factor },
        { *worm_mode,  *worm_factor }
    };
}

Result<void> TaskManager::executeTask(const std::string& command) const
{
    if (auto effector = isModeSwitch(command)) {
        return param_utils::setParameter(node_, "end_effectors.current_factor", *effector)
            ? Result<void>::success()
            : Result<void>::error("Failed to set end effector parameter");
    }

    TimerResults timer_results;
    auto task_storage = std::make_shared<Task>();

    auto createTaskWithTimer = [&]() -> Result<Task> {
        return measureTime<Task>("Create Task Timer", timer_results, [&]() {
            return task_factory_->createTask(command);
        });
    };
    auto storeCreatedTask = [&](Task& created_task) -> void {
        *task_storage = std::move(created_task);
    };
    auto planTaskWithTimer = [&]() -> Result<void> {
        return measureTime<void>("Plan Task Timer", timer_results, [&]() {
            return planTask(*task_storage);
        });
    };
    auto executeSolutionWithTimer = [&]() -> Result<void> {
        return measureTime<void>("Execute Task Timer", timer_results, [&]() {
            return executeSolution(*task_storage, command);
        });
    };
    auto recordTimerResults = [&]() -> void {
        timer_data_collector_->recordTimerData(command, timer_results);
    };

    return createTaskWithTimer()
        .map(storeCreatedTask)
        .flatMap(planTaskWithTimer)
        .flatMap(executeSolutionWithTimer)
        .map(recordTimerResults);
}

Result<void> TaskManager::planTask(Task& task) const
{
    task.enableIntrospection();
    task.init();
    
    auto plan_attempts = param_utils::getParameter<int>(node_, "settings.planning_attempts");
    return task.plan(*plan_attempts)
        ? Result<void>::success()
        : Result<void>::error("Failed to plan task");
}

Result<void> TaskManager::executeSolution(Task& task,
                                          const std::string& command) const
{
    const auto& sols = task.solutions();
    if (sols.empty()) return Result<void>::error("No solutions found for task");

    auto valid = findValidSolution(task, sols);
    if (!valid.has_value()) return Result<void>::error("No valid solutions found for task");

    task.introspection().publishSolution(*valid.value().get());
    MoveItErrorCodes result = task.execute(*valid.value().get());
    
    if (result.val != MoveItErrorCodes::SUCCESS) return createExecutionError(result, command);
    return Result<void>::success();
}

TaskManager::OptionalSolutionRef 
TaskManager::findValidSolution(const Task& task, const ordered<SolutionPtr>& solutions) const
{
    if (auto it = std::find_if(solutions.begin(), solutions.end(), [&](const auto& sol) {
            return !sol->isFailure() && task_validator_->validateSolution(
                task,
                sol->start()->scene()->getCurrentState(),
                sol->end()->scene()->getCurrentState());
        }); it != solutions.end()) {
        return std::cref(*it);
    }
    return std::nullopt;
}

Result<void> TaskManager::createExecutionError(const MoveItErrorCodes& result,
                                               const std::string& command) const
{
    std::string msg = "Task execution failed for command [" + command +
                      "], code: " + std::to_string(result.val);
    return Result<void>::error(msg);
}

std::optional<std::string> TaskManager::isModeSwitch(const std::string& command) const
{
    auto it = mode_map_.find(command);
    if (it != mode_map_.end()) return it->second;
    return std::nullopt;
}