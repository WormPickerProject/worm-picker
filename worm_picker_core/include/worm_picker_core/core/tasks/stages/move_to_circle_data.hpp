// move_to_circle_data.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <moveit_msgs/msg/constraints.hpp>
#include "worm_picker_core/core/tasks/stages/movement_data_base.hpp"
#include "worm_picker_core/core/tasks/stages/circular_constraint.hpp"

class MoveToCircleData : public MovementDataBase {
public:
    MoveToCircleData();
    MoveToCircleData(double px, double py, double pz,
                     double vel_scaling = 0.1, double acc_scaling = 0.1);
    MoveToCircleData(double px, double py, double pz,
                     double ox, double oy, double oz, double ow,
                     double vel_scaling = 0.1, double acc_scaling = 0.1);

    void setCircularConstraint(const CircularConstraint& c);
    const CircularConstraint& getCircularConstraint() const;

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
    moveit_msgs::msg::Constraints createCircularPathConstraints(const NodePtr& node) const;
    geometry_msgs::msg::PoseStamped createPoseGoal(const NodePtr& node) const;
    geometry_msgs::msg::PoseStamped createPointGoal(const NodePtr& node) const; 

    double x_{};
    double y_{};
    double z_{};
    double qx_{};
    double qy_{};
    double qz_{};
    double qw_{};
    bool has_orientation_{false};
    std::optional<CircularConstraint> circ_;
};