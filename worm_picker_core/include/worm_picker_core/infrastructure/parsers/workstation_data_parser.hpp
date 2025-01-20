// workstation_data_parser.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <nlohmann/json.hpp>
#include "worm_picker_core/core/model/workstation_data.hpp"

class WorkstationDataParser {
public:
    using WorkstationDataMap = std::unordered_map<std::string, WorkstationData>;
    
    explicit WorkstationDataParser(const std::string& file_path);
    const WorkstationDataMap& getWorkstationDataMap() const;

private:
    using json = nlohmann::json;

    void parseJsonFile(const std::string& file_path);
    bool hasInvalidValue(const json& col_data) const;
    Coordinate parseCoordinate(const json& coord_json) const;

    static constexpr double INVALID_VALUE = -9999.9;
    WorkstationDataMap workstation_data_map_;
};