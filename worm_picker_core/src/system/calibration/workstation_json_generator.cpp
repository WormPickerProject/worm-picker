// workstation_json_generator.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <fstream>
#include "worm_picker_core/system/calibration/workstation_json_generator.hpp"

WorkstationJsonGenerator::WorkstationJsonGenerator(const PoseMap& averaged_poses)
    : averaged_poses_(averaged_poses)
{
}

void WorkstationJsonGenerator::generateJson(const std::string& output_path) const
{
    auto json_data = generateJsonData();
    writeJsonToFile(json_data, output_path);
}

WorkstationJsonGenerator::OrderedJson WorkstationJsonGenerator::generateJsonData() const 
{
    OrderedJson json_array = OrderedJson::array();
    auto grouped_poses = groupPoses();

    for (char row = 'A'; row <= 'M'; ++row) {
        OrderedJson row_obj;
        row_obj["row_letter"] = std::string(1, row);
        row_obj["columns"] = OrderedJson::object();

        if (auto row_it = grouped_poses.find(row); row_it != grouped_poses.end()) {
            for (const auto& [col, pose_ptr] : row_it->second) {
                OrderedJson coordinate;
                coordinate["position_x"]   = pose_ptr->pose.position.x;
                coordinate["position_y"]   = pose_ptr->pose.position.y;
                coordinate["position_z"]   = pose_ptr->pose.position.z;
                coordinate["orientation_x"] = pose_ptr->pose.orientation.x;
                coordinate["orientation_y"] = pose_ptr->pose.orientation.y;
                coordinate["orientation_z"] = pose_ptr->pose.orientation.z;
                coordinate["orientation_w"] = pose_ptr->pose.orientation.w;

                row_obj["columns"][col]["coordinate"] = coordinate;
            }
        }

        json_array.push_back(row_obj);
    }

    return json_array;
}

void WorkstationJsonGenerator::writeJsonToFile(const OrderedJson& json_data,
                                               const std::string& output_path) const
{
    std::ofstream file(output_path, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open output file: " + output_path);
    }
    file << json_data.dump(4);
}

WorkstationJsonGenerator::GroupedPoseMap WorkstationJsonGenerator::groupPoses() const
{
    std::map<char, std::map<std::string, const geometry_msgs::msg::PoseStamped*>> grouped;
    for (const auto& [point_name, pose] : averaged_poses_) {
        char row = point_name[0];
        std::string col = point_name.substr(1);
        grouped[row][col] = &pose;
    }
    return grouped;
}