// command_config.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <fmt/format.h>
#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/utils/parameter_utils.hpp"

class CommandConfig {
public:
    using NodePtr   = rclcpp::Node::SharedPtr;
    using StringVec = std::vector<std::string>;

    virtual ~CommandConfig() = default;
    virtual StringVec getArgumentNames() const = 0;
    virtual size_t getBaseArgumentCount() const = 0;
    virtual bool validateArgs(const StringVec& args) const = 0;
    virtual void setDynamicMultiplier(size_t /*n*/, size_t /*base*/) {}
};

template <std::size_t N>
struct ConfigTraits;

template <>
struct ConfigTraits<0> {
    inline static constexpr char param_key[] = "commands.zero_arg";
};

template <>
struct ConfigTraits<1> {
    inline static constexpr char param_key[] = "commands.one_arg";
};

template <>
struct ConfigTraits<3> {
    inline static constexpr char param_key[] = "commands.three_arg";
};

template <std::size_t BaseArgCount>
class FixedArgsConfig : public CommandConfig {
public:
    using NodePtr   = typename CommandConfig::NodePtr;
    using StringVec = typename CommandConfig::StringVec;

    explicit FixedArgsConfig(const NodePtr& node) {
        constexpr const char* param_key = ConfigTraits<BaseArgCount>::param_key;

        if (auto names = param_utils::getParameter<StringVec>(node, param_key)) {
            argument_names_ = std::move(names.value());
            RCLCPP_INFO(rclcpp::get_logger("FixedArgsConfig"), "%zu-arg commands loaded: %s", 
                BaseArgCount, fmt::format("{}", fmt::join(argument_names_, ", ")).c_str());
            return;
        }
        RCLCPP_WARN(rclcpp::get_logger("FixedArgsConfig"), 
            "No commands found for key '%s'", param_key);
    }

    StringVec getArgumentNames() const override {
        return argument_names_;
    }

    size_t getBaseArgumentCount() const override {
        return BaseArgCount;
    }

    bool validateArgs(const StringVec& args) const override {
        return (args.size() == BaseArgCount || args.size() == BaseArgCount + 2);
    }

private:
    StringVec argument_names_;
};

using ZeroArgConfig = FixedArgsConfig<0>;
using OneArgConfig   = FixedArgsConfig<1>;
using ThreeArgConfig = FixedArgsConfig<3>;

class VariableArgConfig : public CommandConfig {
public:
    explicit VariableArgConfig() = default;
    explicit VariableArgConfig(const NodePtr& node, 
                               const std::string& param_key = "commands.variable_arg");
    StringVec getArgumentNames() const override;
    size_t getBaseArgumentCount() const override;
    bool validateArgs(const StringVec& args) const override;
    void setDynamicMultiplier(size_t n, size_t base) override;

private:
    StringVec argument_names_;
    size_t base_argument_count_{0};
};
