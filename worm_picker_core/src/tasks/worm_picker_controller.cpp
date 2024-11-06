// worm_picker_controller.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tasks/worm_picker_controller.hpp"

WormPickerController::WormPickerController(const rclcpp::NodeOptions& options)
    : worm_picker_node_{std::make_shared<rclcpp::Node>(NODE_NAME, options)},
      task_factory_{std::make_shared<TaskFactory>(worm_picker_node_)},
      timer_data_collector_{std::make_shared<TimerDataCollector>(TIMER_LOG_PATH)}
{
    declareParameters();
    setupServicesAndActions();
}

void WormPickerController::declareParameters()
{
    const std::vector<std::pair<std::string, rclcpp::ParameterValue>> default_parameters{
        {"action_server_timeout_sec", rclcpp::ParameterValue(3)},
        {"max_retries", rclcpp::ParameterValue(10)},
        {"planning_attempts", rclcpp::ParameterValue(5)}
    };

    for (const auto& [name, default_value] : default_parameters) {
        worm_picker_node_->declare_parameter(name, default_value);
    }
}

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr WormPickerController::getBaseInterface() 
{
    return worm_picker_node_->get_node_base_interface();
}

void WormPickerController::setupServicesAndActions() 
{
    execute_task_action_client_ = rclcpp_action::create_client<ExecuteTaskSolutionAction>(
        worm_picker_node_,
        EXECUTE_TASK_ACTION_NAME
    );

    execute_task_wait_thread_ = std::jthread(&WormPickerController::waitForActionServer, this);

    task_command_service_ = worm_picker_node_->create_service<TaskCommandService>(
        TASK_COMMAND_SERVICE_NAME,
        [this](std::shared_ptr<const TaskCommandRequest> request,
               std::shared_ptr<TaskCommandResponse> response) {
            handleTaskCommand(request, response);
        }
    );
}

void WormPickerController::waitForActionServer() 
{
    const int max_retries = worm_picker_node_->get_parameter("max_retries").as_int();
    const int timeout_sec = worm_picker_node_->get_parameter("action_server_timeout_sec").as_int();
    int retry_count = 0;

    while (rclcpp::ok() && retry_count < max_retries) {
        if (execute_task_action_client_->wait_for_action_server(std::chrono::seconds(timeout_sec))) {
            server_ready_.store(true);
            break;
        } 
        retry_count++;
    }
}

void WormPickerController::handleTaskCommand(
    std::shared_ptr<const TaskCommandRequest> request,
    std::shared_ptr<TaskCommandResponse> response) 
{
    try {
        if (!server_ready_.load()) {
            throw ActionServerUnavailableException(
                "Action server '" + std::string(EXECUTE_TASK_ACTION_NAME) + "' is not available."
            );
        }

        const auto status = doTask(request->command);
        response->success = (status == TaskExecutionStatus::Success);
    } catch (const std::exception& e) {
        RCLCPP_ERROR(worm_picker_node_->get_logger(), "Error in handleTaskCommand: %s", e.what());
        response->success = false;
    }
}

WormPickerController::TaskExecutionStatus WormPickerController::doTask(std::string_view command) 
{
    const auto planning_attempts = worm_picker_node_->get_parameter("planning_attempts").as_int();
    std::vector<std::pair<std::string, double>> timer_results;
    moveit_msgs::msg::MoveItErrorCodes execution_result;

    {
        ExecutionTimer timer("Create Task Timer");
        current_task_ = task_factory_->createTask(std::string(command));
        timer_results.emplace_back(timer.getName(), timer.stop());
    }

    {
        ExecutionTimer timer("Initialize Task Timer");
        current_task_.init();
        timer_results.emplace_back(timer.getName(), timer.stop());
    }

    {
        ExecutionTimer timer("Plan Task Timer");
        if (!current_task_.plan(planning_attempts)) {
            return TaskExecutionStatus::PlanningFailed;
        }
        timer_results.emplace_back(timer.getName(), timer.stop());
    }

    {
        ExecutionTimer timer("Execute Task Timer");
        if (current_task_.solutions().empty()) {
            return TaskExecutionStatus::PlanningFailed;
        }

        current_task_.introspection().publishSolution(*current_task_.solutions().front());
        execution_result = current_task_.execute(*current_task_.solutions().front());
        timer_results.emplace_back(timer.getName(), timer.stop());
    }

    timer_data_collector_->recordTimerData(std::string(command), timer_results);
    return checkExecutionResult(execution_result, command);
}

WormPickerController::TaskExecutionStatus WormPickerController::checkExecutionResult(
    const moveit_msgs::msg::MoveItErrorCodes& result,
    std::string_view command) 
{
    if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
        RCLCPP_ERROR(
            worm_picker_node_->get_logger(),
            "Task execution failed: %s (code: %d)", std::string(command).c_str(), result.val
        );
        return TaskExecutionStatus::ExecutionFailed;
    }
    return TaskExecutionStatus::Success;
}

int main(int argc, char **argv) 
{
    rclcpp::init(argc, argv);

    auto worm_picker_controller = std::make_shared<WormPickerController>(
        rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));
    
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(worm_picker_controller->getBaseInterface());

    executor.spin();

    executor.remove_node(worm_picker_controller->getBaseInterface());
    rclcpp::shutdown();

    return 0;
}