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

    /// @brief Construct a MoveToJointData with full joint specification
    /// @param joint1 Angle for joint 1 in degrees
    /// @param joint2 Angle for joint 2 in degrees
    /// @param joint3 Angle for joint 3 in degrees
    /// @param joint4 Angle for joint 4 in degrees
    /// @param joint5 Angle for joint 5 in degrees
    /// @param joint6 Angle for joint 6 in degrees
    /// @param velocity_scaling Velocity scaling factor (0.0 to 1.0)
    /// @param acceleration_scaling Acceleration scaling factor (0.0 to 1.0)
    MoveToJointData(double joint1, double joint2, double joint3,
                    double joint4, double joint5, double joint6,
                    double velocity_scaling = 0.1, double acceleration_scaling = 0.1)
        : velocity_scaling_factor_(velocity_scaling), 
          acceleration_scaling_factor_(acceleration_scaling)
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

    /// @brief Construct a MoveToJointData with partial joint specification
    /// @param joint_targets Map of joint names to target angles (in degrees)
    /// @param velocity_scaling Velocity scaling factor (0.0 to 1.0)
    /// @param acceleration_scaling Acceleration scaling factor (0.0 to 1.0)
    MoveToJointData(const std::map<std::string, double>& joint_targets,
                    double velocity_scaling = 0.1, double acceleration_scaling = 0.1)
        : velocity_scaling_factor_(velocity_scaling), 
          acceleration_scaling_factor_(acceleration_scaling)
    {
        for (const auto& [joint, angle] : joint_targets) {
            joint_positions_[joint] = angle * DEG_TO_RAD;
        }
    }
    
    StagePtr createStage(const std::string& name, const NodePtr& node) const override;
    StageType getType() const override { return StageType::MOVE_TO_JOINT; }

    const std::map<std::string, double>& getJointPositions() const { return joint_positions_; }
    constexpr double getVelocityScalingFactor() const { return velocity_scaling_factor_; }
    constexpr double getAccelerationScalingFactor() const { return acceleration_scaling_factor_; }

private:
    static constexpr double DEG_TO_RAD = 3.14159265358979323846 / 180.0;
    std::map<std::string, double> joint_positions_{};
    double velocity_scaling_factor_{};
    double acceleration_scaling_factor_{};
};

inline StageData::StagePtr MoveToJointData::createStage(const std::string& name, 
                                                        const NodePtr& node) const
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
