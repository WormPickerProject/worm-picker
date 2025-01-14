// calibration_points_parser.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <fstream>
#include "worm_picker_core/infrastructure/parsers/calibration_points_parser.hpp"

CalibrationPointsParser::CalibrationPointsParser(const std::string& file_path) 
{
    parseJsonFile(file_path);
}

void CalibrationPointsParser::parseJsonFile(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open calibration points file: " + file_path);
    }

    auto data = json::parse(file);
    const auto& points = data["initial_calibration_points"];

    for (const auto& point : points) {
        const auto& key = point["calibration_point"].get<std::string>();
        const auto& positions = point["joint_positions"];
        MoveToJointData joint_data(
            positions[0].get<double>(),
            positions[1].get<double>(), 
            positions[2].get<double>(),
            positions[3].get<double>(),
            positions[4].get<double>(),
            positions[5].get<double>()
        );

        point_map_.emplace(key, joint_data);
        point_order_.push_back(key);
    }
}

const CalibrationPointsParser::PointMap& CalibrationPointsParser::getCalibrationPointMap() const 
{
    return point_map_;
}

const std::vector<std::string>& CalibrationPointsParser::getPointOrder() const 
{
    return point_order_;
}
