// hotel_data_parser.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <fstream>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include "worm_picker_core/infrastructure/parsers/hotel_data_parser.hpp"

HotelDataParser::HotelDataParser(const std::string& file_path) 
{
    parseJsonFile(file_path);
}

const HotelDataParser::HotelDataMap& HotelDataParser::getHotelDataMap() const 
{
    return hotel_data_map_;
}

void HotelDataParser::parseJsonFile(const std::string& file_path) 
{
    const auto package_share_dir = ament_index_cpp::get_package_share_directory("worm_picker_core");
    std::ifstream file(package_share_dir + file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + package_share_dir + file_path);
    }

    json hotel_json;
    file >> hotel_json;
    RoomInfoVec validRooms;

    for (const auto& hotel_entry : hotel_json) {
        for (const auto& [hotel_num, hotel_data] : hotel_entry["hotel"].items()) {
            for (const auto& [floor_num, floor_data] : hotel_data["floor"].items()) {
                for (const auto& [room_num, room_data] : floor_data["room"].items()) {
                    const auto& coord_json = room_data["coordinate"];
                    if (!hasInvalidValue(coord_json)) {
                        Coordinate coord = parseCoordinate(coord_json);
                        validRooms.emplace_back(hotel_num, floor_num, room_num, coord);
                    }
                }
            }
        }
    }

    for (const auto& [hotel, floor, room, coord] : validRooms) {
        std::string key = hotel + floor + room;
        hotel_data_map_.emplace(key, HotelData{coord});
    }
}

bool HotelDataParser::hasInvalidValue(const json& coord_json) const 
{
    const std::vector<std::string> coordinate_keys = {
        "position_x", "position_y", "position_z",
        "orientation_x", "orientation_y", "orientation_z", "orientation_w"
    };

    return std::any_of(coordinate_keys.begin(), coordinate_keys.end(),
        [this, &coord_json](const std::string& key) {
            return std::abs(coord_json[key].get<double>() - INVALID_VALUE) < 1e-6;
        });
}

Coordinate HotelDataParser::parseCoordinate(const json& coord_json) const 
{
    return Coordinate{
        coord_json["position_x"].get<double>(),
        coord_json["position_y"].get<double>(),
        coord_json["position_z"].get<double>(),
        coord_json["orientation_x"].get<double>(),
        coord_json["orientation_y"].get<double>(),
        coord_json["orientation_z"].get<double>(),
        coord_json["orientation_w"].get<double>()
    };
}