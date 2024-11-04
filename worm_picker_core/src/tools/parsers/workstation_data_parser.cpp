// workstation_data_parser.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tools/parsers/workstation_data_parser.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>

WorkstationDataParser::WorkstationDataParser(const std::string& file_path)
{
    parseJsonFile(file_path);
}

const std::unordered_map<std::string, WorkstationData>& WorkstationDataParser::getWorkstationDataMap() const 
{
    return workstation_data_map_;
}

void WorkstationDataParser::parseJsonFile(const std::string& file_path) 
{
    const std::string current_path = std::filesystem::current_path().string();
    std::ifstream file(current_path + file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + current_path + file_path);
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
            workstation_data_map_.emplace(key, WorkstationData{coord});
        }
    }
}

bool WorkstationDataParser::hasInvalidValue(const json& col_data) const 
{
    const std::vector<std::string> coordinate_keys = {
        "position_x", "position_y", "position_z",
        "orientation_x", "orientation_y", "orientation_z", "orientation_w"
    };

    const auto& coord = col_data["coordinate"];
    for (const auto& key : coordinate_keys) {
        if (coord[key].get<double>() == INVALID_VALUE) {
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
