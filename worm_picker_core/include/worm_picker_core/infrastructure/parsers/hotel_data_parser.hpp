// hotel_data_parser.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <nlohmann/json.hpp>
#include "worm_picker_core/core/model/hotel_data.hpp"

class HotelDataParser {
public:
    using HotelDataMap = std::unordered_map<std::string, HotelData>;

    explicit HotelDataParser(const std::string& file_path);
    const HotelDataMap& getHotelDataMap() const;

private:
    using json = nlohmann::json;
    using RoomInfo = std::tuple<std::string, std::string, Coordinate>;
    using RoomInfoVec = std::vector<RoomInfo>;
    
    void parseJsonFile(const std::string& file_path);
    bool hasInvalidValue(const json& coord_json) const;
    Coordinate parseCoordinate(const json& coord_json) const;
    std::string generateKey(const std::string& hotel_num, const std::string& room_num) const; 

    static constexpr double INVALID_VALUE = -9999.9;
    HotelDataMap hotel_data_map_;
};