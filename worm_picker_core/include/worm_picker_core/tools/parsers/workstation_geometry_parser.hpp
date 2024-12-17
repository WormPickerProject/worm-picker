// workstation_geometry_parser.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef WORKSTATION_GEOMETRY_PARSER_HPP
#define WORKSTATION_GEOMETRY_PARSER_HPP

#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "worm_picker_core/common/data_types/fixed_point.hpp"
#include "worm_picker_core/common/data_types/workstation_geometry.hpp"

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