// movement_data_base.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef MOVEMENT_DATA_BASE_HPP
#define MOVEMENT_DATA_BASE_HPP

#include <moveit/task_constructor/stages.h>
#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/core/tasks/stages/stage_data.hpp"

class MovementDataBase : public StageData {
public:
    virtual ~MovementDataBase() = default;
    MovementDataBase(double vel_scaling = 0.1, double acc_scaling = 0.1)
      : velocity_scaling_(vel_scaling), acceleration_scaling_(acc_scaling) {}

    StagePtr createStage(const std::string& name, const NodePtr& node) const final;
    void setVelocityScalingFactor(double v) { velocity_scaling_ = v; }
    void setAccelerationScalingFactor(double a) { acceleration_scaling_ = a; }
    double getVelocityScalingFactor() const { return velocity_scaling_; }
    double getAccelerationScalingFactor() const { return acceleration_scaling_; }

protected:
    virtual std::shared_ptr<void> createPlannerImpl(const NodePtr& node, 
                                                    double vel_scaling, 
                                                    double acc_scaling) const = 0;
    virtual StagePtr createStageInstanceImpl(const std::string& name, 
                                             std::shared_ptr<void> planner) const = 0;
    virtual void configureStageImpl(Stage& stage, const NodePtr& node) const = 0;
    void setCommonInfo(Stage& stage, const NodePtr& node) const;

private:
    void setCommonExecutionInfo(Stage& stage) const;

    double velocity_scaling_;
    double acceleration_scaling_;
};

inline MovementDataBase::StagePtr 
MovementDataBase::createStage(const std::string& name, const NodePtr& node) const 
{
    // 1) Possibly read step size, fraction, or other parameters from Node
    //    or do override logic if your code wants. We keep it minimal here:
    double v_scale = velocity_scaling_;
    double a_scale = acceleration_scaling_;

    auto planner = createPlannerImpl(node, v_scale, a_scale);
    auto stage = createStageInstanceImpl(name, planner);
    configureStageImpl(*stage, node);

    return stage;
}

inline void MovementDataBase::setCommonInfo(Stage& stage, const NodePtr& node) const
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

inline void MovementDataBase::setCommonExecutionInfo(Stage& stage) const
{
  moveit::task_constructor::TrajectoryExecutionInfo exec_info;
  exec_info.controller_names = {"follow_joint_trajectory"};
  stage.setProperty("trajectory_execution_info", exec_info);
}

#endif // MOVEMENT_DATA_BASE_HPP