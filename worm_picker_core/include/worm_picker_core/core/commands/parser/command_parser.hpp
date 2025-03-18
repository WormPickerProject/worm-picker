// command_parser.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/core/commands/parser/parser_core.hpp"
#include "worm_picker_core/core/commands/command_info.hpp"

namespace worm_picker {
namespace parser {

//----------------------------------------
// Command-Specific Types
//----------------------------------------
struct VariableArgResult {
    size_t multiplier;
    std::vector<std::string> remaining_args;
};

struct SpeedOverride {
    double velocity;
    double acceleration;
};

//----------------------------------------
// Command Registry
//----------------------------------------
class CommandRegistry {
public:
    CommandRegistry() = default;

    void loadFromNode(const rclcpp::Node::SharedPtr& node);
    bool hasCommand(const std::string& command) const;
    size_t getBaseArgCount(const std::string& command) const;
    bool isVariable(const std::string& command) const;
    size_t getVariableBaseCount(const std::string& command) const;
    std::vector<std::string> getAllCommands() const;
    void registerCommand(const std::string& command, size_t base_arg_count,
                         bool is_variable = false, size_t variable_base_count = 0);
    
private:
    void loadCommandsFromParameter(const rclcpp::Node::SharedPtr& node, 
                                   const std::string& param_name,
                                   size_t base_arg_count);

    std::unordered_map<std::string, size_t> command_to_base_arg_count_;
    std::unordered_map<std::string, bool> is_variable_command_;
    std::unordered_map<std::string, size_t> variable_command_base_count_;
};

//----------------------------------------
// Helper and Basic Parsers
//----------------------------------------
Parser<std::string> baseCommandParser();
Parser<std::vector<std::string>> argumentsParser();
Parser<std::string> parseCommandName(const std::string& expected_command);
Parser<ParserInput> parseColon();
Parser<ParserInput> parseOptionalColon();
bool validateArguments(const std::vector<std::string>& args,
                       size_t expected_count,
                       const ParserInput& input,
                       const std::string& command_name,
                       std::string& error_msg);
std::optional<SpeedOverride> parseSpeedOverrideFromArgs(const std::vector<std::string>& args,
                                                        size_t base_arg_count);
CommandInfo buildCommandInfo(const std::string& command_name, 
                             size_t base_arg_count, 
                             const std::vector<std::string>& args = {});

//----------------------------------------
// Command Parsers
//----------------------------------------
Parser<CommandInfo> commandParser(const std::string& command_name, size_t base_arg_count);
Parser<CommandInfo> variableCommandParser(const std::string& command_name, size_t base_arg_group);

//----------------------------------------
// Command Builder Helper
//----------------------------------------
class CommandBuilder {
public:
    static std::vector<Parser<CommandInfo>> createCommandParsers(const CommandRegistry& registry);
    static Parser<CommandInfo> createMainParser(const CommandRegistry& registry);
};

} // namespace parser
} // namespace worm_picker