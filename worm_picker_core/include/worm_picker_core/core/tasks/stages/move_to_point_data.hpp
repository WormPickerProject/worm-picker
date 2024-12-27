// move_to_point_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef MOVE_TO_POINT_DATA_HPP
#define MOVE_TO_POINT_DATA_HPP

#include <tf2/LinearMath/Quaternion.h>
#include <moveit/task_constructor/solvers.h>
#include "worm_picker_core/core/tasks/stages/movement_data_base.hpp"

class MoveToPointData : public MovementDataBase {
public:
    MoveToPointData() : MovementDataBase(0.1, 0.1) {}
    MoveToPointData(double px, double py, double pz,
                    double ox, double oy, double oz, double ow,
                    double vel_scaling = 0.1, double acc_scaling = 0.1)
        : MovementDataBase(vel_scaling, acc_scaling), 
          x_(px), y_(py), z_(pz) {
        tf2::Quaternion q(ox, oy, oz, ow);
        q.normalize();
        qx_ = q.x();
        qy_ = q.y();
        qz_ = q.z();
        qw_ = q.w();
    }

    StageType getType() const override { return StageType::MOVE_TO_POINT; }
    constexpr double getX() const { return x_; }
    constexpr double getY() const { return y_; }
    constexpr double getZ() const { return z_; }
    constexpr double getQX() const { return qx_; }
    constexpr double getQY() const { return qy_; }
    constexpr double getQZ() const { return qz_; }
    constexpr double getQW() const { return qw_; }

protected:
    std::shared_ptr<void> createPlannerImpl(const NodePtr& node, 
                                            double vel_scaling, 
                                            double acc_scaling) const override;
    StagePtr createStageInstanceImpl(const std::string& name, 
                                     std::shared_ptr<void> planner) const override;
    void configureStageImpl(Stage& stage, const NodePtr& node) const override;

private:
    double x_{};
    double y_{};
    double z_{};
    double qx_{};
    double qy_{};
    double qz_{};
    double qw_{};
};

inline std::shared_ptr<void> MoveToPointData::createPlannerImpl(const NodePtr& node, 
                                                                double vel_scaling, 
                                                                double acc_scaling) const 
{
    using namespace moveit::task_constructor;
    auto cartesian_planner = std::make_shared<solvers::CartesianPath>();
    cartesian_planner->setMaxVelocityScalingFactor(vel_scaling);
    cartesian_planner->setMaxAccelerationScalingFactor(acc_scaling);

    auto step_size = param_utils::getParameter<double>(node, "validation.step_size");
    cartesian_planner->setStepSize(*step_size);
    
    auto min_fraction = param_utils::getParameter<double>(node, "validation.min_fraction");
    cartesian_planner->setMinFraction(*min_fraction);
    
    return cartesian_planner;
}

inline MoveToPointData::StagePtr 
MoveToPointData::createStageInstanceImpl(const std::string& name, 
                                         std::shared_ptr<void> planner) const 
{
    using namespace moveit::task_constructor;
    auto cartesian_planner = std::static_pointer_cast<solvers::CartesianPath>(planner);
    auto stage = std::make_unique<stages::MoveTo>(name, cartesian_planner);
    return stage;
}

inline void MoveToPointData::configureStageImpl(Stage& stage, const NodePtr& node) const 
{
    using namespace moveit::task_constructor;
    auto& move_to_stage = dynamic_cast<stages::MoveTo&>(stage);

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
    
    move_to_stage.setGoal(target_pose);
    setCommonInfo(move_to_stage, node);
}

#endif // MOVE_TO_POINT_DATA_HPP