// calibration_points_parser.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <fstream>
#include "worm_picker_core/tools/parsers/calibration_points_parser.hpp"

CalibrationPointsParser::CalibrationPointsParser(const std::string& file_path) 
{
    parseJsonFile(file_path);
}

void CalibrationPointsParser::parseJsonFile(const std::string& file_path) 
{
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open calibration points file: " + file_path);
    }

    const auto data = json::parse(file);
    const auto& points = data["initial_calibration_points"];

    points_.reserve(points.size());
    for (const auto& point : points) {
        const auto& positions = point["joint_positions"];
        points_.emplace_back(
            positions[0].get<double>(),
            positions[1].get<double>(), 
            positions[2].get<double>(),
            positions[3].get<double>(),
            positions[4].get<double>(),
            positions[5].get<double>()
        );
    }
}

const std::vector<MoveToJointData>& CalibrationPointsParser::getCalibrationPoints() const 
{
    return points_;
}
