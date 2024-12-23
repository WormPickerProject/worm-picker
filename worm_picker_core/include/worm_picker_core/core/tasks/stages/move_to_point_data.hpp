// move_to_point_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef MOVE_TO_POINT_DATA_HPP
#define MOVE_TO_POINT_DATA_HPP

#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
#include <tf2/LinearMath/Quaternion.h>
#include "worm_picker_core/core/tasks/stages/stage_data.hpp"
#include "worm_picker_core/utils/parameter_utils.hpp"

class MoveToPointData : public StageData {
public:
    MoveToPointData() = default;

    MoveToPointData(double px, double py, double pz,
                    double ox, double oy, double oz, double ow,
                    double velocity_scaling, double acceleration_scaling)
        : x_(px), y_(py), z_(pz), 
          velocity_scaling_factor_(velocity_scaling), 
          acceleration_scaling_factor_(acceleration_scaling) 
    {
        tf2::Quaternion q(ox, oy, oz, ow);
        q.normalize();
        qx_ = q.x();
        qy_ = q.y();
        qz_ = q.z();
        qw_ = q.w();
    }
    
    StagePtr createStage(const std::string& name, const NodePtr& node) const override;

    StageType getType() const override { return StageType::MOVE_TO_POINT; }

    constexpr double getX() const { return x_; }
    constexpr double getY() const { return y_; }
    constexpr double getZ() const { return z_; }
    constexpr double getQX() const { return qx_; }
    constexpr double getQY() const { return qy_; }
    constexpr double getQZ() const { return qz_; }
    constexpr double getQW() const { return qw_; }
    constexpr double getVelocityScalingFactor() const { return velocity_scaling_factor_; }
    constexpr double getAccelerationScalingFactor() const { return acceleration_scaling_factor_; }

private:
    double x_{};
    double y_{};
    double z_{};
    double qx_{};
    double qy_{};
    double qz_{};
    double qw_{1.0}; 
    double velocity_scaling_factor_{0.1};
    double acceleration_scaling_factor_{0.1};
};

inline MoveToPointData::StagePtr MoveToPointData::createStage(const std::string& name, 
                                                              const NodePtr& node) const
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

    using namespace moveit::task_constructor;
    auto cartesian_planner = std::make_shared<solvers::CartesianPath>();
    cartesian_planner->setMaxVelocityScalingFactor(velocity_scaling_factor_);
    cartesian_planner->setMaxAccelerationScalingFactor(acceleration_scaling_factor_);

    auto step_size = param_utils::getParameter<double>(node, "validation.step_size");
    auto min_fraction = param_utils::getParameter<double>(node, "validation.min_fraction");
    cartesian_planner->setStepSize(*step_size);
    cartesian_planner->setMinFraction(*min_fraction);

    auto stage = std::make_unique<stages::MoveTo>(name, cartesian_planner);
    stage->setGoal(target_pose);
    stage->setGroup("gp4_arm");

    auto ee_link = param_utils::getParameter<std::string>(node, "end_effectors.current_factor");
    stage->setIKFrame(*ee_link);

    TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {"follow_joint_trajectory"};
    stage->setProperty("trajectory_execution_info", execution_info);

    return stage;
}

#endif // MOVE_TO_POINT_DATA_HPP
