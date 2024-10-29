// workstation_data_parser.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
//
// Licensed under the Apache License, Version 2.0 (the "License");

#ifndef WORKSTATION_DATA_PARSER_HPP
#define WORKSTATION_DATA_PARSER_HPP

#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include "worm_picker_core/tasks/task_data_structure.hpp"

/**
 * @brief Class responsible for parsing workstation data from a JSON file.
 */
class WorkstationDataParser 
{
public:
    /**
     * @brief Constructs a parser with the given file path.
     * @param file_path Path to the JSON file.
     * @param node Shared pointer to the ROS2 node.
     */
    explicit WorkstationDataParser(const std::string& file_path);

    /**
     * @brief Retrieves the parsed workstation data map.
     * @return A constant reference to the workstation data map.
     */
    const std::unordered_map<std::string, WorkstationData>& getWorkstationDataMap() const;

private:
    /**
     * @brief Parses the JSON file.
     * @param file_path Path to the JSON file.
     * @param node Shared pointer to the ROS2 node.
     */
    void parseJsonFile(const std::string& file_path);

    /**
     * @brief Checks for invalid values in the JSON data.
     * @param col_data JSON data for a column.
     * @return True if invalid values are found, otherwise false.
     */
    bool hasInvalidValue(const nlohmann::json& col_data) const;

    /**
     * @brief Parses the coordinate data from JSON.
     * @param coord_json JSON data for coordinates.
     * @return Parsed Coordinate structure.
     */
    Coordinate parseCoordinate(const nlohmann::json& coord_json) const;

    // Type aliases
    using json = nlohmann::json;
    using WorkstationDataMap = std::unordered_map<std::string, WorkstationData>;

    static constexpr double INVALID_VALUE = -9999.9;  ///< Invalid value constant.

    WorkstationDataMap workstation_data_map_;  ///< Map of workstation IDs (e.g., "A1") to `WorkstationData` containing Cartesian `Coordinate` positions.
};

#endif // WORKSTATION_DATA_PARSER_HPP
