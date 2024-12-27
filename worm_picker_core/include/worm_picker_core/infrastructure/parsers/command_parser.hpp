// command_parser.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/core/model/command_info.hpp"
#include "worm_picker_core/core/model/command_config.hpp"

class CommandParser {
public:
    using NodePtr = rclcpp::Node::SharedPtr;

    explicit CommandParser() = default;
    explicit CommandParser(const NodePtr& node);
    CommandInfo parse(const std::string& command);

private:
    using SpeedOverrideOpt = std::optional<std::pair<double, double>>;
    using CommandConfigPtr = std::shared_ptr<CommandConfig>;
    using CommandConfigVec = std::vector<CommandConfigPtr>;

    void initCommandConfigs(const NodePtr& node);
    const CommandConfig* findConfigForCommand(const std::string& command);
    static std::pair<std::string, size_t> getNextValue(const std::string& command, size_t pos);
    static std::string getBaseCommand(const std::string& command);
    static std::vector<std::string> parseArguments(const std::string& command);
    SpeedOverrideOpt extractSpeedOverride(
            const std::vector<std::string>& args,
            const std::string& baseCommand);

    CommandConfigVec configs_;
};

#endif // COMMAND_PARSER_HPP