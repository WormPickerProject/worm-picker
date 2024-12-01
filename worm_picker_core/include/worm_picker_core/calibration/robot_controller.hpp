// robot_controller.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef ROBOT_CONTROLLER_HPP
#define ROBOT_CONTROLLER_HPP

#include <rclcpp/rclcpp.hpp>
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/stages.h>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include "worm_picker_core/stages/move_to_joint_data.hpp"
#include "worm_picker_core/tools/parsers/calibration_points_parser.hpp"

class RobotController {
public:
    RobotController(const rclcpp::Node::SharedPtr& node, const std::string& calibration_file_path);
    bool moveToPoint(size_t index);
    std::optional<geometry_msgs::msg::PoseStamped> getCurrentPose() const;
    size_t getTotalPoints() const;

private:
    void initializeCalibrationPoints(const std::string& calibration_file_path);
    moveit::task_constructor::Task createMoveTask(const MoveToJointData& point) const;
    bool executeTask(moveit::task_constructor::Task& task) const;

    rclcpp::Node::SharedPtr node_;
    std::vector<MoveToJointData> points_;
    static constexpr int MAX_PLANNING_ATTEMPTS = 5;
    static constexpr const char* DEFAULT_END_EFFECTOR = "eoat_tcp";
};

#endif // ROBOT_CONTROLLER_HPP
