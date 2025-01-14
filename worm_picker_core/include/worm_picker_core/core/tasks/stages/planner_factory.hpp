// planner_factory.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#ifndef PLANNER_FACTORY_HPP
#define PLANNER_FACTORY_HPP

#include <rclcpp/rclcpp.hpp>
#include <moveit/task_constructor/solvers.h>
#include "worm_picker_core/utils/parameter_utils.hpp"

class PlannerFactory {
public:
    using NodePtr = rclcpp::Node::SharedPtr;
    using PlanPtr = std::shared_ptr<moveit::task_constructor::solvers::PlannerInterface>;
    using PlannerInfo = std::pair<std::optional<std::string>, std::string>;
    using CreatorFunc = std::function<PlanPtr(const NodePtr&, const std::string&, double, double)>;

    static PlannerFactory& getInstance() {
        static PlannerFactory instance;
        return instance;
    }

    void registerPlannerCreator(const std::string& planner_type, CreatorFunc creator) {
        planner_creators_[planner_type] = std::move(creator);
    }

    PlanPtr createPlanner(const PlannerInfo& planner_info_1,
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

private:
    PlannerFactory() {
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
    }

    std::map<std::string, CreatorFunc> planner_creators_;
};

#endif // PLANNER_FACTORY_HPP