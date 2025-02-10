// command_info.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>
#include <vector>
#include <optional>

class CommandInfo {
public:
    using SpeedOverrideOpt = std::optional<std::pair<double, double>>;

    CommandInfo() = default;
    CommandInfo(const std::string& base_command, 
                const std::vector<std::string>& arguments,
                const SpeedOverrideOpt& speed_override = std::nullopt);

    const std::string& getBaseCommand() const;
    const std::vector<std::string>& getArgs() const;
    const SpeedOverrideOpt& getSpeedOverride() const;
    const std::string& getBaseCommandKey() const;
    const size_t getBaseArgsAmount() const;
    
    void setBaseCommand(const std::string& command);
    void setArgs(const std::vector<std::string>& args);
    void setSpeedOverride(const SpeedOverrideOpt& override);
    void setBaseArgsAmount(size_t amount);

private:
    mutable std::string cached_key_{};
    std::string base_command_{};
    std::vector<std::string> args_{};
    SpeedOverrideOpt speed_override_{};
    size_t base_args_amount_{0};
};