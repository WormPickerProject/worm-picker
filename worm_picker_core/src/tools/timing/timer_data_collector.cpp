// timer_data_collector.cpp 
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tools/timing/timer_data_collector.hpp"

TimerDataCollector::TimerDataCollector(const std::string& output_directory)
    : data_(nlohmann::json::array()), 
      output_directory_(std::filesystem::current_path().string() + (output_directory.empty() ? "" : output_directory))
{
    std::filesystem::create_directories(output_directory_);
}

TimerDataCollector::~TimerDataCollector()
{
    saveDataToFile();
}

void TimerDataCollector::recordTimerData(const std::string& command_name, const std::vector<std::pair<std::string, double>>& timer_results)
{
    std::lock_guard<std::mutex> lock(data_mutex_);

    nlohmann::json command_data = {
        {"command", command_name},
        {"timers", nlohmann::json::array()}
    };

    for (const auto& [timer_name, timer_duration] : timer_results)
    {
        command_data["timers"].push_back({
            {"name", timer_name},
            {"duration", timer_duration}
        });
    }

    data_.push_back(command_data);
}

void TimerDataCollector::saveDataToFile()
{
    std::lock_guard<std::mutex> lock(data_mutex_);
    const std::string file_path = output_directory_ + "/timer_data.json";

    std::ofstream file(file_path);
    if (!file)
    {
        // std::cerr << "Error: Unable to open file at " << file_path << "\n";
        return;
    }

    file << data_.dump(4);
}
