// robot_controller.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <tf2_eigen/tf2_eigen.hpp>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include "worm_picker_core/system/calibration/robot_controller.hpp"

RobotController::RobotController(const NodePtr& node,
                                 const std::string& calibration_file_path,
                                 const std::string& robot_group,
                                 const std::string& end_effector_link)
    : node_(node), robot_group_(robot_group), end_effector_link_(end_effector_link)
{
    CalibrationPointsParser parser(calibration_file_path);
    points_map_ = parser.getCalibrationPointsMap();
    points_order_ = parser.getPointsOrder();

    node_->declare_parameter<std::string>("end_effector", "eoat_tcp");
    planning_scene_sub_ = node_->create_subscription<moveit_msgs::msg::PlanningScene>(
        "monitored_planning_scene", 10,
        [this](const PlanningSceneMsg msg) {
            monitoredPlanningSceneCallback(msg);
        });
}

bool RobotController::moveToPoint(const std::string& key)
{
    auto it = points_map_.find(key);
    if (it == points_map_.end()) {
        // RCLCPP_ERROR(node_->get_logger(), "No calibration point named '%s'", key.c_str());
        return false;
    }

    const auto& point_data = it->second;
    auto task = createTaskForPoint(point_data);
    return executeTask(task);
}

RobotController::Task RobotController::createTaskForPoint(const MoveToJointData& point_data) const
{
    Task task;
    task.stages()->setName("MoveToPoint");
    task.loadRobotModel(node_);

    task.setProperty("group", robot_group_);
    task.setProperty("ik_frame", end_effector_link_);

    moveit::task_constructor::TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {"follow_joint_trajectory"};
    task.setProperty("trajectory_execution_info", execution_info);

    task.add(std::make_unique<moveit::task_constructor::stages::CurrentState>("current"));
    task.add(point_data.createStage("move_to_target", node_));

    return task;
}

bool RobotController::executeTask(Task& task) const
{
    task.enableIntrospection();
    task.init();

    static constexpr int MAX_PLANNING_ATTEMPTS = 5;
    if (!task.plan(MAX_PLANNING_ATTEMPTS)) {
        RCLCPP_ERROR(node_->get_logger(), "Task planning failed.");
        return false;
    }

    if (task.solutions().empty()) {
        RCLCPP_ERROR(node_->get_logger(), "No solutions found.");
        return false;
    }

    const auto& solution = *task.solutions().front();
    task.introspection().publishSolution(solution);
    const auto result = task.execute(solution);

    if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
        RCLCPP_ERROR(node_->get_logger(), "Task execution failed.");
        return false;
    }

    return true;
}

void RobotController::monitoredPlanningSceneCallback(const PlanningSceneMsg msg) 
{
    std::lock_guard<std::mutex> lock(scene_mutex_);
    if (!current_scene_) {
        robot_model_loader::RobotModelLoader::Options options;
        options.robot_description_ = "robot_description";
        auto robot_model = robot_model_loader::RobotModelLoader(node_, options).getModel();
        current_scene_ = std::make_shared<planning_scene::PlanningScene>(robot_model);
    }
    current_scene_->usePlanningSceneMsg(*msg);
}

std::optional<RobotController::Pose> RobotController::getCurrentPose() const
{
    std::lock_guard<std::mutex> lock(scene_mutex_);
    
    if (!current_scene_) {
        RCLCPP_ERROR(node_->get_logger(), "Planning scene not yet received");
        return std::nullopt;
    }
    
    const auto& end_effector_link = node_->get_parameter("end_effector").as_string();
    const Eigen::Isometry3d& transform = 
        current_scene_->getCurrentState().getGlobalLinkTransform(end_effector_link);
    
    Pose pose;
    pose.header.frame_id = current_scene_->getPlanningFrame();
    pose.header.stamp = node_->get_clock()->now();
    pose.pose = tf2::toMsg(transform);
    
    return pose;
}