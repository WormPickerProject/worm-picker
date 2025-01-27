// command_config.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/core/commands/command_config.hpp"

VariableArgConfig::VariableArgConfig(const NodePtr& node, const std::string& param_key)
{
    if (auto names = param_utils::getParameter<StringVec>(node, param_key)) {
        argument_names_ = std::move(names.value());
        RCLCPP_INFO(rclcpp::get_logger("VariableArgConfig"), "Variable-arg commands loaded: %s",
            fmt::format("{}", fmt::join(argument_names_, ", ")).c_str());
        return;
    }
    RCLCPP_WARN(rclcpp::get_logger("VariableArgConfig"),
        "No commands found for key '%s'", param_key.c_str());
}

CommandConfig::StringVec VariableArgConfig::getArgumentNames() const
{
    return argument_names_;
}

size_t VariableArgConfig::getBaseArgumentCount() const
{
    return base_argument_count_;
}

bool VariableArgConfig::validateArgs(const StringVec& args) const
{
    return (args.size() == base_argument_count_ || args.size() == base_argument_count_ + 2);
}

void VariableArgConfig::setDynamicMultiplier(size_t n, size_t base)
{
    base_argument_count_ = n * base;
}