// workstation_data_parser.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
//
// Licensed under the Apache License, Version 2.0 (the "License");

#include "worm_picker_core/tools/parsers/workstation_data_parser.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>

WorkstationDataParser::WorkstationDataParser(const std::string& file_path, const rclcpp::Node::SharedPtr& node)
{
    parseJsonFile(file_path, node);
}

const std::unordered_map<std::string, WorkstationData>& WorkstationDataParser::getWorkstationDataMap() const 
{
    return workstation_data_map_;
}

void WorkstationDataParser::parseJsonFile(const std::string& file_path, const rclcpp::Node::SharedPtr& node)
{
    const std::string current_path = std::filesystem::current_path().string();
    std::ifstream file(current_path + file_path);
    if (!file.is_open()) {
        RCLCPP_ERROR(node->get_logger(), "Failed to open %s", (current_path + file_path).c_str());
    }

    json workstation_json;
    file >> workstation_json;

    for (const auto& row : workstation_json) {
        const std::string row_letter = row["row_letter"].get<std::string>();

        for (const auto& [col_num, col_data] : row["columns"].items()) {
            const std::string key = row_letter + col_num;

            if (hasInvalidValue(col_data)) {
                continue;
            }

            Coordinate coord = parseCoordinate(col_data["coordinate"]);
            Joint joint = parseJoint(col_data["joint"]);

            workstation_data_map_.emplace(key, WorkstationData{coord, joint});
        }
    }
}

bool WorkstationDataParser::hasInvalidValue(const json& col_data) const 
{
    const std::vector<std::string> coordinate_keys = {
        "position_x", "position_y", "position_z",
        "orientation_x", "orientation_y", "orientation_z", "orientation_w"
    };

    const std::vector<std::string> joint_keys = {
        "joint_1", "joint_2", "joint_3", "joint_4", "joint_5", "joint_6"
    };

    const auto& coord = col_data["coordinate"];
    for (const auto& key : coordinate_keys) {
        if (coord[key].get<double>() == INVALID_VALUE) {
            return true;
        }
    }

    const auto& joint = col_data["joint"];
    for (const auto& key : joint_keys) {
        if (joint[key].get<double>() == INVALID_VALUE) {
            return true;
        }
    }

    return false;
}

Coordinate WorkstationDataParser::parseCoordinate(const json& coord_json) const 
{
    return Coordinate{
        coord_json["position_x"].get<double>(),
        coord_json["position_y"].get<double>(),
        coord_json["position_z"].get<double>(),
        coord_json["orientation_x"].get<double>(),
        coord_json["orientation_y"].get<double>(),
        coord_json["orientation_z"].get<double>(),
        coord_json["orientation_w"].get<double>()
    };
}

Joint WorkstationDataParser::parseJoint(const json& joint_json) const 
{
    return Joint{
        joint_json["joint_1"].get<double>(),
        joint_json["joint_2"].get<double>(),
        joint_json["joint_3"].get<double>(),
        joint_json["joint_4"].get<double>(),
        joint_json["joint_5"].get<double>(),
        joint_json["joint_6"].get<double>()
    };
}
