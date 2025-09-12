// move_to_point_data.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <moveit_msgs/msg/constraints.hpp>
#include "worm_picker_core/core/tasks/stages/movement_data_base.hpp"
#include "worm_picker_core/core/tasks/stages/joint_constraint.hpp"

class MoveToPointData : public MovementDataBase {
public:
    MoveToPointData();
    MoveToPointData(double px, double py, double pz,
                    double vel_scaling = 0.1, double acc_scaling = 0.1);
    MoveToPointData(double px, double py, double pz,
                    double ox, double oy, double oz, double ow,
                    double vel_scaling = 0.1, double acc_scaling = 0.1);

    void addJointConstraint(const JointConstraint& constraint);
    std::unique_ptr<StageData> clone() const override;
    StageType getType() const override;
    double getX() const;
    double getY() const;
    double getZ() const;
    double getQX() const;
    double getQY() const;
    double getQZ() const;
    double getQW() const;

protected:
    StagePtr createStageInstanceImpl(const std::string& name, 
                                    std::shared_ptr<void> planner) const override;
    void configureStageImpl(Stage& stage, const NodePtr& node) const override;

private:
    geometry_msgs::msg::PoseStamped createPoseGoal(const NodePtr& node) const;
    geometry_msgs::msg::PoseStamped createPointGoal(const NodePtr& node) const;
    moveit_msgs::msg::Constraints createJointConstraints() const;

    double x_{};
    double y_{};
    double z_{};
    double qx_{};
    double qy_{};
    double qz_{};
    double qw_{};
    bool has_orientation_{false};
    std::optional<std::vector<JointConstraint>> joint_constraints_;
};