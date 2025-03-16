// command_parser.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/core/result.hpp"
#include "worm_picker_core/core/commands/command_info.hpp"
#include "worm_picker_core/core/commands/command_config.hpp"

class CommandParser {
public:
    using NodePtr = rclcpp::Node::SharedPtr;

    explicit CommandParser(const NodePtr& node);
    Result<CommandInfo> parse(const std::string& command);

private:
    using StringVec = std::vector<std::string>;
    using SpeedOverrideOpt = std::optional<std::pair<double, double>>;
    using CommandConfigPtr = std::shared_ptr<CommandConfig>;
    using CommandConfigVec = std::vector<CommandConfigPtr>;
    using CommandConfigMap = std::unordered_map<std::string, CommandConfigPtr>;
    using BaseConfigOptPair = std::optional<std::pair<const CommandConfig*, std::size_t>>;

    struct ParseContext {
        std::unique_ptr<VariableArgConfig> var_config;
        StringVec tokens;
        StringVec args;
        std::string base_command;
    };

    void initCommandParser(const NodePtr& node);
    void buildCommandMap();
    const CommandConfig* findConfigForCommand(ParseContext& ctx) const;
    const CommandConfig* handleVariableConfig(ParseContext& ctx) const;
    BaseConfigOptPair findBaseConfigForVariableCommand(const std::string& base_command) const;
    std::unique_ptr<VariableArgConfig> createVariableConfig(std::size_t N, 
                                                            std::size_t base_count) const;
    static StringVec tokenizeByColon(const std::string& input);
    std::optional<std::size_t> extractMovementCount(const std::string& token) const;
    SpeedOverrideOpt extractSpeedOverride(const StringVec& args, 
                                          const CommandConfig* config) const;
    Result<CommandInfo> createCommandInfo(ParseContext& ctx, 
                                          const CommandConfig* config) const;

    CommandConfigVec configs_;
    CommandConfigMap command_map_;
    rclcpp::Logger logger_{rclcpp::get_logger("CommandParser")};
};