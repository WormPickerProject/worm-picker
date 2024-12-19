// move_to_joint_data.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <cmath>
#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
#include "worm_picker_core/stages/move_to_joint_data.hpp"

MoveToJointData::MoveToJointData(double joint1, double joint2, double joint3, 
                                 double joint4, double joint5, double joint6,
                                 double velocity_scaling, double acceleration_scaling) 
    : velocity_scaling_factor_(velocity_scaling), 
      acceleration_scaling_factor_(acceleration_scaling)
{
    const double deg_to_rad = M_PI / 180.0;

    joint_positions_["joint_1"] = joint1 * deg_to_rad;
    joint_positions_["joint_2"] = joint2 * deg_to_rad;
    joint_positions_["joint_3"] = joint3 * deg_to_rad;
    joint_positions_["joint_4"] = joint4 * deg_to_rad;
    joint_positions_["joint_5"] = joint5 * deg_to_rad;
    joint_positions_["joint_6"] = joint6 * deg_to_rad;
}

std::unique_ptr<moveit::task_constructor::Stage> MoveToJointData::createStage(const std::string& name,
                                                                              const rclcpp::Node::SharedPtr& node) const
{
    const std::string current_end_effector = node->get_parameter("end_effector").as_string();

    auto joint_planner = std::make_shared<moveit::task_constructor::solvers::JointInterpolationPlanner>();
    joint_planner->setMaxVelocityScalingFactor(velocity_scaling_factor_);
    joint_planner->setMaxAccelerationScalingFactor(acceleration_scaling_factor_);

    auto stage = std::make_unique<moveit::task_constructor::stages::MoveTo>(name, joint_planner);
    stage->setGoal(joint_positions_);
    stage->setGroup("gp4_arm");
    stage->setIKFrame(current_end_effector);

    moveit::task_constructor::TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {"follow_joint_trajectory"};
    stage->setProperty("trajectory_execution_info", execution_info);

    return stage;
}

StageType MoveToJointData::getType() const noexcept
{
    return StageType::MOVE_TO_JOINT;
}

const std::map<std::string, double>& MoveToJointData::getJointPositions() const noexcept 
{
    return joint_positions_;
}

double MoveToJointData::getVelocityScalingFactor() const noexcept 
{
    return velocity_scaling_factor_;
}

double MoveToJointData::getAccelerationScalingFactor() const noexcept 
{
    return acceleration_scaling_factor_;
}
