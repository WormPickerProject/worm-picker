#ifndef HOTEL_DATA_PARSER_HPP
#define HOTEL_DATA_PARSER_HPP

#include <string>
#include <unordered_map>
#include "worm_picker_core/common/coordinate.hpp"

/**
 * @brief Class responsible for (placeholder) parsing hotel data from a JSON file.
 */
class HotelDataParser 
{
public:
    /**
     * @brief Constructs a parser with the given file path.
     * @param file_path Path to the JSON file.
     */
    explicit HotelDataParser(const std::string& file_path);

    /**
     * @brief Retrieves the parsed hotel data map (empty for now).
     * @return A constant reference to the empty hotel data map.
     */
    const std::unordered_map<std::string, HotelData>& getHotelDataMap() const;

private:
    std::unordered_map<std::string, HotelData> hotel_data_map_;  ///< Empty map for now
};

#endif // HOTEL_DATA_PARSER_HPP
