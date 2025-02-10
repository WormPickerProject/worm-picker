// command_info.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <fmt/format.h>
#include "worm_picker_core/core/commands/command_info.hpp"

CommandInfo::CommandInfo(const std::string& base_command, 
                         const std::vector<std::string>& arguments,
                         const SpeedOverrideOpt& speed_override)
    : base_command_(base_command), 
      args_(arguments), 
      speed_override_(speed_override) {}

const std::string& CommandInfo::getBaseCommandKey() const 
{
    if (!cached_key_.empty()) {
        return cached_key_;
    }

    const std::size_t actual_arg_count = std::min(base_args_amount_, args_.size());
    if (actual_arg_count == 0) {
        cached_key_ = base_command_;
        return cached_key_;
    }

    const auto first = args_.begin();
    const auto last  = args_.begin() + actual_arg_count;
    const std::string joined_args = fmt::format("{}", fmt::join(first, last, ":"));

    cached_key_ = fmt::format("{}:{}", base_command_, joined_args);
    return cached_key_;
}

const std::string& CommandInfo::getBaseCommand() const 
{ 
    return base_command_; 
}

const std::vector<std::string>& CommandInfo::getArgs() const 
{ 
    return args_; 
}

const CommandInfo::SpeedOverrideOpt& CommandInfo::getSpeedOverride() const 
{ 
    return speed_override_; 
}

const size_t CommandInfo::getBaseArgsAmount() const 
{ 
    return base_args_amount_; 
}

void CommandInfo::setBaseCommand(const std::string& command) 
{ 
    base_command_ = command; 
}

void CommandInfo::setArgs(const std::vector<std::string>& args) 
{ 
    args_ = args; 
}

void CommandInfo::setSpeedOverride(const SpeedOverrideOpt& override) 
{ 
    speed_override_ = override; 
}

void CommandInfo::setBaseArgsAmount(size_t amount) 
{ 
    base_args_amount_ = amount; 
}