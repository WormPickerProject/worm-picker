// robot_controller.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef ROBOT_CONTROLLER_HPP
#define ROBOT_CONTROLLER_HPP

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <moveit_msgs/msg/planning_scene.hpp>
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/stages.h>
#include <moveit/planning_scene/planning_scene.h>
#include "worm_picker_core/core/tasks/stages/move_to_joint_data.hpp"
#include "worm_picker_core/infrastructure/parsers/calibration_points_parser.hpp"

class RobotController {
public:
    using NodePtr = rclcpp::Node::SharedPtr;
    using Pose = geometry_msgs::msg::PoseStamped;
    using Task = moveit::task_constructor::Task;

    RobotController(const NodePtr& node,
                    const std::string& calibration_file_path,
                    const std::string& robot_group,
                    const std::string& end_effector_link);

    bool moveToPoint(const std::string& key);
    std::optional<Pose> getCurrentPose() const;
    const std::map<std::string, MoveToJointData>& getPointsMap() { return points_map_; }
    const std::vector<std::string>& getPointsOrder() { return points_order_; }
    size_t getTotalPoints() const { return points_order_.size(); }

private:
    using PlanningSceneMsg = moveit_msgs::msg::PlanningScene::SharedPtr;

    Task createTaskForPoint(const MoveToJointData& point_data) const;
    bool executeTask(Task& task) const;
    void monitoredPlanningSceneCallback(const PlanningSceneMsg msg);

    NodePtr node_;
    std::map<std::string, MoveToJointData> points_map_;
    std::vector<std::string> points_order_;
    std::string robot_group_;
    std::string end_effector_link_;
    rclcpp::Subscription<moveit_msgs::msg::PlanningScene>::SharedPtr planning_scene_sub_;
    std::shared_ptr<planning_scene::PlanningScene> current_scene_;
    mutable std::mutex scene_mutex_;
};

#endif // ROBOT_CONTROLLER_HPP