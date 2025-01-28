// command_parser.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/infrastructure/parsers/command_parser.hpp"
#include <fmt/format.h>
#include <ranges>

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
    const auto it = command_map_.find(ctx.base_command);
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

    const auto base_config = findBaseConfigForVariableCommand(ctx.base_command);
    if (!base_config.has_value()) {
        RCLCPP_WARN(logger_, "No base config found for variable command: %s",
                    ctx.base_command.c_str());
        return nullptr;
    }

    const auto movement_sets = extractMovementCount(ctx.args.front());
    return movement_sets.has_value()
        ? [&]() -> const CommandConfig* {
            ctx.var_config = createVariableConfig(*movement_sets, base_config->second);
            ctx.args.erase(ctx.args.begin());
            return ctx.var_config.get();
          }()
        : base_config->first;
}

CommandParser::BaseConfigOptPair
CommandParser::findBaseConfigForVariableCommand(const std::string& base_command) const
{
    auto config_range = configs_ 
        | std::ranges::views::drop(1)
        | std::ranges::views::transform([](const auto& cfg) {
            return std::make_pair(cfg.get(), cfg->getBaseArgumentCount());
        })
        | std::ranges::views::filter([&base_command](const auto& pair) {
            const auto& [cfg, count] = pair;
            const auto& names = cfg->getArgumentNames();
            return std::ranges::find(names, base_command) != std::ranges::end(names);
        });

    auto it = std::ranges::begin(config_range);
    return it != std::ranges::end(config_range) 
        ? std::make_optional(*it)
        : std::nullopt;
}

std::optional<std::size_t> CommandParser::extractMovementCount(const std::string& token) const 
{
    static constexpr std::string_view prefix{"N="};
    if (!token.starts_with(prefix)) {
        RCLCPP_WARN(logger_, "Token '%.*s' doesn't start with N=",
                    static_cast<int>(token.size()), token.data());
        return std::nullopt;
    }
    
    const std::string numeric_str(token.substr(prefix.size()));
    try {
        const std::size_t count = std::stoul(numeric_str);
        return count > 0 ? std::make_optional(count) : std::nullopt;
    } catch (const std::exception& e) {
        RCLCPP_WARN(logger_, "N= parsing failed: %s", e.what());
        return std::nullopt;
    }
}

std::unique_ptr<VariableArgConfig> CommandParser::createVariableConfig(
    std::size_t N, std::size_t base_count) const 
{
    VariableArgConfig config;
    config.setDynamicMultiplier(N, base_count);
    return std::make_unique<VariableArgConfig>(config);
}

CommandParser::StringVec CommandParser::tokenizeByColon(const std::string& input) 
{
    StringVec tokens;
    std::size_t start = 0;
    while (true) {
        const std::size_t colon_pos = input.find(':', start);
        if (colon_pos == std::string_view::npos) {
            tokens.emplace_back(input.substr(start));
            break;
        }
        tokens.emplace_back(input.substr(start, colon_pos - start));
        start = colon_pos + 1;
    }
    return tokens;
}

CommandParser::SpeedOverrideOpt 
CommandParser::extractSpeedOverride(const StringVec& args,
                                    const CommandConfig* config) const 
{
    const auto base = config->getBaseArgumentCount();
    const auto checkArgCount = [&args, base, this]() -> bool {
        if (args.size() != (base + 2)) {
            RCLCPP_WARN(logger_, 
                        "Not extracting speed override; arg count is %zu, expected %zu + 2",
                        args.size(), base);
            return false;
        }
        return true;
    };

    const auto parseValues = [&args, base, this]() -> std::optional<std::pair<double, double>> {
        try {
            return std::make_pair(std::stod(args[base]), std::stod(args[base + 1]));
        } catch (const std::exception& e) {
            RCLCPP_WARN(logger_, "Failed parsing speed override: %s", e.what());
            return std::nullopt;
        }
    };

    const auto validateRange = [this](const std::pair<double, double>& values) -> bool {
        const auto& [speed, accel] = values;
        const bool is_valid = (speed > 0.0 && speed <= 1.0) && (accel > 0.0 && accel <= 1.0);
        if (!is_valid) {
            RCLCPP_WARN(logger_, "Speed override values out of range (0,1]: speed=%f, accel=%f", 
                        speed, accel);
            return false;
        }
        RCLCPP_INFO(logger_, "Parsed speed override -> Speed: %f; Accel: %f", speed, accel);
        return true;
    };

    if (!checkArgCount()) {
        return std::nullopt;
    }

    if (auto values = parseValues()) {
        return validateRange(*values) ? values : std::nullopt;
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