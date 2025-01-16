// movement_data_base.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <moveit/task_constructor/stages.h>
#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/core/tasks/planner_factory.hpp"
#include "worm_picker_core/core/tasks/stages/movement_data_base.hpp"

MovementDataBase::MovementDataBase(double vel_scaling, double acc_scaling)
    : velocity_scaling_(vel_scaling), 
      acceleration_scaling_(acc_scaling) {}

MovementDataBase::StagePtr 
MovementDataBase::createStage(const std::string& name, const NodePtr& node) const 
{
    auto planner = createPlannerImpl(node, velocity_scaling_, acceleration_scaling_);
    auto stage = createStageInstanceImpl(name, planner);
    configureStageImpl(*stage, node);
    return stage;
}

std::shared_ptr<void> MovementDataBase::createPlannerImpl(const NodePtr& node, 
                                                          double vel_scaling, 
                                                          double acc_scaling) const 
{
    auto planners = [&]() -> std::pair<std::pair<std::optional<std::string>, std::string>,
                                       std::pair<std::optional<std::string>, std::string>> {
        auto it = type_map_.find(getType());
        const std::string base = "planners." + it->second;
        return std::make_pair(
            std::make_pair(param_utils::getParameter<std::string>(node, base + ".primary"), base),
            std::make_pair(param_utils::getParameter<std::string>(node, base + ".backup"), base)
        );
    }();

    auto planner_ptr = PlannerFactory::getInstance().createPlanner(
            planners.first, planners.second, node, vel_scaling, acc_scaling);

    return std::static_pointer_cast<void>(planner_ptr);
}

void MovementDataBase::setCommonInfo(Stage& stage, const NodePtr& node) const
{
    auto ee_link = param_utils::getParameter<std::string>(node, "end_effectors.current_factor");
    auto move_group = param_utils::getParameter<std::string>(node, "operation_modes.group");

    using namespace moveit::task_constructor;
    if (auto* move_to_stage = dynamic_cast<stages::MoveTo*>(&stage)) {
        move_to_stage->setGroup(*move_group);
        move_to_stage->setIKFrame(*ee_link);
        setCommonExecutionInfo(*move_to_stage);  
    } else if (auto* move_relative_stage = dynamic_cast<stages::MoveRelative*>(&stage)) {
        move_relative_stage->setGroup(*move_group);
        move_relative_stage->setIKFrame(*ee_link);
        setCommonExecutionInfo(*move_relative_stage);
    }
}

void MovementDataBase::setCommonExecutionInfo(Stage& stage) const
{
    moveit::task_constructor::TrajectoryExecutionInfo exec_info;
    exec_info.controller_names = {"follow_joint_trajectory"};
    stage.setProperty("trajectory_execution_info", exec_info);
}

void MovementDataBase::setVelocityScalingFactor(double v) 
{ 
    velocity_scaling_ = v; 
}

void MovementDataBase::setAccelerationScalingFactor(double a) 
{ 
    acceleration_scaling_ = a; 
}

double MovementDataBase::getVelocityScalingFactor() const 
{ 
    return velocity_scaling_; 
}

double MovementDataBase::getAccelerationScalingFactor() const 
{ 
    return acceleration_scaling_; 
}