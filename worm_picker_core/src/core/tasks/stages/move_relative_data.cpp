// move_relative_data.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <moveit/task_constructor/stages.h>
#include <moveit/task_constructor/solvers.h>
#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/core/tasks/stages/move_relative_data.hpp"

MoveRelativeData::MoveRelativeData() 
  : MovementDataBase(0.1, 0.1) {}

MoveRelativeData::MoveRelativeData(double dx, double dy, double dz,
                                   double vel_scaling, double acc_scaling)
  : MovementDataBase(vel_scaling, acc_scaling), 
    dx_(dx), dy_(dy), dz_(dz) {}

MoveRelativeData::StagePtr 
MoveRelativeData::createStageInstanceImpl(const std::string& name, 
                                          std::shared_ptr<void> planner) const 
{
    using namespace moveit::task_constructor;
    auto planner_interface = std::static_pointer_cast<solvers::PlannerInterface>(planner);
    auto stage = std::make_unique<stages::MoveRelative>(name, planner_interface);
    return stage;
}

void MoveRelativeData::configureStageImpl(Stage& stage, const NodePtr& node) const 
{
    using namespace moveit::task_constructor;
    auto& move_relative_stage = dynamic_cast<stages::MoveRelative&>(stage);

    geometry_msgs::msg::Vector3Stamped direction;
    auto ee_link = param_utils::getParameter<std::string>(node, "end_effectors.current_factor");
    direction.header.frame_id = *ee_link;
    direction.vector.x = dx_;
    direction.vector.y = dy_;
    direction.vector.z = dz_;
    direction.header.stamp = node->now();

    move_relative_stage.setDirection(direction);
    setCommonInfo(move_relative_stage, node);
}

std::unique_ptr<StageData> 
MoveRelativeData::clone() const { return std::make_unique<MoveRelativeData>(*this); }
StageType MoveRelativeData::getType() const { return StageType::MOVE_RELATIVE; }
double MoveRelativeData::getDX() const { return dx_; }
double MoveRelativeData::getDY() const { return dy_; }
double MoveRelativeData::getDZ() const { return dz_; }