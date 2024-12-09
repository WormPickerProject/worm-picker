// workstation_geometry_parser.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef WORKSTATION_GEOMETRY_PARSER_HPP
#define WORKSTATION_GEOMETRY_PARSER_HPP

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

struct FixedPoint {
    std::string name;
    double x;
    double y;
};

struct WorkstationGeometry {
    double ray_separation_angle;
    std::vector<FixedPoint> fixed_points;
};

class WorkstationGeometryParser {
public:
    explicit WorkstationGeometryParser(const std::string& file_path);
    const WorkstationGeometry& getGeometry() const;

private:
    using json = nlohmann::json;
    void parseJsonFile(const std::string& file_path);
    WorkstationGeometry geometry_;
};

#endif // WORKSTATION_GEOMETRY_PARSER_HPP