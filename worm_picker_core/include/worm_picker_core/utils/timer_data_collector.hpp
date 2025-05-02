// timer_data_collector.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include <rclcpp/rclcpp.hpp>

class TimerDataCollector {
public:
    using NodePtr = rclcpp::Node::SharedPtr;
    using TimerResult = std::pair<std::string, double>;
    using TimerResults = std::vector<TimerResult>;

    explicit TimerDataCollector(const NodePtr& node);
    ~TimerDataCollector();
    void recordTimerData(const std::string& command_name, const TimerResults& timer_results);
    void saveDataToFile() const;
    void flushIfBufferBig(std::size_t max_entries = 1000) const;

private:
    void initializeOutputDirectory(const NodePtr& node);

    mutable std::mutex data_mutex_;
    mutable nlohmann::json data_;
    std::filesystem::path output_path_;
};