// calibration_points_parser.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef CALIBRATION_POINTS_PARSER_HPP
#define CALIBRATION_POINTS_PARSER_HPP

#include <nlohmann/json.hpp>
#include "worm_picker_core/core/tasks/stages/move_to_joint_data.hpp"

class CalibrationPointsParser {
public:
    using PointMap = std::map<std::string, MoveToJointData>;

    explicit CalibrationPointsParser(const std::string& file_path);
    const PointMap& getCalibrationPointMap() const;
    const std::vector<std::string>& getPointOrder() const;

private:
    using json = nlohmann::json;

    void parseJsonFile(const std::string& file_path);

    PointMap point_map_;
    std::vector<std::string> point_order_;
};

#endif // CALIBRATION_POINTS_PARSER_HPP
