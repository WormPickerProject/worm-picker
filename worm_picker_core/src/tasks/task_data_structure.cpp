// task_data_structure.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
// Additional Contributions: Fang-Yen Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");

#include "worm_picker_core/tasks/task_data_structure.hpp"

MoveToData::MoveToData(double px, double py, double pz, double ox, double oy, double oz, double ow,
                       double velocity_scaling, double acceleration_scaling) 
    : x(px), y(py), z(pz), qx(ox), qy(oy), qz(oz), qw(ow),
      velocity_scaling_factor(velocity_scaling), acceleration_scaling_factor(acceleration_scaling)
{
    tf2::Quaternion q(qx, qy, qz, qw);
    q.normalize();
    qx = q.x();
    qy = q.y();
    qz = q.z();
    qw = q.w();
}

JointData::JointData(double joint1, double joint2, double joint3, double joint4, double joint5, double joint6,
                     double velocity_scaling, double acceleration_scaling) 
    : velocity_scaling_factor(velocity_scaling), acceleration_scaling_factor(acceleration_scaling)
{
    const double deg_to_rad = M_PI / 180.0;

    joint_positions["joint_1"] = joint1 * deg_to_rad;
    joint_positions["joint_2"] = joint2 * deg_to_rad;
    joint_positions["joint_3"] = joint3 * deg_to_rad;
    joint_positions["joint_4"] = joint4 * deg_to_rad;
    joint_positions["joint_5"] = joint5 * deg_to_rad;
    joint_positions["joint_6"] = joint6 * deg_to_rad;
}

TaskData::TaskData(const std::map<std::string, std::shared_ptr<StageData>>& stage_data_map,
                   const std::initializer_list<std::string>& stage_names) 
{
    for (const auto& name : stage_names) {
        auto it = stage_data_map.find(name);
        if (it != stage_data_map.end()) {
            stages.emplace_back(it->second);
        } else {
            RCLCPP_ERROR(rclcpp::get_logger("TaskData"), "Stage name '%s' not found in stage_data_map.", name.c_str());
            throw std::invalid_argument("TaskData::TaskData failed: Stage name '" + name + "' not found.");
        }
    }
}