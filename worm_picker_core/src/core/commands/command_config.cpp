// command_config.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <fmt/format.h>
#include "worm_picker_core/core/commands/command_config.hpp"

ZeroArgsConfig::ZeroArgsConfig(const NodePtr& node)
{
    if (auto names = param_utils::getParameter<StringVec>(node, "commands.zero_arg")) {
        argument_names_ = std::move(names.value());
        RCLCPP_INFO(rclcpp::get_logger("ZeroArgsConfig"), 
            "Zero-arg commands loaded with %lu commands: %s", 
            argument_names_.size(), fmt::format("{}", 
            fmt::join(argument_names_, ", ")).c_str());
    }
}

CommandConfig::StringVec ZeroArgsConfig::getArgumentNames() const
{
    return argument_names_;
}

size_t ZeroArgsConfig::getBaseArgumentCount() const
{
    return 0;
}

OneArgConfig::OneArgConfig(const NodePtr& node)
{
    if (auto names = param_utils::getParameter<StringVec>(node, "commands.one_arg")) {
        argument_names_ = std::move(names.value());
        RCLCPP_INFO(rclcpp::get_logger("OneArgConfig"), 
            "One-arg commands loaded with %lu commands: %s", 
            argument_names_.size(), fmt::format("{}", 
            fmt::join(argument_names_, ", ")).c_str());
    }
}

CommandConfig::StringVec OneArgConfig::getArgumentNames() const
{
    return argument_names_;
}

size_t OneArgConfig::getBaseArgumentCount() const
{
    return 1;
}

ThreeArgsConfig::ThreeArgsConfig(const NodePtr& node)
{
    if (auto names = param_utils::getParameter<StringVec>(node, "commands.three_arg")) {
        argument_names_ = std::move(names.value());
        RCLCPP_INFO(rclcpp::get_logger("ThreeArgsConfig"), 
            "Three-arg commands loaded with %lu commands: %s", 
            argument_names_.size(), fmt::format("{}", 
            fmt::join(argument_names_, ", ")).c_str());
    }
}

CommandConfig::StringVec ThreeArgsConfig::getArgumentNames() const
{
    return argument_names_;
}

size_t ThreeArgsConfig::getBaseArgumentCount() const
{
    return 3;
}