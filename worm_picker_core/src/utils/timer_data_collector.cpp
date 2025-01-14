// timer_data_collector.cpp 
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <fstream>
#include <filesystem>
#include "worm_picker_core/utils/timer_data_collector.hpp"
#include "worm_picker_core/utils/parameter_utils.hpp"

TimerDataCollector::TimerDataCollector(const NodePtr& node)
    : data_(nlohmann::json::array())
{
    initializeOutputDirectory(node);
}

void TimerDataCollector::initializeOutputDirectory(const NodePtr& node) 
{
    const auto base_path = std::filesystem::current_path().string();
    auto relative_path = param_utils::getParameter<std::string>(node, "config_files.timer_log");
    output_path_ = base_path + *relative_path;

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
    const std::filesystem::path file_path(output_path_.string() + "/timer_data.json");

    std::ofstream file(file_path);
    if (!file) {
        throw std::runtime_error("Unable to open file: " + file_path.string());
    }

    file << data_.dump(4);
    if (!file) {
        throw std::runtime_error("Failed to write to file: " + file_path.string());
    }

    file.close();
}
