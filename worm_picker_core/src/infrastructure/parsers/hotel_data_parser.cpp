// hotel_data_parser.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/infrastructure/parsers/hotel_data_parser.hpp"

HotelDataParser::HotelDataParser(const std::string& file_path) 
{
    (void)file_path;
}

const HotelDataParser::HotelDataMap& HotelDataParser::getHotelDataMap() const 
{
    return hotel_data_map_;
}
