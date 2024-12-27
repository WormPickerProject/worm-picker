// move_relative_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef MOVE_RELATIVE_DATA_HPP
#define MOVE_RELATIVE_DATA_HPP

#include <moveit/task_constructor/solvers.h>
#include "worm_picker_core/core/tasks/stages/movement_data_base.hpp"

class MoveRelativeData : public MovementDataBase {
public:
    MoveRelativeData() : MovementDataBase(0.1, 0.1) {}
    MoveRelativeData(double dx, double dy, double dz,
                     double vel_scaling = 0.1, double acc_scaling = 0.1)
        : MovementDataBase(vel_scaling, acc_scaling), 
          dx_(dx), dy_(dy), dz_(dz) {}

    StageType getType() const override { return StageType::MOVE_RELATIVE; }
    constexpr double getDX() const { return dx_; }
    constexpr double getDY() const { return dy_; }
    constexpr double getDZ() const { return dz_; }

protected:
    std::shared_ptr<void> createPlannerImpl(const NodePtr& node, 
                                            double vel_scaling, 
                                            double acc_scaling) const override;
    StagePtr createStageInstanceImpl(const std::string& name, 
                                     std::shared_ptr<void> planner) const override;
    void configureStageImpl(Stage& stage, const NodePtr& node) const override;

private:
    double dx_{};
    double dy_{};
    double dz_{};
};

inline std::shared_ptr<void> MoveRelativeData::createPlannerImpl(const NodePtr& node, 
                                                                 double vel_scaling, 
                                                                 double acc_scaling) const 
{
    using namespace moveit::task_constructor;
    auto cartesian_planner = std::make_shared<solvers::CartesianPath>();
    cartesian_planner->setMaxVelocityScalingFactor(vel_scaling);
    cartesian_planner->setMaxAccelerationScalingFactor(acc_scaling);

    auto step_size = param_utils::getParameter<double>(node, "validation.step_size");
    cartesian_planner->setStepSize(*step_size);
    
    auto min_fraction = param_utils::getParameter<double>(node, "validation.min_fraction");
    cartesian_planner->setMinFraction(*min_fraction);
    
    return cartesian_planner;
}

inline MoveRelativeData::StagePtr 
MoveRelativeData::createStageInstanceImpl(const std::string& name, 
                                          std::shared_ptr<void> planner) const 
{
    using namespace moveit::task_constructor;
    auto cartesian_planner = std::static_pointer_cast<solvers::CartesianPath>(planner);
    auto stage = std::make_unique<stages::MoveRelative>(name, cartesian_planner);
    return stage;
}

inline void MoveRelativeData::configureStageImpl(Stage& stage, const NodePtr& node) const 
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

#endif // MOVE_RELATIVE_DATA_HPP