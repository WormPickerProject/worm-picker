// planner_factory.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/core/tasks/planner_factory.hpp"

PlannerFactory& PlannerFactory::getInstance() 
{
    static PlannerFactory instance;
    return instance;
}

void PlannerFactory::registerPlannerCreator(const std::string& planner_type, CreatorFunc creator) 
{
    planner_creators_[planner_type] = std::move(creator);
}

PlannerFactory::PlanPtr PlannerFactory::createPlanner(
    const PlannerInfo& planner_info_1,
    const PlannerInfo& planner_info_2, 
    const NodePtr& node,
    double vel_scaling, 
    double acc_scaling) const 
{
    if (planner_info_1.first) {
        const auto& planner_type = *planner_info_1.first;
        const auto it = planner_creators_.find(planner_type);
        
        if (it != planner_creators_.end()) {
            return it->second(node, planner_info_1.second, vel_scaling, acc_scaling);
        }
    }

    if (planner_info_2.first) {
        const auto& planner_type = *planner_info_2.first;
        const auto it = planner_creators_.find(planner_type);
        
        if (it != planner_creators_.end()) {
            return it->second(node, planner_info_2.second, vel_scaling, acc_scaling);
        }
    }

    throw std::runtime_error("No valid planner type specified");
}

PlannerFactory::PlannerFactory() 
{
    registerPlannerCreator("cartesian", 
        [](const NodePtr& node, const std::string& param_path, 
           double vel_scaling, double acc_scaling) -> PlanPtr 
        {
            using namespace moveit::task_constructor::solvers;
            auto planner = std::make_shared<CartesianPath>();
            planner->setMaxVelocityScalingFactor(vel_scaling);
            planner->setMaxAccelerationScalingFactor(acc_scaling);

            const std::string base_config = param_path + ".configs.cartesian.";
            if (auto step_size = param_utils::getParameter<double>(
                    node, base_config + "step_size")) {
                planner->setStepSize(*step_size);
            }
            if (auto min_fraction = param_utils::getParameter<double>(
                    node, base_config + "min_fraction")) {
                planner->setMinFraction(*min_fraction);
            }

            return planner;
        }
    );

    registerPlannerCreator("joint_interpolation",
        [](const NodePtr&, const std::string&, 
           double vel_scaling, double acc_scaling) -> PlanPtr 
        {
            using namespace moveit::task_constructor::solvers;
            auto planner = std::make_shared<JointInterpolationPlanner>();
            planner->setMaxVelocityScalingFactor(vel_scaling);
            planner->setMaxAccelerationScalingFactor(acc_scaling);
            return planner;
        }
    );

    registerPlannerCreator("pilz",
        [](const NodePtr& node, const std::string&, 
           double vel_scaling, double acc_scaling) -> PlanPtr 
        {
            using namespace moveit::task_constructor::solvers;
            auto planner = 
                std::make_shared<PipelinePlanner>(node, "pilz_industrial_motion_planner");
            planner->setPlannerId("LIN");
            planner->setMaxVelocityScalingFactor(vel_scaling);
            planner->setMaxAccelerationScalingFactor(acc_scaling);
            return planner;
        }
    );

    registerPlannerCreator("pilz_circ",
        [](const NodePtr& node, const std::string&, 
           double vel_scaling, double acc_scaling) -> PlanPtr 
        {
            using namespace moveit::task_constructor::solvers;
            auto planner = 
                std::make_shared<PipelinePlanner>(node, "pilz_industrial_motion_planner");
            planner->setPlannerId("CIRC");
            planner->setMaxVelocityScalingFactor(vel_scaling);
            planner->setMaxAccelerationScalingFactor(acc_scaling);
            return planner;
        }
    );
}