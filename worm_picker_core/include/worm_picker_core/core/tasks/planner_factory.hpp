// planner_factory.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <moveit/task_constructor/solvers.h>
#include "worm_picker_core/utils/parameter_utils.hpp"

class PlannerFactory {
public:
    using NodePtr = rclcpp::Node::SharedPtr;
    using PlanPtr = std::shared_ptr<moveit::task_constructor::solvers::PlannerInterface>;
    using PlannerInfo = std::pair<std::optional<std::string>, std::string>;
    using CreatorFunc = std::function<PlanPtr(const NodePtr&, const std::string&, double, double)>;

    static PlannerFactory& getInstance();
    void registerPlannerCreator(const std::string& planner_type, CreatorFunc creator);
    PlanPtr createPlanner(const PlannerInfo& planner_info_1,
                          const PlannerInfo& planner_info_2, 
                          const NodePtr& node,
                          double vel_scaling, 
                          double acc_scaling) const;

private:
    PlannerFactory();
    PlannerFactory(const PlannerFactory&) = delete;
    PlannerFactory& operator=(const PlannerFactory&) = delete;

    std::map<std::string, CreatorFunc> planner_creators_;
};