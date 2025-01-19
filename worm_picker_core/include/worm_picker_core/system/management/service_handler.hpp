// service_handler.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#ifndef SERVICE_HANDLER_HPP
#define SERVICE_HANDLER_HPP

#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <worm_picker_custom_msgs/srv/task_command.hpp>

#include "worm_picker_core/system/management/task_manager.hpp"
#include "worm_picker_core/system/management/action_client_manager.hpp"

class ServiceHandler {
public:
    using NodePtr = rclcpp::Node::SharedPtr;
    using TaskManagerPtr = std::shared_ptr<TaskManager>;
    using ActionClientManagerPtr = std::shared_ptr<ActionClientManager>;

    ServiceHandler(const NodePtr& node, 
                   const TaskManagerPtr& task_manager, 
                   const ActionClientManagerPtr& action_client_manager);

private:
    using TaskCommandService = worm_picker_custom_msgs::srv::TaskCommand;
    using TaskCommandRequest = TaskCommandService::Request;
    using TaskCommandResponse = TaskCommandService::Response;
    using TaskCommandServicePtr = rclcpp::Service<TaskCommandService>::SharedPtr;

    void handleServiceRequest(const std::shared_ptr<const TaskCommandRequest>& request,
                              const std::shared_ptr<TaskCommandResponse>& response);
    
    NodePtr node_;
    TaskCommandServicePtr service_;
    TaskManagerPtr task_manager_;
    ActionClientManagerPtr action_client_manager_;
};

#endif // SERVICE_HANDLER_HPP
