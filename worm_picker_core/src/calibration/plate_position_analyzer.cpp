// plate_position_analyzer.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <filesystem>
#include "worm_picker_core/calibration/plate_position_analyzer.hpp"
#include "worm_picker_core/tools/parsers/workstation_geometry_parser.hpp"

PlatePositionAnalyzer::PlatePositionAnalyzer(const PoseMap& recorded_positions)
    : recorded_positions_(recorded_positions)
{
    const auto current_path = std::filesystem::current_path().string();
    const auto config_path = "/worm-picker/worm_picker_core/config/workstation_geometry.json";
    workstation_geometry_ = WorkstationGeometryParser(current_path + config_path).getGeometry();
}

PlatePositionAnalyzer::NormalizedPoseSet PlatePositionAnalyzer::normalizeAllPoints() const {
    NormalizedPoseSet result;

    for (const auto& [ref_name, recorded_pose] : recorded_positions_) {
        const auto fixed_ref = std::ranges::find_if(workstation_geometry_.fixed_points, 
            [&ref_name](const auto& point) { return point.name == ref_name; });

        const auto& ref_x = fixed_ref->x;
        const auto& ref_y = fixed_ref->y;
        const auto& recorded_x = recorded_pose.pose.position.x;
        const auto& recorded_y = recorded_pose.pose.position.y;

        auto& normalized_points = result[ref_name];
        for (const auto& point : workstation_geometry_.fixed_points) {
            auto normalized = recorded_pose; 
            auto& pos = normalized.pose.position;
            
            pos.x = (point.x - ref_x) * MM_TO_M + recorded_x;
            pos.y = (point.y - ref_y) * MM_TO_M + recorded_y;
            
            normalized_points[point.name] = normalized;
        }
    }

    return result;
}
