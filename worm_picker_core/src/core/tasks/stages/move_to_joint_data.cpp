// move_to_joint_data.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <moveit/task_constructor/stages.h>
#include <moveit/task_constructor/solvers.h>
#include "worm_picker_core/core/tasks/stages/move_to_joint_data.hpp"

MoveToJointData::MoveToJointData() 
    : MovementDataBase(0.1, 0.1) {}

MoveToJointData::MoveToJointData(double joint_1, double joint_2, double joint_3,
                                 double joint_4, double joint_5, double joint_6,
                                 double vel_scaling, double acc_scaling)
    : MovementDataBase(vel_scaling, acc_scaling) 
{
    joint_positions_ = {
        {"joint_1", joint_1 * DEG_TO_RAD},
        {"joint_2", joint_2 * DEG_TO_RAD},
        {"joint_3", joint_3 * DEG_TO_RAD},
        {"joint_4", joint_4 * DEG_TO_RAD},
        {"joint_5", joint_5 * DEG_TO_RAD},
        {"joint_6", joint_6 * DEG_TO_RAD}
    };
}

MoveToJointData::MoveToJointData(const std::map<std::string, double>& joint_targets,
                                 double vel_scaling, double acc_scaling)
    : MovementDataBase(vel_scaling, acc_scaling) 
{
    for (const auto& [joint, angle] : joint_targets) {
        joint_positions_[joint] = angle * DEG_TO_RAD;
    }
}

MoveToJointData::StagePtr 
MoveToJointData::createStageInstanceImpl(const std::string& name, 
                                        std::shared_ptr<void> planner) const 
{
    using namespace moveit::task_constructor;
    auto joint_planner = std::static_pointer_cast<solvers::JointInterpolationPlanner>(planner);
    auto stage = std::make_unique<stages::MoveTo>(name, joint_planner);
    return stage;
}

void MoveToJointData::configureStageImpl(Stage& stage, const NodePtr& node) const 
{
    using namespace moveit::task_constructor;
    auto& move_to_stage = dynamic_cast<stages::MoveTo&>(stage);
    move_to_stage.setGoal(joint_positions_);
    setCommonInfo(move_to_stage, node);
}

std::unique_ptr<StageData> MoveToJointData::clone() const
{
    return std::make_unique<MoveToJointData>(*this);
}

StageType MoveToJointData::getType() const 
{ 
    return StageType::MOVE_TO_JOINT; 
}

const std::map<std::string, double>& MoveToJointData::getJointPositions() const 
{ 
    return joint_positions_; 
}