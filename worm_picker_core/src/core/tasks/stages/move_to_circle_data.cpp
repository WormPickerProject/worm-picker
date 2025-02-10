// move_to_circle_data.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <tf2/LinearMath/Quaternion.h>
#include <moveit/task_constructor/stages.h>
#include <moveit/task_constructor/solvers.h>
#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_circle_data.hpp"
#include "worm_picker_core/utils/circular_motion_utils.hpp"

MoveToCircleData::MoveToCircleData() 
  : MovementDataBase(0.1, 0.1) {}

  MoveToCircleData::MoveToCircleData(double px, double py, double pz,
                                     double vel_scaling = 0.1, double acc_scaling = 0.1)
  : MovementDataBase(vel_scaling, acc_scaling),
    x_(px), y_(py), z_(pz),
    has_orientation_(false) {}

  MoveToCircleData::MoveToCircleData(double px, double py, double pz,
                                 double ox, double oy, double oz, double ow,
                                 double vel_scaling, double acc_scaling)
  : MovementDataBase(vel_scaling, acc_scaling), 
    x_(px), y_(py), z_(pz), 
    has_orientation_(false)
{
    tf2::Quaternion q(ox, oy, oz, ow);
    q.normalize();
    qx_ = q.x();
    qy_ = q.y();
    qz_ = q.z();
    qw_ = q.w();
}

MoveToCircleData::StagePtr 
MoveToCircleData::createStageInstanceImpl(const std::string& name, 
                                         std::shared_ptr<void> planner) const 
{
    using namespace moveit::task_constructor;
    auto planner_interface = std::static_pointer_cast<solvers::PlannerInterface>(planner);
    auto stage = std::make_unique<stages::MoveTo>(name, planner_interface);
    return stage;
}

void MoveToCircleData::configureStageImpl(Stage& stage, const NodePtr& node) const 
{
    using PoseStamped = geometry_msgs::msg::PoseStamped;
    using CircConfig = std::unordered_map<CircularMotionType, std::pair<std::string, std::string>>;

    const CircConfig CIRC_CONFIG = {
        {CircularMotionType::CENTER, {"center", "circ_center"}},
        {CircularMotionType::INTERIM, {"interim", "circ_interim"}}
    };
    auto [type_str, pose_key] = CIRC_CONFIG.at(getCircularConstraint().type);

    auto& move_to_stage = dynamic_cast<moveit::task_constructor::stages::MoveTo&>(stage);
    move_to_stage.properties().set<std::string>("circ_type", type_str);
    move_to_stage.properties().set<PoseStamped>(pose_key, getCircularConstraint().aux_pose);
  
    move_to_stage.setGoal(has_orientation_ ? createPoseGoal(node) : createPointGoal(node));
    setCommonInfo(move_to_stage, node);
}

const geometry_msgs::msg::PoseStamped& MoveToCircleData::createPoseGoal(const NodePtr& node) const 
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

const geometry_msgs::msg::PoseStamped& MoveToCircleData::createPointGoal(const NodePtr& node) const 
{
    geometry_msgs::msg::PoseStamped target_point;
    target_point.header.frame_id = "base_link";
    target_point.header.stamp = node->now();
    target_point.pose.position.x = x_;
    target_point.pose.position.y = y_;
    target_point.pose.position.z = z_;
    return target_point;
}

const CircularConstraint& MoveToCircleData::getCircularConstraint() const 
{
    if (!circ_) {
        throw std::runtime_error("No circular constraint set");
    }
    return *circ_;
}

std::unique_ptr<StageData> 
MoveToCircleData::clone() const { return std::make_unique<MoveToCircleData>(*this); }
StageType MoveToCircleData::getType() const { return StageType::MOVE_TO_POINT; }
void MoveToCircleData::setCircularConstraint(const CircularConstraint& c) { circ_ = c; }
double MoveToCircleData::getX() const { return x_; }
double MoveToCircleData::getY() const { return y_; }
double MoveToCircleData::getZ() const { return z_; }
double MoveToCircleData::getQX() const { return qx_; }
double MoveToCircleData::getQY() const { return qy_; }
double MoveToCircleData::getQZ() const { return qz_; }
double MoveToCircleData::getQW() const { return qw_; }