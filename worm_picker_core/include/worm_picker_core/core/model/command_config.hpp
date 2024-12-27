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
    virtual ~CommandConfig() = default;
    virtual std::vector<std::string> getArgumentNames() const = 0;
    virtual size_t getBaseArgumentCount() const = 0;
};

class ZeroArgsConfig : public CommandConfig {
public:
    explicit ZeroArgsConfig() = default;
    explicit ZeroArgsConfig(const rclcpp::Node::SharedPtr& node) { 
        auto names = param_utils::getParameter<std::vector<std::string>>(
            node, "commands.zero_arg");
        argument_names_ = names.value();
    }
    std::vector<std::string> getArgumentNames() const override { 
        return argument_names_;
    }
    size_t getBaseArgumentCount() const override { return 0; }

private:
    std::vector<std::string> argument_names_;
};

class OneArgConfig : public CommandConfig {
public:
    explicit OneArgConfig() = default;
    explicit OneArgConfig(const rclcpp::Node::SharedPtr& node) { 
        auto names = param_utils::getParameter<std::vector<std::string>>(
            node, "commands.one_arg");
        argument_names_ = names.value();
    }
    std::vector<std::string> getArgumentNames() const override { 
        return argument_names_;
    }
    size_t getBaseArgumentCount() const override { return 1; }

private:
    std::vector<std::string> argument_names_;
};

class ThreeArgsConfig : public CommandConfig {
public:
    explicit ThreeArgsConfig() = default;
    explicit ThreeArgsConfig(const rclcpp::Node::SharedPtr& node) { 
        auto names = param_utils::getParameter<std::vector<std::string>>(
            node, "commands.three_arg");
        argument_names_ = names.value();
    }
    std::vector<std::string> getArgumentNames() const override { 
        return argument_names_;
    }
    size_t getBaseArgumentCount() const override { return 3; }

private:
    std::vector<std::string> argument_names_;
};

#endif // COMMAND_CONFIG_HPP