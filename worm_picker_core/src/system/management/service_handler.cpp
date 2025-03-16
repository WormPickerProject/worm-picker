// service_handler.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <tf2_eigen/tf2_eigen.hpp>
#include "worm_picker_core/system/management/service_handler.hpp"
#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_point_data.hpp"

ServiceHandler::ServiceHandler(NodePtr node, 
                               std::shared_ptr<TaskFactory> task_factory,
                               std::shared_ptr<TaskManager> task_manager,
                               std::shared_ptr<ActionClientManager> action_client_manager)
  : node_{node}, 
    task_factory_{task_factory},
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

    const std::string& command = request->command;
    if (command.starts_with(GET_PREFIX)) {
        auto pose = handleGetRequest(command);
        response->success = pose.isSuccess();
        response->feedback = pose.isSuccess() ? formatPose(pose.value()) : pose.error();
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

Result<ServiceHandler::Pose> ServiceHandler::handleGetRequest(const std::string& command) 
{
    const std::string task_key = extractTaskKey(command);
    
    const auto& task_data_map = task_factory_->getTaskDataMap();
    auto it = task_data_map.find(task_key);
    if (it == task_data_map.end()) {
        return Result<Pose>::error(fmt::format("Unknown task key: {}", task_key));
    }

    const auto& task_data = it->second;
    const auto& stage_data = task_data.getStages()[0];
    if (stage_data->getType() != StageType::MOVE_TO_POINT) {
        return Result<Pose>::error("First stage is not a move-to-point operation");
    }

    auto move_to_point_data = std::dynamic_pointer_cast<MoveToPointData>(stage_data);
    if (!move_to_point_data) {
        return Result<Pose>::error("Failed to cast stage data to MoveToPointData");
    }

    Pose pose;
    pose.pose.position.x = move_to_point_data->getX();
    pose.pose.position.y = move_to_point_data->getY();
    pose.pose.position.z = move_to_point_data->getZ();
    pose.pose.orientation.x = move_to_point_data->getQX();
    pose.pose.orientation.y = move_to_point_data->getQY();
    pose.pose.orientation.z = move_to_point_data->getQZ();
    pose.pose.orientation.w = move_to_point_data->getQW();

    return Result<Pose>::success(pose);
}

const std::string ServiceHandler::extractTaskKey(const std::string& command) const 
{
    size_t start = strlen(GET_PREFIX);
    
    size_t end = command.find(":0.");
    if (end != std::string::npos) {
        return command.substr(start, end - start);
    }
    
    return command.substr(start);
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