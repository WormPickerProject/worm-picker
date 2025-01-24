// service_handler.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <moveit/planning_scene/planning_scene.h>
#include <worm_picker_custom_msgs/srv/task_command.hpp>
#include "worm_picker_core/system/management/task_manager.hpp"
#include "worm_picker_core/system/management/action_client_manager.hpp"

class ServiceHandler {
public:
    using NodePtr = rclcpp::Node::SharedPtr;

    ServiceHandler(NodePtr node, 
                   std::shared_ptr<TaskManager> task_manager,
                   std::shared_ptr<ActionClientManager> action_client_manager);

private:
    using TaskCommandService = worm_picker_custom_msgs::srv::TaskCommand;
    using TaskCommandRequest = TaskCommandService::Request;
    using TaskCommandResponse = TaskCommandService::Response;

    void handleServiceRequest(const std::shared_ptr<const TaskCommandRequest>& request,
                              const std::shared_ptr<TaskCommandResponse>& response);
    std::optional<geometry_msgs::msg::PoseStamped> getCurrentPose() const;
    
    NodePtr node_;
    rclcpp::Service<TaskCommandService>::SharedPtr service_;
    std::shared_ptr<TaskManager> task_manager_;
    std::shared_ptr<ActionClientManager> action_client_manager_;
    rclcpp::Subscription<moveit_msgs::msg::PlanningScene>::SharedPtr planning_scene_sub_;
    std::shared_ptr<planning_scene::PlanningScene> current_scene_;
    mutable std::mutex scene_mutex_;
};