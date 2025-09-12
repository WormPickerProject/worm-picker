// move_to_point_data.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <tf2/LinearMath/Quaternion.h>
#include <moveit/task_constructor/stages.h>
#include <moveit/task_constructor/solvers.h>
#include "worm_picker_core/core/tasks/stages/move_to_point_data.hpp"

MoveToPointData::MoveToPointData() 
  : MovementDataBase(0.1, 0.1) {}

MoveToPointData::MoveToPointData(double px, double py, double pz,
                                 double vel_scaling, double acc_scaling)
  : MovementDataBase(vel_scaling, acc_scaling),
    x_(px), y_(py), z_(pz),
    has_orientation_(false) {}

MoveToPointData::MoveToPointData(double px, double py, double pz,
                                 double ox, double oy, double oz, double ow,
                                 double vel_scaling, double acc_scaling)
  : MovementDataBase(vel_scaling, acc_scaling), 
    x_(px), y_(py), z_(pz), 
    has_orientation_(true)
{
    tf2::Quaternion q(ox, oy, oz, ow);
    q.normalize();
    qx_ = q.x();
    qy_ = q.y();
    qz_ = q.z();
    qw_ = q.w();
}

MoveToPointData::StagePtr 
MoveToPointData::createStageInstanceImpl(const std::string& name, 
                                         std::shared_ptr<void> planner) const 
{
    using namespace moveit::task_constructor;
    auto planner_interface = std::static_pointer_cast<solvers::PlannerInterface>(planner);
    auto stage = std::make_unique<stages::MoveTo>(name, planner_interface);
    return stage;
}

void MoveToPointData::configureStageImpl(Stage& stage, const NodePtr& node) const 
{
    using namespace moveit::task_constructor;
    auto& move_to_stage = dynamic_cast<stages::MoveTo&>(stage);
    
    if (joint_constraints_ && !joint_constraints_->empty()) {
        auto constraints = createJointConstraints();
        move_to_stage.setPathConstraints(constraints);
    }
    
    move_to_stage.setGoal(has_orientation_ ? createPoseGoal(node) : createPointGoal(node));
    setCommonInfo(move_to_stage, node);
}

geometry_msgs::msg::PoseStamped MoveToPointData::createPoseGoal(const NodePtr& node) const 
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
    return target_pose;
}

 geometry_msgs::msg::PoseStamped MoveToPointData::createPointGoal(const NodePtr& node) const 
{
    geometry_msgs::msg::PoseStamped target_point;
    target_point.header.frame_id = "base_link";
    target_point.header.stamp = node->now();
    target_point.pose.position.x = x_;
    target_point.pose.position.y = y_;
    target_point.pose.position.z = z_;
    return target_point;
}

void MoveToPointData::addJointConstraint(const JointConstraint& constraint) 
{
    if (!joint_constraints_) {
        joint_constraints_ = std::vector<JointConstraint>();
    }
    joint_constraints_->push_back(constraint);
}

moveit_msgs::msg::Constraints MoveToPointData::createJointConstraints() const 
{
    moveit_msgs::msg::Constraints constraints;
    constraints.name = "joint_constraints";
    
    if (joint_constraints_) {
        for (const auto& jc : *joint_constraints_) {
            moveit_msgs::msg::JointConstraint joint_constraint;
            joint_constraint.joint_name = jc.joint_name;
            
            double center = (jc.min_position + jc.max_position) / 2.0;
            double half_range = (jc.max_position - jc.min_position) / 2.0;
            
            joint_constraint.position = center;
            joint_constraint.tolerance_above = half_range + jc.tolerance_above;
            joint_constraint.tolerance_below = half_range + jc.tolerance_below;
            joint_constraint.weight = jc.weight;
            
            constraints.joint_constraints.push_back(joint_constraint);
        }
    }
    
    return constraints;
}

std::unique_ptr<StageData> 
MoveToPointData::clone() const { return std::make_unique<MoveToPointData>(*this); }
StageType MoveToPointData::getType() const { return StageType::MOVE_TO_POINT; }
double MoveToPointData::getX() const { return x_; }
double MoveToPointData::getY() const { return y_; }
double MoveToPointData::getZ() const { return z_; }
double MoveToPointData::getQX() const { return qx_; }
double MoveToPointData::getQY() const { return qy_; }
double MoveToPointData::getQZ() const { return qz_; }
double MoveToPointData::getQW() const { return qw_; }