// workstation_geometry_parser.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <fstream>
#include "worm_picker_core/infrastructure/parsers/workstation_geometry_parser.hpp"

WorkstationGeometryParser::WorkstationGeometryParser(const std::string& file_path) 
{
    parseJsonFile(file_path);
}

void WorkstationGeometryParser::parseJsonFile(const std::string& file_path) 
{
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open workstation geometry file: " + file_path);
    }

    auto data = json::parse(file);
    geometry_.setRaySeparationAngle(data["ray_separation_angle"].get<double>());

    const auto& points = data["fixed_points"];
    for (const auto& point : points) {
        geometry_.addFixedPoint({
            point["id"].get<std::string>(),
            point["x"].get<double>(),
            point["y"].get<double>()
        });
    }
}

const WorkstationGeometry& WorkstationGeometryParser::getGeometry() const 
{
    return geometry_;
}
