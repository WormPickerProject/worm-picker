// command_parser.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/infrastructure/parsers/command_parser.hpp"
#include <fmt/format.h>

CommandParser::CommandParser(const NodePtr& node) 
{
    initCommandParser(node);
    buildCommandMap();
}

void CommandParser::initCommandParser(const NodePtr& node) 
{
    configs_ = {
        std::make_shared<VariableArgConfig>(node),
        std::make_shared<ZeroArgConfig>(node),
        std::make_shared<OneArgConfig>(node),
        std::make_shared<ThreeArgConfig>(node)
    };
}

void CommandParser::buildCommandMap() 
{
    for (const auto& config : configs_) {
        for (const auto& name : config->getArgumentNames()) {
            command_map_.try_emplace(name, config);
        }
    }
}

Result<CommandInfo> CommandParser::parse(const std::string& command)
{
    ParseContext ctx;
    
    try {
        ctx.tokens = tokenizeByColon(command);
        if (ctx.tokens.empty()) {
            return Result<CommandInfo>::error(
                fmt::format("Command '{}' is empty or invalid", command));
        }

        ctx.base_command = ctx.tokens.front();
        if (ctx.tokens.size() > 1) {
            ctx.args.assign(ctx.tokens.begin() + 1, ctx.tokens.end());
        }

        const CommandConfig* config = findConfigForCommand(ctx);
        if (!config) {
            return Result<CommandInfo>::error(
                fmt::format("No CommandConfig found for base command '{}'", ctx.base_command));
        }

        return createCommandInfo(ctx, config);
    }
    catch (const std::exception& e) {
        return Result<CommandInfo>::error(
            fmt::format("Failed to parse command: {}", e.what()));
    }
}

const CommandConfig* CommandParser::findConfigForCommand(ParseContext& ctx) const 
{
    auto it = command_map_.find(ctx.base_command);
    if (it == command_map_.end()) {
        RCLCPP_WARN(logger_, "No config found for command: %s", ctx.base_command.c_str());
        return nullptr;
    }

    if (dynamic_cast<VariableArgConfig*>(it->second.get())) {
        return handleVariableConfig(ctx);
    }

    return it->second.get();
}

const CommandConfig* CommandParser::handleVariableConfig(ParseContext& ctx) const 
{
    if (ctx.args.empty()) {
        RCLCPP_WARN(logger_, "No arguments provided for variable command: %s",
            ctx.base_command.c_str());
        return nullptr;
    }

    const CommandConfig* base_config = nullptr;
    size_t base_count = 0;

    for (auto it = std::next(configs_.begin()); it != configs_.end(); ++it) {
        const auto& config = *it;
        const auto& names = config->getArgumentNames();
        if (std::find(names.begin(), names.end(), ctx.base_command) != names.end()) {
            base_config = config.get();
            base_count = config->getBaseArgumentCount();
            break;
        }
    }

    if (!base_config) {
        RCLCPP_WARN(logger_, "No base config found for variable command: %s",
            ctx.base_command.c_str());
        return nullptr;
    }

    auto N_opt = extractMovementCount(ctx.args[0]);
    if (!N_opt) {
        return base_config;
    }

    ctx.args.erase(ctx.args.begin());
    ctx.var_config = std::make_unique<VariableArgConfig>();
    ctx.var_config->setDynamicMultiplier(*N_opt, base_count);
    return ctx.var_config.get();
}

std::optional<size_t> CommandParser::extractMovementCount(const std::string& token) const 
{
    if (!token.starts_with("N=")) {
        RCLCPP_DEBUG(logger_, "Token '%s' doesn't start with N=", token.c_str());
        return std::nullopt;
    }
    
    try {
        size_t N = std::stoul(token.substr(2));
        if (N == 0) {
            RCLCPP_WARN(logger_, "Invalid N value: cannot be zero");
            return std::nullopt;
        }
        return N;
    } 
    catch (const std::exception& e) {
        RCLCPP_WARN(logger_, "Failed to parse N value from '%s': %s", 
            token.c_str(), e.what());
        return std::nullopt;
    }
}

CommandParser::StringVec CommandParser::tokenizeByColon(const std::string& str) 
{
    StringVec tokens;
    size_t start = 0;

    while (true) {
        size_t pos = str.find(':', start);
        if (pos == std::string::npos) {
            tokens.push_back(str.substr(start));
            break;
        }
        tokens.push_back(str.substr(start, pos - start));
        start = pos + 1;
    }
    
    return tokens;
}

CommandParser::SpeedOverrideOpt CommandParser::extractSpeedOverride(
    const StringVec& args,
    const CommandConfig* config) const 
{
    const size_t expected_base_args = config->getBaseArgumentCount();
    if (args.size() != expected_base_args + 2) {
        RCLCPP_DEBUG(logger_, "Not extracting speed override; arg count is %zu, expected %zu + 2",
            args.size(), expected_base_args);
        return std::nullopt;
    }

    try {
        double v = std::stod(args[expected_base_args]);
        double a = std::stod(args[expected_base_args + 1]);

        if (v > 0 && v <= 1 && a > 0 && a <= 1) {
            RCLCPP_INFO(logger_, "Parsed speed override -> Speed: %f; Accel: %f", v, a);
            return std::make_pair(v, a);
        }
        
        RCLCPP_WARN(logger_, "Speed override values out of range (0,1]: v=%f, a=%f", v, a);
    } 
    catch (const std::exception& e) {
        RCLCPP_WARN(logger_, "Failed parsing speed override: %s", e.what());
    }
    
    return std::nullopt;
}

Result<CommandInfo> CommandParser::createCommandInfo(
    ParseContext& ctx,
    const CommandConfig* config) const 
{
    if (!config->validateArgs(ctx.args)) {
        return Result<CommandInfo>::error(
            fmt::format("Invalid arguments for command '{}'", ctx.base_command));
    }

    CommandInfo info;
    info.setBaseCommand(ctx.base_command);
    info.setBaseArgsAmount(config->getBaseArgumentCount());
    info.setArgs(ctx.args);
    info.setSpeedOverride(extractSpeedOverride(ctx.args, config));

    return Result<CommandInfo>::success(info);
}