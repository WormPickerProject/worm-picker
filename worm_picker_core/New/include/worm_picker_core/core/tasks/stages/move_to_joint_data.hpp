// move_to_joint_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef MOVE_TO_JOINT_DATA_HPP
#define MOVE_TO_JOINT_DATA_HPP

#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
#include "worm_picker_core/core/tasks/stages/stage_data.hpp"
#include "worm_picker_core/utils/parameter_utils.hpp"

class MoveToJointData : public StageData {
public:
    MoveToJointData() = default;

    MoveToJointData(double joint1, double joint2, double joint3,
                    double joint4, double joint5, double joint6,
                    double velocity_scaling, double acceleration_scaling)
        : velocity_scaling_factor_(velocity_scaling)
        , acceleration_scaling_factor_(acceleration_scaling)
    {
        joint_positions_ = {
            {"joint_1", joint1 * DEG_TO_RAD},
            {"joint_2", joint2 * DEG_TO_RAD},
            {"joint_3", joint3 * DEG_TO_RAD},
            {"joint_4", joint4 * DEG_TO_RAD},
            {"joint_5", joint5 * DEG_TO_RAD},
            {"joint_6", joint6 * DEG_TO_RAD}
        };
    }
    
    StagePtr createStage(const std::string& name, const NodePtr& node) const override;

    StageType getType() const override { return StageType::MOVE_TO_JOINT; }

    const std::map<std::string, double>& getJointPositions() const { return joint_positions_; }
    constexpr double getVelocityScalingFactor() const { return velocity_scaling_factor_; }
    constexpr double getAccelerationScalingFactor() const { return acceleration_scaling_factor_; }

private:
    static constexpr double DEG_TO_RAD = 3.14159265358979323846 / 180.0;
    std::map<std::string, double> joint_positions_{};
    double velocity_scaling_factor_{0.1};
    double acceleration_scaling_factor_{0.1};
};

inline StageData::StagePtr MoveToJointData::createStage(
    const std::string& name, const NodePtr& node) const
{
    using namespace moveit::task_constructor;
    auto joint_planner = std::make_shared<solvers::JointInterpolationPlanner>();
    joint_planner->setMaxVelocityScalingFactor(velocity_scaling_factor_);
    joint_planner->setMaxAccelerationScalingFactor(acceleration_scaling_factor_);

    auto stage = std::make_unique<stages::MoveTo>(name, joint_planner);
    stage->setGoal(joint_positions_);
    stage->setGroup("gp4_arm");

    auto ee_link = param_utils::getParameter<std::string>(node, "end_effectors.current_factor");
    stage->setIKFrame(*ee_link);

    TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {"follow_joint_trajectory"};
    stage->setProperty("trajectory_execution_info", execution_info);

    return stage;
}

#endif // MOVE_TO_JOINT_DATA_HPP
