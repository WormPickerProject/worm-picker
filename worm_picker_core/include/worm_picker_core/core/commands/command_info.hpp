// command_info.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef COMMAND_INFO_HPP
#define COMMAND_INFO_HPP

#include <string>
#include <vector>
#include <optional>
#include <fmt/format.h>

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
    const std::string& getBaseCommandKey() const;
    void setBaseCommand(const std::string& command) { base_command_ = command; }
    void setArgs(const std::vector<std::string>& args) { args_ = args; }
    void setSpeedOverride(const SpeedOverrideOpt& override) { speed_override_ = override; }
    void setBaseArgsAmount(size_t amount) { base_args_amount_ = amount; }

private:
    mutable std::string cached_key_{};
    std::string base_command_{};
    std::vector<std::string> args_{};
    SpeedOverrideOpt speed_override_{};
    size_t base_args_amount_{0};
};

inline const std::string& CommandInfo::getBaseCommandKey() const 
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

#endif // COMMAND_INFO_HPP