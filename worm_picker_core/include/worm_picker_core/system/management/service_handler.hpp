// service_handler.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <worm_picker_custom_msgs/srv/task_command.hpp>
#include "worm_picker_core/core/result.hpp"
#include "worm_picker_core/system/tasks/task_factory.hpp"
#include "worm_picker_core/system/management/task_manager.hpp"
#include "worm_picker_core/system/management/action_client_manager.hpp"

class ServiceHandler {
public:
    using NodePtr = rclcpp::Node::SharedPtr;

    ServiceHandler(NodePtr node, 
                   std::shared_ptr<TaskFactory> task_factory,
                   std::shared_ptr<TaskManager> task_manager,
                   std::shared_ptr<ActionClientManager> action_client_manager);

private:
    static constexpr const char* GET_PREFIX = "get:";
    
    using TaskCommandService = worm_picker_custom_msgs::srv::TaskCommand;
    using TaskCommandRequest = TaskCommandService::Request;
    using TaskCommandResponse = TaskCommandService::Response;
    using Pose = geometry_msgs::msg::PoseStamped;

    void handleServiceRequest(const std::shared_ptr<const TaskCommandRequest>& request,
                              const std::shared_ptr<TaskCommandResponse>& response);
    Result<Pose> handleGetRequest(const std::string& command);
    const std::string extractTaskKey(const std::string& command) const;
    std::optional<Pose> getCurrentPose() const;
    const std::string formatPose(const std::optional<Pose>& maybe_pose);
    
    NodePtr node_;
    rclcpp::Service<TaskCommandService>::SharedPtr service_;
    std::shared_ptr<TaskFactory> task_factory_;
    std::shared_ptr<TaskManager> task_manager_;
    std::shared_ptr<ActionClientManager> action_client_manager_;
    std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
};