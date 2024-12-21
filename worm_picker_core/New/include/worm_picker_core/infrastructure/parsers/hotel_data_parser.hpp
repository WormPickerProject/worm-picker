// hotel_data_parser.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef HOTEL_DATA_PARSER_HPP
#define HOTEL_DATA_PARSER_HPP

#include <nlohmann/json.hpp>
#include "worm_picker_core/core/model/hotel_data.hpp"

class HotelDataParser {
public:
    using HotelDataMap = std::unordered_map<std::string, HotelData>;

    explicit HotelDataParser(const std::string& file_path);
    const HotelDataMap& getHotelDataMap() const;

private:
    HotelDataMap hotel_data_map_;
};

#endif // HOTEL_DATA_PARSER_HPP
