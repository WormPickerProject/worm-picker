// timer_data_collector.cpp 
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tools/timing/timer_data_collector.hpp"

TimerDataCollector::TimerDataCollector(const NodePtr& node)
    : data_(nlohmann::json::array())
{
    if (!node) {
        throw std::invalid_argument("Node pointer cannot be null");
    }
    initializeOutputDirectory(node);
}

void TimerDataCollector::initializeOutputDirectory(const NodePtr& node) 
{
    const auto relative_directory = node->get_parameter("timer_log_path").as_string();
    const auto base_directory = std::filesystem::current_path().string();
    output_path_ = base_directory + relative_directory;

    std::error_code ec;
    if (!std::filesystem::create_directories(output_path_, ec) && ec) {
        throw std::runtime_error(
            "Failed to create output directory: " + output_path_.string() + 
            " Error: " + ec.message()
        );
    }
}

TimerDataCollector::~TimerDataCollector()
{
    saveDataToFile();
}

void TimerDataCollector::recordTimerData(const std::string& command_name,
                                         const TimerResults& timer_results)
{
    std::lock_guard<std::mutex> lock(data_mutex_);

    nlohmann::json command_data = {
        {"command", command_name},
        {"timers", nlohmann::json::array()}
    };

    for (const auto& [timer_name, timer_duration] : timer_results) {
        command_data["timers"].push_back({
            {"name", timer_name},
            {"duration", timer_duration}
        });
    }

    data_.push_back(std::move(command_data));
}

void TimerDataCollector::saveDataToFile() const
{
    std::lock_guard<std::mutex> lock(data_mutex_);
    const auto file_path = output_path_ / "/timer_data.json";

    std::ofstream file(file_path);
    if (!file) {
        throw std::runtime_error("Unable to open file: " + file_path.string());
    }

    file << data_.dump(4);
    if (!file) {
        throw std::runtime_error("Failed to write to file: " + file_path.string());
    }
}
