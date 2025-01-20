// command_config.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

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
    explicit ZeroArgsConfig(const NodePtr& node);
    StringVec getArgumentNames() const override;
    size_t getBaseArgumentCount() const override;

private:
    StringVec argument_names_{};
};

class OneArgConfig final : public CommandConfig {
public:
    explicit OneArgConfig() = default;
    explicit OneArgConfig(const NodePtr& node);
    StringVec getArgumentNames() const override;
    size_t getBaseArgumentCount() const override;

private:
    StringVec argument_names_{};
};

class ThreeArgsConfig final : public CommandConfig {
public:
    explicit ThreeArgsConfig() = default;
    explicit ThreeArgsConfig(const NodePtr& node);
    StringVec getArgumentNames() const override;
    size_t getBaseArgumentCount() const override;

private:
    StringVec argument_names_{};
};