// move_to_joint_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef MOVE_TO_JOINT_DATA_HPP
#define MOVE_TO_JOINT_DATA_HPP

#include <moveit/task_constructor/solvers.h>
#include "worm_picker_core/core/tasks/stages/movement_data_base.hpp"

class MoveToJointData : public MovementDataBase {
public:
    MoveToJointData() : MovementDataBase(0.1, 0.1) {}
    MoveToJointData(double joint_1, double joint_2, double joint_3,
                    double joint_4, double joint_5, double joint_6,
                    double vel_scaling = 0.1, double acc_scaling = 0.1)
        : MovementDataBase(vel_scaling, acc_scaling) {
        joint_positions_ = {
            {"joint_1", joint_1 * DEG_TO_RAD},
            {"joint_2", joint_2 * DEG_TO_RAD},
            {"joint_3", joint_3 * DEG_TO_RAD},
            {"joint_4", joint_4 * DEG_TO_RAD},
            {"joint_5", joint_5 * DEG_TO_RAD},
            {"joint_6", joint_6 * DEG_TO_RAD}
        };
    }
    MoveToJointData(const std::map<std::string, double>& joint_targets,
                    double vel_scaling = 0.1, double acc_scaling = 0.1)
        : MovementDataBase(vel_scaling, acc_scaling) {
        for (const auto& [joint, angle] : joint_targets) {
            joint_positions_[joint] = angle * DEG_TO_RAD;
        }
    }
    
    StageType getType() const override { return StageType::MOVE_TO_JOINT; }
    const std::map<std::string, double>& getJointPositions() const { return joint_positions_; }

protected:
    std::shared_ptr<void> createPlannerImpl(const NodePtr& node, 
                                            double vel_scaling, 
                                            double acc_scaling) const override;
    StagePtr createStageInstanceImpl(const std::string& name, 
                                     std::shared_ptr<void> planner) const override;
    void configureStageImpl(Stage& stage, const NodePtr& node) const override;

private:
    static constexpr double DEG_TO_RAD = 3.14159265358979323846 / 180.0;
    std::map<std::string, double> joint_positions_{};
};

inline std::shared_ptr<void> MoveToJointData::createPlannerImpl(const NodePtr& node,
                                                                double vel_scaling, 
                                                                double acc_scaling) const 
{
    (void)node;
    using namespace moveit::task_constructor;
    auto joint_planner = std::make_shared<solvers::JointInterpolationPlanner>();
    joint_planner->setMaxVelocityScalingFactor(vel_scaling);
    joint_planner->setMaxAccelerationScalingFactor(acc_scaling);
    
    return joint_planner;
}

inline MoveToJointData::StagePtr 
MoveToJointData::createStageInstanceImpl(const std::string& name, 
                                         std::shared_ptr<void> planner) const 
{
    using namespace moveit::task_constructor;
    auto joint_planner = std::static_pointer_cast<solvers::JointInterpolationPlanner>(planner);
    auto stage = std::make_unique<stages::MoveTo>(name, joint_planner);
    return stage;
}

inline void MoveToJointData::configureStageImpl(Stage& stage, const NodePtr& node) const 
{
    using namespace moveit::task_constructor;
    auto& move_to_stage = dynamic_cast<stages::MoveTo&>(stage);

    move_to_stage.setGoal(joint_positions_);
    setCommonInfo(move_to_stage, node);
}

#endif // MOVE_TO_JOINT_DATA_HPP
