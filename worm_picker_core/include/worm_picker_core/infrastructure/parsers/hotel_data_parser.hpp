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
    HotelDataMap hotel_data_map_;
};