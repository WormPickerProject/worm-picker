// command_config.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef COMMAND_CONFIG_HPP
#define COMMAND_CONFIG_HPP

#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/utils/parameter_utils.hpp"

class CommandConfig {
public:
    using NodePtr = rclcpp::Node::SharedPtr;
    using StringVec = std::vector<std::string>;

    virtual ~CommandConfig() = default;
    virtual StringVec getArgumentNames() const = 0;
    virtual size_t getBaseArgumentCount() const = 0;
};

class ZeroArgsConfig final : public CommandConfig {
public:
    explicit ZeroArgsConfig() = default;
    explicit ZeroArgsConfig(const NodePtr& node) {
        if (auto names = param_utils::getParameter<StringVec>(node, "commands.zero_arg")) {
            argument_names_ = std::move(names.value());
        }
    }
    StringVec getArgumentNames() const override {
        return argument_names_;
    }
    size_t getBaseArgumentCount() const override {
        return 0;
    }

private:
    StringVec argument_names_{};
};

class OneArgConfig final : public CommandConfig {
public:
    explicit OneArgConfig() = default;
    explicit OneArgConfig(const NodePtr& node) {
        if (auto names = param_utils::getParameter<StringVec>(node, "commands.one_arg")) {
            argument_names_ = std::move(names.value());
        }
    }
    StringVec getArgumentNames() const override {
        return argument_names_;
    }
    size_t getBaseArgumentCount() const override {
        return 1;
    }

private:
    StringVec argument_names_{};
};

class ThreeArgsConfig final : public CommandConfig {
public:
    explicit ThreeArgsConfig() = default;
    explicit ThreeArgsConfig(const NodePtr& node) {
        if (auto names = param_utils::getParameter<StringVec>(node, "commands.three_arg")) {
            argument_names_ = std::move(names.value());
        }
    }
    StringVec getArgumentNames() const override {
        return argument_names_;
    }
    size_t getBaseArgumentCount() const override {
        return 3;
    }

private:
    StringVec argument_names_{};
};

#endif // COMMAND_CONFIG_HPP