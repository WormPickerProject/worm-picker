// timer_data_collector.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef TIMER_DATA_COLLECTOR_HPP
#define TIMER_DATA_COLLECTOR_HPP

#include <string>
#include <vector>
#include <mutex>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <rclcpp/rclcpp.hpp>

/**
 * @class TimerDataCollector
 * @brief Collects and stores timing data for various commands in JSON format
 * 
 * @details
 * TimerDataCollector manages the collection and persistence of timing data
 * for different commands. It provides operations for recording timing results 
 * and automatically saves data to a JSON file upon destruction.The output 
 * directory is configured via a ROS 2 parameter.
 */
class TimerDataCollector {
public:
    // Public Type Aliases
    using NodePtr = rclcpp::Node::SharedPtr;
    using TimerResult = std::pair<std::string, double>;
    using TimerResults = std::vector<TimerResult>;

    /**
     * @brief Constructs a TimerDataCollector with the specified ROS 2 node
     * 
     * @param node ROS 2 node pointer used to access parameters
     * @throws std::runtime_error if the output directory cannot be created
     */
    explicit TimerDataCollector(const NodePtr& node);

    /**
     * @brief Saves collected data to file and destructs the object
     */
    ~TimerDataCollector();

    /**
     * @brief Records timing data for a specific command
     * 
     * @param command_name Name of the command being timed
     * @param timer_results Vector of timing results (name-duration pairs)
     */
    void recordTimerData(const std::string& command_name, const TimerResults& timer_results);

    /**
     * @brief Explicitly saves the current data to file
     * 
     * @throws std::runtime_error if unable to open or write to the output file
     */
    void saveDataToFile() const;

private:
    /**
     * @brief Initializes the output directory from node parameters
     * 
     * @param node ROS 2 node pointer
     * @throws std::runtime_error if directory creation fails
     */
    void initializeOutputDirectory(const NodePtr& node);

    mutable std::mutex data_mutex_;        ///< Mutex for thread-safe data access
    nlohmann::json data_;                  ///< JSON structure holding timing data
    std::filesystem::path output_path_;    ///< Full path to output directory
};

#endif  // TIMER_DATA_COLLECTOR_HPP
