// service_handler.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tasks/controllers/service_handler.hpp"

ServiceHandler::ServiceHandler(const NodePtr& node, 
                               const TaskManagerPtr& task_manager, 
                               const ActionClientManagerPtr& action_client_manager)
    : node_{node}, 
      task_manager_{task_manager}, 
      action_client_manager_{action_client_manager}
{
    const auto service_name = node_->get_parameter("task_command_service_name").as_string();

    service_ = node_->create_service<TaskCommandService>(
        service_name,
        [this](const std::shared_ptr<const TaskCommandRequest>& request,
               const std::shared_ptr<TaskCommandResponse>& response) {
            handleServiceRequest(request, response);
        }
    );
}

void ServiceHandler::handleServiceRequest(const std::shared_ptr<const TaskCommandRequest>& request,
                                          const std::shared_ptr<TaskCommandResponse>& response) 
{
    try {
        if (!action_client_manager_->isServerAvailable()) {
            const auto server_name = 
                node_->get_parameter("exec_task_action_name").as_string();
            throw std::runtime_error(
                fmt::format("Action server '{}' is not available", server_name));
        }

        const auto status = task_manager_->executeTask(request->command);
        response->success = (status == TaskManager::TaskExecutionStatus::Success);

    } catch (const std::exception& e) {
        RCLCPP_ERROR(node_->get_logger(), "Error in handleServiceRequest: %s", e.what());
        response->success = false;
    }
}
