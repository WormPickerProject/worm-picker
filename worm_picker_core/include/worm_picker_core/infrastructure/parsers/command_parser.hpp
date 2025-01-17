// command_parser.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/core/result.hpp"
#include "worm_picker_core/core/commands/command_info.hpp"
#include "worm_picker_core/core/commands/command_config.hpp"

class CommandParser {
public:
    using NodePtr = rclcpp::Node::SharedPtr;

    explicit CommandParser() = default;
    explicit CommandParser(const NodePtr& node);
    Result<CommandInfo> parse(const std::string& command);

private:
    using SpeedOverrideOpt = std::optional<std::pair<double, double>>;
    using CommandConfigPtr = std::shared_ptr<CommandConfig>;
    using CommandConfigVec = std::vector<CommandConfigPtr>;

    void initCommandConfigs(const NodePtr& node);
    const CommandConfig* findConfigForCommand(const std::string& base_command) const;
    static std::vector<std::string> tokenizeByColon(const std::string& str);
    SpeedOverrideOpt extractSpeedOverride(const std::vector<std::string>& args,
                                          const CommandConfig* config) const;

    CommandConfigVec configs_;
};

#endif // COMMAND_PARSER_HPP