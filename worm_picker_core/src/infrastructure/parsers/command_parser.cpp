// command_parser.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/infrastructure/parsers/command_parser.hpp"

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

CommandInfo CommandParser::parse(const std::string& command) 
{
    CommandInfo info;
    info.setBaseCommand(getBaseCommand(command));
    info.setArgs(parseArguments(command));
    info.setSpeedOverride(extractSpeedOverride(info.getArgs(), getBaseCommand(command)));
    return info;
}

std::string CommandParser::getBaseCommand(const std::string& command) 
{
    auto [base_command, _] = getNextValue(command, 0);
    return base_command;
}

std::vector<std::string> CommandParser::parseArguments(const std::string& command) 
{
    std::vector<std::string> args;
    size_t pos = command.find(':');
    
    if (pos != std::string::npos) {
        pos++; 
        while (pos < command.length()) {
            auto [arg, next_pos] = getNextValue(command, pos);
            if (!arg.empty()) {
                args.push_back(arg);
            }
            pos = next_pos;
        }
    }
    return args;
}

std::pair<std::string, size_t> CommandParser::getNextValue(const std::string& command, size_t pos)
{
    const size_t next = command.find(':', pos);
    size_t next_pos = next + 1;
    
    if (next == std::string::npos) {
        next_pos = command.length();
    }
    
    return {command.substr(pos, next - pos), next_pos};
}

CommandParser::SpeedOverrideOpt CommandParser::extractSpeedOverride(
    const std::vector<std::string>& args,
    const std::string& baseCommand) 
{
    auto config = findConfigForCommand(baseCommand);
    if (!config) return std::nullopt;

    size_t expected_args = config->getBaseArgumentCount();
    if (args.size() != expected_args + 2) return std::nullopt;

    try {
        double v = std::stod(args[expected_args]);
        double a = std::stod(args[expected_args + 1]);
        if (v > 0 && v <= 1 && a > 0 && a <= 1) {
            return std::make_pair(v, a);
        }
    } catch (...) {}
    return std::nullopt;
}

const CommandConfig* CommandParser::findConfigForCommand(const std::string& command) 
{
    for (const auto& config : configs_) {
        if (std::find(config->getArgumentNames().begin(),
                      config->getArgumentNames().end(),
                      command) != config->getArgumentNames().end()) {
            return config.get();
        }
    }
    return nullptr;
}