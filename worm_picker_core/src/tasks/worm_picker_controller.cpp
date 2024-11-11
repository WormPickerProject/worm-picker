// worm_picker_controller.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tasks/worm_picker_controller.hpp"

WormPickerController::WormPickerController(const rclcpp::NodeOptions& options) 
    : worm_picker_node_{std::make_shared<rclcpp::Node>(std::string(NODE_NAME), options)}
{
    declareParameters();

    task_factory_ = std::make_shared<TaskFactory>(worm_picker_node_);
    timer_data_collector_ = std::make_shared<TimerDataCollector>(std::string(TIMER_LOG_PATH));
    
    setupServicesAndActions();
}

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr WormPickerController::getBaseInterface()
{
    return worm_picker_node_->get_node_base_interface();
}

void WormPickerController::declareParameters() 
{
    const std::vector<std::pair<std::string, rclcpp::ParameterValue>> default_parameters{
        {"workstation_config_file", 
         rclcpp::ParameterValue(std::string(CONFIG_PATH) + "/workstation_data.json")},
        {"hotel_config_file", 
         rclcpp::ParameterValue(std::string(CONFIG_PATH) + "/hotel_data.json")}, 
        {"defined_stages_file", 
         rclcpp::ParameterValue(std::string(CONFIG_PATH) + "/defined_stages.json")},
        {"defined_tasks_file", 
         rclcpp::ParameterValue(std::string(CONFIG_PATH) + "/defined_tasks.json")},
        {"action_server_timeout_sec", rclcpp::ParameterValue(3)},
        {"max_retries", rclcpp::ParameterValue(10)},
        {"planning_attempts", rclcpp::ParameterValue(5)},
        {"end_effector", rclcpp::ParameterValue(std::string("eoat_tcp"))}
    };

    for (const auto& [name, value] : default_parameters) {
        worm_picker_node_->declare_parameter(name, value);
    }
}

void WormPickerController::setupServicesAndActions() 
{
    execution_action_client_ = rclcpp_action::create_client<ExecTaskSolutionAction>(
        worm_picker_node_,
        std::string(EXECUTE_TASK_ACTION_NAME)
    );

    wait_thread_ = std::jthread([this] { waitForActionServer(); });

    task_service_ = worm_picker_node_->create_service<TaskCommandService>(
        std::string(TASK_COMMAND_SERVICE_NAME),
        [this](std::shared_ptr<const TaskCommandRequest> request,
               std::shared_ptr<TaskCommandResponse> response) {
            handleTaskCommand(request, response);
        }
    );
}

void WormPickerController::waitForActionServer() 
{
    using namespace std::chrono_literals;

    const auto max_retries = worm_picker_node_->get_parameter("max_retries").as_int();
    const auto timeout = std::chrono::seconds{
        worm_picker_node_->get_parameter("action_server_timeout_sec").as_int()
    };
    
    int retry_count = 0;
    while (rclcpp::ok() && retry_count < max_retries) {
        if (execution_action_client_->wait_for_action_server(timeout)) {
            server_ready_.store(true);
            break;
        } 
        retry_count++;
    }
}

void WormPickerController::handleTaskCommand(std::shared_ptr<const TaskCommandRequest> request,
                                             std::shared_ptr<TaskCommandResponse> response) 
{
    try {
        if (!server_ready_.load()) {
            throw std::runtime_error(
                fmt::format("Action server '{}' is not available.", EXECUTE_TASK_ACTION_NAME)
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
    if (auto new_end_effector = isModeSwitch(command)) {
        worm_picker_node_->set_parameter(
            rclcpp::Parameter("end_effector", std::string(*new_end_effector))
        );
        return TaskExecutionStatus::Success;
    }
    
    const auto planning_attempts = worm_picker_node_->get_parameter("planning_attempts").as_int();
    std::vector<std::pair<std::string, double>> timer_results;
    moveit_msgs::msg::MoveItErrorCodes execution_result;

    {
        auto create_timer = ExecutionTimer{"Create Task Timer"};
        current_task_ = task_factory_->createTask(command);
        timer_results.emplace_back(create_timer.getName(), create_timer.stop());
    }

    {
        auto plan_timer = ExecutionTimer{"Initialize and Plan Task Timer"};
        current_task_.init();
        if (!current_task_.plan(planning_attempts)) {
            return TaskExecutionStatus::PlanningFailed;
        }
        timer_results.emplace_back(plan_timer.getName(), plan_timer.stop());
    }

    {
        auto execute_timer = ExecutionTimer{"Execute Task Timer"};
        if (current_task_.solutions().empty()) {
            return TaskExecutionStatus::PlanningFailed;
        }

        const auto& solution = *current_task_.solutions().front();
        current_task_.introspection().publishSolution(solution);
        execution_result = current_task_.execute(solution);
        timer_results.emplace_back(execute_timer.getName(), execute_timer.stop());
    }

    timer_data_collector_->recordTimerData(std::string(command), timer_results);
    return checkExecutionResult(execution_result, command);
}

std::optional<std::string_view> WormPickerController::isModeSwitch(std::string_view command) 
{
    static const std::unordered_map<std::string_view, std::string_view> mode_map = {
        {PLATE_MODE_COMMAND, EOAT_TCP},
        {WORM_MODE_COMMAND, WORMPICKER_TCP}
    };

    if (auto it = mode_map.find(command); it != mode_map.end()) {
        return it->second;
    }
    return std::nullopt;
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
