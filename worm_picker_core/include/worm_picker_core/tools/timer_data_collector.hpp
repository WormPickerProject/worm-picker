// Include guard
#ifndef TIMER_DATA_COLLECTOR_HPP
#define TIMER_DATA_COLLECTOR_HPP

#include <string>
#include <vector>
#include <mutex>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <nlohmann/json.hpp>

class TimerDataCollector
{
public:
    // Constructor
    TimerDataCollector(const std::string& output_directory = "");

    // Destructor
    ~TimerDataCollector();

    // Method to record timer data
    void recordTimerData(const std::string& command_name, const std::vector<std::pair<std::string, double>>& timer_results);

    // Method to save data to a JSON file
    void saveDataToFile();

private:
    std::mutex data_mutex_;
    nlohmann::json data_;
    std::string output_directory_;
};

#endif  // TIMER_DATA_COLLECTOR_HPP
