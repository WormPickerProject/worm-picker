// move_relative_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef MOVE_RELATIVE_DATA_HPP
#define MOVE_RELATIVE_DATA_HPP

#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
#include "worm_picker_core/core/tasks/stages/stage_data.hpp"

class MoveRelativeData : public StageData {
public:
    MoveRelativeData() = default;

    constexpr MoveRelativeData(double delta_x, double delta_y, double delta_z,
                               double velocity_scaling, double acceleration_scaling)
        : dx_(delta_x), dy_(delta_y), dz_(delta_z), 
          velocity_scaling_factor_(velocity_scaling), 
          acceleration_scaling_factor_(acceleration_scaling) {}

    StagePtr createStage(const std::string& name, const NodePtr& node) const override;

    StageType getType() const override { return StageType::MOVE_RELATIVE; }

    constexpr double getDX() const { return dx_; }
    constexpr double getDY() const { return dy_; }
    constexpr double getDZ() const { return dz_; }
    constexpr double getVelocityScalingFactor() const { return velocity_scaling_factor_; }
    constexpr double getAccelerationScalingFactor() const {return acceleration_scaling_factor_; }

private:
    double dx_{};
    double dy_{};
    double dz_{};
    double velocity_scaling_factor_{0.1};
    double acceleration_scaling_factor_{0.1};
};

inline StageData::StagePtr MoveRelativeData::createStage(const std::string& name,
                                                         const NodePtr& node) const
{
    geometry_msgs::msg::Vector3Stamped direction_vector;
    direction_vector.header.frame_id = current_end_effector;
    direction_vector.header.stamp = node->now();
    direction_vector.vector.x = dx_;
    direction_vector.vector.y = dy_;
    direction_vector.vector.z = dz_;

    using namespace moveit::task_constructor;
    auto cartesian_planner = std::make_shared<solvers::CartesianPath>();
    cartesian_planner->setMaxVelocityScalingFactor(velocity_scaling_factor_);
    cartesian_planner->setMaxAccelerationScalingFactor(acceleration_scaling_factor_);
    cartesian_planner->setStepSize(.01);
    cartesian_planner->setMinFraction(0.0);

    auto stage = std::make_unique<stages::MoveRelative>(name, cartesian_planner);
    stage->setDirection(direction_vector);
    stage->setGroup("gp4_arm");

    const auto& current_end_effector = node->get_parameter("end_effector").as_string();
    stage->setIKFrame(current_end_effector);

    TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {"follow_joint_trajectory"};
    stage->setProperty("trajectory_execution_info", execution_info);

    return stage;
}

#endif // MOVE_RELATIVE_DATA_HPP
