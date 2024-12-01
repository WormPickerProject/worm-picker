// calibration_points_parser.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tools/parsers/calibration_points_parser.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

CalibrationPointsParser::CalibrationPointsParser(const std::string& file_path) {
    parseJsonFile(file_path);
}

void CalibrationPointsParser::parseJsonFile(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open calibration points file: " + file_path);
    }

    json data_json;
    try {
        file >> data_json;
    } catch (const json::parse_error& e) {
        throw std::runtime_error("Failed to parse JSON file: " + std::string(e.what()));
    }

    if (!data_json.contains("calibration_points") || !data_json["calibration_points"].is_array()) {
        throw std::runtime_error("JSON does not contain a valid 'calibration_points' array.");
    }

    for (const auto& point_json : data_json["calibration_points"]) {
        if (!point_json.contains("joint_positions") || !point_json["joint_positions"].is_array()) {
            continue; // Skip invalid entries
        }

        const auto& joint_positions_json = point_json["joint_positions"];
        if (joint_positions_json.size() != 6) {
            continue; // Skip entries that do not have exactly 6 joint positions
        }

        try {
            // Extract joint positions as doubles
            double joint1 = joint_positions_json.at(0).get<double>();
            double joint2 = joint_positions_json.at(1).get<double>();
            double joint3 = joint_positions_json.at(2).get<double>();
            double joint4 = joint_positions_json.at(3).get<double>();
            double joint5 = joint_positions_json.at(4).get<double>();
            double joint6 = joint_positions_json.at(5).get<double>();

            // Create MoveToJointData object using the existing constructor
            MoveToJointData point(joint1, joint2, joint3, joint4, joint5, joint6);

            calibration_points_.push_back(std::move(point)); // Use move semantics
        } catch (const json::type_error& e) {
            throw std::runtime_error("Joint positions must be numeric values: " + std::string(e.what()));
        }
    }
}

const std::vector<MoveToJointData>& CalibrationPointsParser::getCalibrationPoints() const {
    return calibration_points_;
}
