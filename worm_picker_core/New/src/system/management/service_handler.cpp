// service_handler.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/system/management/service_handler.hpp"
#include "worm_picker_core/utils/parameter_utils.hpp"

ServiceHandler::ServiceHandler(const NodePtr& node, 
                               const TaskManagerPtr& task_manager, 
                               const ActionClientManagerPtr& action_client_manager)
    : node_{node}, 
      task_manager_{task_manager}, 
      action_client_manager_{action_client_manager}
{
    auto service_name = param_utils::getParameter<std::string>(node_, "actions.task_command");

    service_ = node_->create_service<TaskCommandService>(
        *service_name,
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
            auto server_name = param_utils::getParameter<std::string>(node_, "actions.exec_task");
            throw std::runtime_error(
                fmt::format("Action server '{}' is not available", *server_name));
        }

        const auto status = task_manager_->executeTask(request->command);
        response->success = (status == TaskManager::TaskExecutionStatus::Success);

    } catch (const std::exception& e) {
        RCLCPP_ERROR(node_->get_logger(), "Error in handleServiceRequest: %s", e.what());
        response->success = false;
    }
}
