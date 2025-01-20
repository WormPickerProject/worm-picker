// workstation_geometry_parser.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <nlohmann/json.hpp>
#include "worm_picker_core/core/geometry/fixed_point.hpp"
#include "worm_picker_core/core/geometry/workstation_geometry.hpp"

class WorkstationGeometryParser {
public:
    explicit WorkstationGeometryParser(const std::string& file_path);
    const WorkstationGeometry& getGeometry() const;

private:
    using json = nlohmann::json;

    void parseJsonFile(const std::string& file_path);

    WorkstationGeometry geometry_;
};