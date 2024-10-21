// worm_picker_controller.cpp
//
// Copyright (c)
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
//
// Licensed under the Apache License, Version 2.0 (the "License");

#include "worm_picker_core/tasks/worm_picker_controller.hpp"

WormPickerController::WormPickerController(const rclcpp::NodeOptions& options) 
    : worm_picker_node_{ std::make_shared<rclcpp::Node>("worm_picker_controller", options) },
      task_factory_{ std::make_shared<TaskFactory>(worm_picker_node_) },
      timer_data_collector_{ std::make_shared<TimerDataCollector>("/worm-picker/worm_picker_core/timer_log") }
{
    setupServicesAndActions();
}

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr WormPickerController::getBaseInterface() 
{
    return worm_picker_node_->get_node_base_interface();
}

void WormPickerController::setupServicesAndActions() 
{
    execute_task_action_client_ = rclcpp_action::create_client<ExecuteTaskSolutionAction>(
        worm_picker_node_, "/execute_task_solution"
    );

    execute_task_wait_thread_ = std::jthread(&WormPickerController::waitForActionServer, this);

    task_command_service_ = worm_picker_node_->create_service<TaskCommandService>(
        "/task_command",
        [this](const std::shared_ptr<TaskCommandRequest> request, 
               std::shared_ptr<TaskCommandResponse> response) {
            handleTaskCommand(request, response);
        }
    );
}

void WormPickerController::waitForActionServer() 
{
    int retry_count = 0;
    const int max_retries = 10;

    while (rclcpp::ok() && retry_count < max_retries) {
        if (execute_task_action_client_->wait_for_action_server(std::chrono::seconds(3))) {
            break;
        } else {
            retry_count++;
        }
    }
}

void WormPickerController::handleTaskCommand(const std::shared_ptr<TaskCommandRequest> request,
                                             std::shared_ptr<TaskCommandResponse> response) 
{
    try {
        if (!execute_task_action_client_->wait_for_action_server(std::chrono::seconds(0))) {
            throw ActionServerUnavailableException("Action server '/execute_task_solution' is not available.");
        }

        doTask(request->command);
        response->success = true;
    } catch (const std::exception& e) {
        RCLCPP_ERROR(worm_picker_node_->get_logger(), "Error in handleTaskCommand: %s", e.what());
        response->success = false;
    }
}

void WormPickerController::doTask(const std::string& command) 
{
    std::vector<std::pair<std::string, double>> timer_results;
    moveit_msgs::msg::MoveItErrorCodes execution_result;

    {
        ExecutionTimer timer("Create Task Timer");
        current_task_ = task_factory_->createTask(command);
        timer_results.emplace_back(timer.getName(), timer.stop());
    }

    {
        ExecutionTimer timer("Initialize Task Timer");
        current_task_.init();
        timer_results.emplace_back(timer.getName(), timer.stop());
    }

    {
        ExecutionTimer timer("Plan Task Timer");
        if (!current_task_.plan(5)) {
            throw TaskPlanningFailedException("Task planning failed for command: " + command);
        }
        timer_results.emplace_back(timer.getName(), timer.stop());
    }

    {
        ExecutionTimer timer("Execute Task Timer");
        if (current_task_.solutions().empty()) {
            throw TaskExecutionFailedException("No solutions found for task execution for command: " + command, -1);
        }

        current_task_.introspection().publishSolution(*current_task_.solutions().front());
        execution_result = current_task_.execute(*current_task_.solutions().front());
        timer_results.emplace_back(timer.getName(), timer.stop());
    }

    timer_data_collector_->recordTimerData(command, timer_results);

    if (execution_result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
        throw TaskExecutionFailedException("Task execution failed with error code: " + std::to_string(execution_result.val) + " for command: " + command, execution_result.val);
    }
}

int main(int argc, char **argv) 
{
    rclcpp::init(argc, argv);

    auto worm_picker_node = std::make_shared<WormPickerController>(
        rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));
    rclcpp::executors::MultiThreadedExecutor executor;

    executor.add_node(worm_picker_node->getBaseInterface());
    executor.spin();
    executor.remove_node(worm_picker_node->getBaseInterface());

    worm_picker_node.reset();
    return 0;
}