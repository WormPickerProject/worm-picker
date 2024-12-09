// calibration_points_parser.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef CALIBRATION_POINTS_PARSER_HPP
#define CALIBRATION_POINTS_PARSER_HPP

#include <nlohmann/json.hpp>
#include "worm_picker_core/stages/move_to_joint_data.hpp"

class CalibrationPointsParser {
public:
    explicit CalibrationPointsParser(const std::string& file_path);
    const std::vector<MoveToJointData>& getCalibrationPoints() const;

private:
    using json = nlohmann::json;
    void parseJsonFile(const std::string& file_path);
    std::vector<MoveToJointData> points_;
};

#endif // CALIBRATION_POINTS_PARSER_HPP
