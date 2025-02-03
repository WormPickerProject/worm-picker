// service_handler.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <tf2_eigen/tf2_eigen.hpp>
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

    tf_buffer_ = std::make_shared<tf2_ros::Buffer>(node_->get_clock());
    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
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
    response->feedback = formatPose(getCurrentPose());
}

std::optional<ServiceHandler::Pose> ServiceHandler::getCurrentPose() const
{ 
    auto transform = tf_buffer_->lookupTransform(
        *param_utils::getParameter<std::string>(node_, "frames.base_link"),
        *param_utils::getParameter<std::string>(node_, "end_effectors.current_factor"),
        tf2::TimePointZero,
        std::chrono::milliseconds(100)
    );

    geometry_msgs::msg::PoseStamped pose;
    pose.header = transform.header;
    pose.pose.position.x = transform.transform.translation.x;
    pose.pose.position.y = transform.transform.translation.y;
    pose.pose.position.z = transform.transform.translation.z;
    pose.pose.orientation = transform.transform.rotation;
    return pose;
}

const std::string ServiceHandler::formatPose(const std::optional<Pose>& maybe_pose) 
{
    if (!maybe_pose) {
        return "position:{9999.90000,9999.90000,9999.90000} "
               "orientation:{9999.90000,9999.90000,9999.90000,9999.90000}";
    }

    const auto& [x, y, z] = maybe_pose->pose.position;
    const auto& [qx, qy, qz, qw] = maybe_pose->pose.orientation;
    
    return fmt::format(
        "position:{{{:.5f},{:.5f},{:.5f}}} orientation:{{{:.5f},{:.5f},{:.5f},{:.5f}}}",
        x, y, z, qx, qy, qz, qw
    );
}