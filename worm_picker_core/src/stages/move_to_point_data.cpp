// move_to_point_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
#include <tf2/LinearMath/Quaternion.h>
#include "worm_picker_core/stages/move_to_point_data.hpp"

MoveToPointData::MoveToPointData(double px, double py, double pz,
                                 double ox, double oy, double oz, double ow,
                                 double velocity_scaling,
                                 double acceleration_scaling)
    : x_(px), y_(py), z_(pz),
      qx_(ox), qy_(oy), qz_(oz), qw_(ow),
      velocity_scaling_factor_(velocity_scaling),
      acceleration_scaling_factor_(acceleration_scaling)
{
    tf2::Quaternion q(qx_, qy_, qz_, qw_);
    q.normalize();
    qx_ = q.x();
    qy_ = q.y();
    qz_ = q.z();
    qw_ = q.w();
}

std::unique_ptr<moveit::task_constructor::Stage> MoveToPointData::createStage(const std::string& name,
                                                                              const rclcpp::Node::SharedPtr& node) const
{
    geometry_msgs::msg::PoseStamped target_pose;
    target_pose.header.frame_id = "base_link";
    target_pose.header.stamp = node->now();
    target_pose.pose.position.x = x_;
    target_pose.pose.position.y = y_;
    target_pose.pose.position.z = z_;
    target_pose.pose.orientation.x = qx_;
    target_pose.pose.orientation.y = qy_;
    target_pose.pose.orientation.z = qz_;
    target_pose.pose.orientation.w = qw_;

    auto cartesian_planner = std::make_shared<moveit::task_constructor::solvers::CartesianPath>();
    cartesian_planner->setMaxVelocityScalingFactor(velocity_scaling_factor_);
    cartesian_planner->setMaxAccelerationScalingFactor(acceleration_scaling_factor_);
    cartesian_planner->setStepSize(.01);
    cartesian_planner->setMinFraction(0.0);

    auto stage = std::make_unique<moveit::task_constructor::stages::MoveTo>(name, cartesian_planner);
    stage->setGoal(target_pose);
    stage->setGroup("gp4_arm");
    stage->setIKFrame("eoat_tcp");

    moveit::task_constructor::TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {"follow_joint_trajectory"};
    stage->setProperty("trajectory_execution_info", execution_info);

    return stage;
}

StageType MoveToPointData::getType() const noexcept
{
    return StageType::MOVE_TO_POINT;
}

double MoveToPointData::getX() const noexcept
{
    return x_;
}

double MoveToPointData::getY() const noexcept
{
    return y_;
}

double MoveToPointData::getZ() const noexcept
{
    return z_;
}

double MoveToPointData::getQX() const noexcept
{
    return qx_;
}

double MoveToPointData::getQY() const noexcept
{
    return qy_;
}

double MoveToPointData::getQZ() const noexcept
{
    return qz_;
}

double MoveToPointData::getQW() const noexcept
{
    return qw_;
}

double MoveToPointData::getVelocityScalingFactor() const noexcept
{
    return velocity_scaling_factor_;
}

double MoveToPointData::getAccelerationScalingFactor() const noexcept
{
    return acceleration_scaling_factor_;
}
