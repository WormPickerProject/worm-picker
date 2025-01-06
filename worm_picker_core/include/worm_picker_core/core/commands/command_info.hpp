// command_info.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef COMMAND_INFO_HPP
#define COMMAND_INFO_HPP

#include <string>
#include <vector>
#include <optional>

class CommandInfo {
public:
    using SpeedOverrideOpt = std::optional<std::pair<double, double>>;

    CommandInfo() = default;
    CommandInfo(const std::string& base_command, 
                const std::vector<std::string>& arguments,
                const SpeedOverrideOpt& speed_override = std::nullopt)
        : base_command_(base_command), 
          args_(arguments), 
          speed_override_(speed_override) {}

    const std::string& getBaseCommand() const { return base_command_; }
    const std::vector<std::string>& getArgs() const { return args_; }
    const SpeedOverrideOpt& getSpeedOverride() const { return speed_override_; }
    void setBaseCommand(const std::string& command) { base_command_ = command; }
    void setArgs(const std::vector<std::string>& args) { args_ = args; }
    void setSpeedOverride(const SpeedOverrideOpt& override) { speed_override_ = override; }

private:
    std::string base_command_{};
    std::vector<std::string> args_{};
    SpeedOverrideOpt speed_override_{};
};

#endif // COMMAND_INFO_HPP