#include "worm_picker_core/tools/parsers/hotel_data_parser.hpp"
#include <fstream>
#include <iostream>

HotelDataParser::HotelDataParser(const std::string& file_path) 
{
    (void)file_path;  // Cast file_path to void to avoid unused variable warning
}

const std::unordered_map<std::string, HotelData>& HotelDataParser::getHotelDataMap() const 
{
    return hotel_data_map_;  // Returning an empty map for now
}
