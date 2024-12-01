// robot_controller.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/calibration/robot_controller.hpp"
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/planning_scene/planning_scene.h>
#include <tf2_eigen/tf2_eigen.hpp>

RobotController::RobotController(const rclcpp::Node::SharedPtr& node, const std::string& calibration_file_path)
    : node_(node) {
    initializeCalibrationPoints(calibration_file_path);
}

void RobotController::initializeCalibrationPoints(const std::string& calibration_file_path) {
    try {
        CalibrationPointsParser parser(calibration_file_path);
        points_ = parser.getCalibrationPoints();

        if (points_.empty()) {
            RCLCPP_ERROR(node_->get_logger(), "No calibration points loaded from file.");
        }
    } catch (const std::exception& e) {
        RCLCPP_ERROR(node_->get_logger(), "Failed to load calibration points: %s", e.what());
    }
}

size_t RobotController::getTotalPoints() const
{
    return points_.size();
}

bool RobotController::moveToPoint(size_t index)
{
    if (index >= points_.size()) {
        RCLCPP_ERROR(node_->get_logger(), "moveToPoint: Point index %zu out of range.", index);
        return false;
    }

    auto task = createMoveTask(points_[index]);
    return executeTask(task);
}

moveit::task_constructor::Task RobotController::createMoveTask(const MoveToJointData& point) const
{
    using namespace moveit::task_constructor;

    Task task;
    task.stages()->setName("MoveToPoint");
    task.loadRobotModel(node_);

    task.setProperty("group", "gp4_arm");
    task.setProperty("ik_frame", DEFAULT_END_EFFECTOR);

    task.add(std::make_unique<stages::CurrentState>("current"));

    auto stage = point.createStage("move_to_target", node_);
    task.add(std::move(stage));

    return task;
}

bool RobotController::executeTask(moveit::task_constructor::Task& task) const
{
    task.init();

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

std::optional<geometry_msgs::msg::PoseStamped> RobotController::getCurrentPose() const
{
    try {
        auto robot_loader = std::make_shared<robot_model_loader::RobotModelLoader>(node_);
        auto kinematic_model = robot_loader->getModel();
        if (!kinematic_model) {
            throw std::runtime_error("Failed to load robot model.");
        }

        planning_scene::PlanningScene planning_scene(kinematic_model);
        planning_scene.getCurrentStateNonConst().update();

        const auto& current_state = planning_scene.getCurrentState();

        const auto link_names = current_state.getRobotModel()->getJointModelGroup("gp4_arm")->getLinkModelNames();
        const auto& end_effector_link = link_names.back();

        const Eigen::Isometry3d& ee_transform = current_state.getGlobalLinkTransform(end_effector_link);

        geometry_msgs::msg::PoseStamped current_pose;
        current_pose.pose = tf2::toMsg(ee_transform);
        current_pose.header.frame_id = "world";
        current_pose.header.stamp = node_->get_clock()->now();

        return current_pose;
    } catch (const std::exception& e) {
        RCLCPP_ERROR(node_->get_logger(), "Exception in getCurrentPose: %s", e.what());
        return std::nullopt;
    }
}
