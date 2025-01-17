// command_parser.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/infrastructure/parsers/command_parser.hpp"
#include <fmt/format.h>

CommandParser::CommandParser(const NodePtr& node) 
{
    initCommandConfigs(node);
}

void CommandParser::initCommandConfigs(const NodePtr& node) 
{
    configs_ = {
        std::make_shared<ZeroArgsConfig>(node),
        std::make_shared<OneArgConfig>(node),
        std::make_shared<ThreeArgsConfig>(node)
    };
}

Result<CommandInfo> CommandParser::parse(const std::string& command)
{
    auto tokens = tokenizeByColon(command);

    if (tokens.empty()) {
        throw std::runtime_error(fmt::format("Command '{}' is empty or invalid", command));
    }

    const std::string& base_command = tokens.front();
    const CommandConfig* config = findConfigForCommand(base_command);

    if (!config) {
        return Result<CommandInfo>::error(
            fmt::format("No CommandConfig found for base command '{}'", base_command));
    }

    std::vector<std::string> args;
    if (tokens.size() > 1) {
        args.assign(tokens.begin() + 1, tokens.end());
    }

    CommandInfo info;
    info.setBaseCommand(base_command);
    info.setBaseArgsAmount(config->getBaseArgumentCount());
    info.setArgs(args);
    info.setSpeedOverride(extractSpeedOverride(args, config));

    return Result<CommandInfo>::success(info);
}

const CommandConfig* CommandParser::findConfigForCommand(const std::string& base_command) const
{
    for (const auto& config : configs_) {
        const auto& names = config->getArgumentNames();
        if (std::find(names.begin(), names.end(), base_command) != names.end()) {
            return config.get();
        }
    }

    RCLCPP_WARN(rclcpp::get_logger("CommandParser"),
                "No config found for command: %s", base_command.c_str());
    return nullptr;
}

std::vector<std::string> CommandParser::tokenizeByColon(const std::string& str)
{
    std::vector<std::string> tokens;
    std::size_t start = 0;
    while (true) {
        std::size_t pos = str.find(':', start);
        if (pos == std::string::npos) {
            tokens.push_back(str.substr(start));
            break;
        }
        tokens.push_back(str.substr(start, pos - start));
        start = pos + 1;
    }
    return tokens;
}

CommandParser::SpeedOverrideOpt
CommandParser::extractSpeedOverride(const std::vector<std::string>& args,
                                    const CommandConfig* config) const
{
    const std::size_t expected_base_args = config->getBaseArgumentCount();
    if (args.size() != expected_base_args + 2) {
        RCLCPP_INFO(rclcpp::get_logger("CommandParser"),
                    "Not extracting speed override; arg count is %zu, expected %zu + 2",
                    args.size(), expected_base_args);
        return std::nullopt;
    }

    try {
        double v = std::stod(args[expected_base_args]);
        double a = std::stod(args[expected_base_args + 1]);

        if (v > 0 && v <= 1 && a > 0 && a <= 1) {
            RCLCPP_INFO(rclcpp::get_logger("CommandParser"),
                        "Parsed speed override -> Speed: %f; Accel: %f", v, a);
            return std::make_pair(v, a);
        }

    } catch (const std::exception& e) {
        RCLCPP_WARN(rclcpp::get_logger("CommandParser"),
            "Failed parsing speed override: %s", e.what());
    }
    return std::nullopt;
}