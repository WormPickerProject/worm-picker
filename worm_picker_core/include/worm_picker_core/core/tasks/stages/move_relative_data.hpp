// move_relative_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef MOVE_RELATIVE_DATA_HPP
#define MOVE_RELATIVE_DATA_HPP

#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
#include "worm_picker_core/core/tasks/stages/stage_data.hpp"
#include "worm_picker_core/utils/parameter_utils.hpp"

class MoveRelativeData : public StageData {
public:
    MoveRelativeData() = default;

    constexpr MoveRelativeData(double delta_x, double delta_y, double delta_z,
                               double velocity_scaling = 0.1, double acceleration_scaling = 0.1)
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
    double velocity_scaling_factor_{};
    double acceleration_scaling_factor_{};
};

inline StageData::StagePtr MoveRelativeData::createStage(const std::string& name,
                                                         const NodePtr& node) const
{
    geometry_msgs::msg::Vector3Stamped direction_vector;
    auto ee_link = param_utils::getParameter<std::string>(node, "end_effectors.current_factor");
    direction_vector.header.frame_id = *ee_link;
    direction_vector.header.stamp = node->now();
    direction_vector.vector.x = dx_;
    direction_vector.vector.y = dy_;
    direction_vector.vector.z = dz_;

    using namespace moveit::task_constructor;
    auto cartesian_planner = std::make_shared<solvers::CartesianPath>();
    cartesian_planner->setMaxVelocityScalingFactor(velocity_scaling_factor_);
    cartesian_planner->setMaxAccelerationScalingFactor(acceleration_scaling_factor_);

    auto step_size = param_utils::getParameter<double>(node, "validation.step_size");
    auto min_fraction = param_utils::getParameter<double>(node, "validation.min_fraction");
    cartesian_planner->setStepSize(*step_size);
    cartesian_planner->setMinFraction(*min_fraction);

    auto stage = std::make_unique<stages::MoveRelative>(name, cartesian_planner);
    stage->setDirection(direction_vector);
    stage->setGroup("gp4_arm");
    stage->setIKFrame(*ee_link);

    TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {"follow_joint_trajectory"};
    stage->setProperty("trajectory_execution_info", execution_info);

    return stage;
}

#endif // MOVE_RELATIVE_DATA_HPP
