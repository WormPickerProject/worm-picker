// service_handler.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <tf2_eigen/tf2_eigen.hpp>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include "worm_picker_core/system/management/service_handler.hpp"
#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/core/result.hpp"

ServiceHandler::ServiceHandler(NodePtr node, 
                               std::shared_ptr<TaskManager> task_manager,
                               std::shared_ptr<ActionClientManager> action_client_manager)
    : node_{node}, 
      task_manager_{task_manager}, 
      action_client_manager_{action_client_manager}
{
    auto service_name = param_utils::getParameter<std::string>(node_, "actions.task_command");
    service_ = node_->create_service<TaskCommandService>(
        *service_name, [this](const std::shared_ptr<const TaskCommandRequest>& request,
                              const std::shared_ptr<TaskCommandResponse>& response) {
            handleServiceRequest(request, response);
        }
    );

    auto mon_scene_topic = param_utils::getParameter<std::string>(node_, "actions.scene_topic");
    auto queue_size = param_utils::getParameter<int>(node_, "settings.planning_scene_queue_size");
    planning_scene_sub_ = node_->create_subscription<moveit_msgs::msg::PlanningScene>(
        *mon_scene_topic, *queue_size, [this](moveit_msgs::msg::PlanningScene::SharedPtr msg) { 
            std::lock_guard lock(scene_mutex_);
            if (current_scene_) current_scene_->usePlanningSceneMsg(*msg);
        }
    );

    using RML = robot_model_loader::RobotModelLoader;
    auto loader = std::make_shared<RML>(node_, "robot_description");
    current_scene_ = std::make_unique<planning_scene::PlanningScene>(loader->getModel());
}

void ServiceHandler::handleServiceRequest(const std::shared_ptr<const TaskCommandRequest>& request,
                                          const std::shared_ptr<TaskCommandResponse>& response) 
{
    response->success = false;
    if (!action_client_manager_->isServerAvailable()) {
        auto server_name = param_utils::getParameter<std::string>(node_, "actions.exec_task");
        response->feedback = fmt::format("Action server '{}' is not available", *server_name);
        return;
    }

    auto status = task_manager_->executeTask(request->command);
    if (!status.isSuccess()) {
        response->feedback = status.error();
        return;
    }

    response->success = true;
    auto pose = getCurrentPose();
    response->feedback = fmt::format(
        "position:{{{:.5f},{:.5f},{:.5f}}} orientation:{{{:.5f},{:.5f},{:.5f},{:.5f}}}",
        pose ? pose->pose.position.x : 9999.9,
        pose ? pose->pose.position.y : 9999.9, 
        pose ? pose->pose.position.z : 9999.9,
        pose ? pose->pose.orientation.x : 9999.9,
        pose ? pose->pose.orientation.y : 9999.9,
        pose ? pose->pose.orientation.z : 9999.9,
        pose ? pose->pose.orientation.w : 9999.9);
}

std::optional<geometry_msgs::msg::PoseStamped> ServiceHandler::getCurrentPose() const
{
   std::lock_guard lock(scene_mutex_);
   if (!current_scene_) {
       RCLCPP_ERROR(node_->get_logger(), "No scene available");
       return std::nullopt;
   }

   geometry_msgs::msg::PoseStamped pose;
   pose.header.frame_id = current_scene_->getPlanningFrame();
   pose.header.stamp = node_->get_clock()->now();
   pose.pose = tf2::toMsg(current_scene_->getCurrentState().getGlobalLinkTransform(
           *param_utils::getParameter<std::string>(node_, "end_effectors.current_factor")
       )
   );
   return pose;
}