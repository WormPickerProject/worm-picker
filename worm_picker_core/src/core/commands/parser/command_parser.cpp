// command_parser.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <regex>
#include "worm_picker_core/core/commands/parser/command_parser.hpp"

namespace worm_picker {
namespace parser {

//----------------------------------------
// CommandRegistry Implementation
//----------------------------------------
void CommandRegistry::loadFromNode(const rclcpp::Node::SharedPtr& node)
{
    loadCommandsFromParameter(node, "commands.zero_arg", 0);
    loadCommandsFromParameter(node, "commands.one_arg", 1);
    loadCommandsFromParameter(node, "commands.two_arg", 2);
    loadCommandsFromParameter(node, "commands.three_arg", 3);
    loadCommandsFromParameter(node, "commands.four_arg", 4);
    loadCommandsFromParameter(node, "commands.eight_arg", 8);

    auto variable_commands = param_utils::getParameter<std::vector<std::string>>(
        node, "commands.variable_arg");
    if (variable_commands) {
        for (const auto& command : variable_commands.value()) {
            auto base_arg = getBaseArgCount(command);
            if (base_arg > 0) {
                registerCommand(command, base_arg, true, base_arg);
            }
        }
    }
}

bool CommandRegistry::hasCommand(const std::string& command) const
{
    return command_to_base_arg_count_.find(command) != command_to_base_arg_count_.end();
}

size_t CommandRegistry::getBaseArgCount(const std::string& command) const
{
    auto it = command_to_base_arg_count_.find(command);
    return (it != command_to_base_arg_count_.end()) ? it->second : 0;
}

bool CommandRegistry::isVariable(const std::string& command) const
{
    auto it = is_variable_command_.find(command);
    return (it != is_variable_command_.end()) ? it->second : false;
}

size_t CommandRegistry::getVariableBaseCount(const std::string& command) const
{
    auto it = variable_command_base_count_.find(command);
    return (it != variable_command_base_count_.end()) ? it->second : 0;
}

std::vector<std::string> CommandRegistry::getAllCommands() const
{
    std::vector<std::string> result;
    result.reserve(command_to_base_arg_count_.size());
    for (const auto& pair : command_to_base_arg_count_) {
        result.push_back(pair.first);
    }
    return result;
}

void CommandRegistry::registerCommand(const std::string& command,
                                      size_t base_arg_count,
                                      bool is_variable,
                                      size_t variable_base_count)
{
    command_to_base_arg_count_[command] = base_arg_count;
    if (is_variable) {
        is_variable_command_[command] = true;
        variable_command_base_count_[command] = variable_base_count;
    }
}

void CommandRegistry::loadCommandsFromParameter(const rclcpp::Node::SharedPtr& node,
                                                  const std::string& param_name,
                                                  size_t base_arg_count)
{
    auto commands = param_utils::getParameter<std::vector<std::string>>(node, param_name);
    if (commands) {
        for (const auto& command : commands.value()) {
            registerCommand(command, base_arg_count);
            RCLCPP_INFO(node->get_logger(), 
                "Registered %zu-arg command: %s", base_arg_count, command.c_str());
        }
    }
}

//----------------------------------------
// Basic Parsers and Helpers
//----------------------------------------
Parser<std::string> baseCommandParser() 
{
    return token(':');
}

Parser<std::vector<std::string>> argumentsParser() 
{
    auto colon_parser = character(':');
    return sepBy(token(':'), colon_parser);
}

Parser<std::string> parseCommandName(const std::string& expected_command) 
{
    return [expected_command](ParserInput input) -> ParserResult<std::string> {
        auto command_result = baseCommandParser()(input);
        if (!command_result.isSuccess()) {
            return ParserResult<std::string>::error(command_result.error());
        }
        auto [actual_command, after_command] = command_result.value();
        if (actual_command != expected_command) {
            return ParserResult<std::string>::error(
                "At " + input.positionInfo() + ": Expected command '" + expected_command +
                "', got '" + actual_command + "'");
        }
        return ParserResult<std::string>::success({actual_command, after_command});
    };
}

Parser<ParserInput> parseColon() 
{
    return [](ParserInput input) -> ParserResult<ParserInput> {
        if (input.atEnd() || input.current() != ':') {
            return ParserResult<ParserInput>::error(
                "At " + input.positionInfo() + ": Expected ':' after command name");
        }
        return ParserResult<ParserInput>::success({input.advance(), input.advance()});
    };
}

Parser<ParserInput> parseOptionalColon() 
{
    return [](ParserInput input) -> ParserResult<ParserInput> {
        if (input.atEnd() || input.current() != ':') {
            return ParserResult<ParserInput>::success({input, input});
        }
        return ParserResult<ParserInput>::success({input.advance(), input.advance()});
    };
}

bool validateArguments(const std::vector<std::string>& args,
                       size_t expected_count,
                       const ParserInput& input,
                       const std::string& command_name,
                       std::string& error_msg) 
{
    if (args.size() != expected_count && args.size() != expected_count + 2) {
        std::ostringstream oss;
        oss << "At " << input.positionInfo() << ": Expected " << expected_count 
            << " arguments for command '" << command_name << "', got " << args.size();
        error_msg = oss.str();
        return false;
    }
    return true;
}

std::optional<SpeedOverride> parseSpeedOverrideFromArgs(const std::vector<std::string>& args,
                                                        size_t base_arg_count) 
{
    if (args.size() != base_arg_count + 2) {
        return std::nullopt;
    }
    
    try {
        size_t idx = args.size() - 2;
        double velocity = std::stod(args[idx]);
        double acceleration = std::stod(args[idx + 1]);
        if (velocity <= 0 || velocity > 1 || acceleration <= 0 || acceleration > 1) {
            return std::nullopt;
        }
        return SpeedOverride{velocity, acceleration};
    } catch (...) {
        return std::nullopt;
    }
}

CommandInfo buildCommandInfo(const std::string& command_name, 
                             size_t base_arg_count, 
                             const std::vector<std::string>& args) 
{
    CommandInfo info;
    info.setBaseCommand(command_name);
    info.setBaseArgsAmount(base_arg_count);
    info.setArgs(args);
    return info;
}

//----------------------------------------
// Variable Argument Parsing Helper
//----------------------------------------
static Parser<VariableArgResult> variableArgParser() 
{
    return [](ParserInput input) -> ParserResult<VariableArgResult> {
        static const std::regex n_pattern(R"(N=(\d+))");

        if (input.atEnd()) {
            return ParserResult<VariableArgResult>::error(
                "At " + input.positionInfo() + ": Unexpected end of input");
        }

        std::string input_str(input.remainder());
        std::smatch match;

        if (!std::regex_search(input_str, match, n_pattern)) {
            return ParserResult<VariableArgResult>::error(
                "At " + input.positionInfo() + ": Expected 'N=' prefix");
        }

        int multiplier = std::stoi(match[1]);
        if (multiplier <= 0) {
            return ParserResult<VariableArgResult>::error(
                "At " + input.positionInfo() + ": Invalid multiplier: must be positive");
        }

        size_t n_length = match[0].length();
        ParserInput after_n = input.advance(n_length);
        if (after_n.atEnd() || after_n.current() != ':') {
            return ParserResult<VariableArgResult>::error(
                "At " + input.positionInfo() + ": Expected ':' after N= token");
        }

        auto args_result = argumentsParser()(after_n.advance());
        if (!args_result.isSuccess()) {
            return ParserResult<VariableArgResult>::error(args_result.error());
        }
        auto [args, next_input] = args_result.value();
        return ParserResult<VariableArgResult>::success(
            {{static_cast<size_t>(multiplier), args}, next_input});
    };
}

//----------------------------------------
// Command Parsers
//----------------------------------------
Parser<CommandInfo> commandParser(const std::string& command_name, size_t base_arg_count) 
{
    return [command_name, base_arg_count](ParserInput input) -> ParserResult<CommandInfo> {
        auto commandChain = combine(
            parseCommandName(command_name),
            orElse(parseColon(), parseOptionalColon()),
            [](std::string, ParserInput after_colon) { return after_colon; }
        );

        auto name_parse_result = commandChain(input);
        if (!name_parse_result.isSuccess()) {
            return ParserResult<CommandInfo>::error(name_parse_result.error());
        }
        auto [after_colon, _] = name_parse_result.value();

        // Handle commands with no arguments
        if (base_arg_count == 0 && after_colon.atEnd()) {
            return ParserResult<CommandInfo>::success(
                {buildCommandInfo(command_name, 0), after_colon});
        }

        auto args_result = argumentsParser()(after_colon);
        if (!args_result.isSuccess()) {
            return ParserResult<CommandInfo>::error(args_result.error());
        }

        auto [args, rest] = args_result.value();

        std::string error_msg;
        if (!validateArguments(args, base_arg_count, after_colon, command_name, error_msg)) {
            return ParserResult<CommandInfo>::error(error_msg);
        }

        CommandInfo info = buildCommandInfo(command_name, base_arg_count, args);
                
        auto speed_override = parseSpeedOverrideFromArgs(args, base_arg_count);
        if (speed_override) {
            info.setSpeedOverride(std::make_pair(
                speed_override->velocity, speed_override->acceleration));
        }

        return ParserResult<CommandInfo>::success({info, rest});
    };
}

Parser<CommandInfo> variableCommandParser(const std::string& command_name, size_t base_arg_group) 
{
    return [command_name, base_arg_group](ParserInput input) -> ParserResult<CommandInfo> {
        auto name_result = parseCommandName(command_name)(input);
        if (!name_result.isSuccess()) {
            return ParserResult<CommandInfo>::error(name_result.error());
        }
        
        auto [_, after_command] = name_result.value();
        
        if (after_command.atEnd() || after_command.current() != ':') {
            return ParserResult<CommandInfo>::error("At " + after_command.positionInfo() +
                ": Expected ':' after command");
        }
        
        ParserInput after_colon = after_command.advance();
        
        auto var_result = variableArgParser()(after_colon);
        if (!var_result.isSuccess()) {
            // Fall back to standard command parser if variable parsing fails
            return commandParser(command_name, base_arg_group)(input);
        }
        
        auto [var_info, after_var] = var_result.value();
        size_t new_base_arg_count = var_info.multiplier * base_arg_group;
        
        std::string error_msg;
        if (!validateArguments(var_info.remaining_args, new_base_arg_count, 
                               after_colon, command_name, error_msg)) {
            return ParserResult<CommandInfo>::error(error_msg);
        }

        CommandInfo info = buildCommandInfo(command_name, new_base_arg_count, 
                                            var_info.remaining_args);
        
        auto speed_override = parseSpeedOverrideFromArgs(var_info.remaining_args, 
                                                         new_base_arg_count);
        if (speed_override) {
            info.setSpeedOverride(std::make_pair(
                speed_override->velocity, speed_override->acceleration));
        }
        
        return ParserResult<CommandInfo>::success({info, after_var});
    };
}

//----------------------------------------
// Command Builder Implementation
//----------------------------------------
std::vector<Parser<CommandInfo>> CommandBuilder::createCommandParsers(
    const CommandRegistry& registry) 
{
    std::vector<Parser<CommandInfo>> parsers;
    parsers.reserve(registry.getAllCommands().size());
    
    for (const auto& command_name : registry.getAllCommands()) {
        if (registry.isVariable(command_name)) {
            const size_t variable_base_count = registry.getVariableBaseCount(command_name);
            parsers.push_back(variableCommandParser(command_name, variable_base_count));
        } else {
            const size_t arg_count = registry.getBaseArgCount(command_name);
            parsers.push_back(commandParser(command_name, arg_count));
        }
    }
    
    return parsers;
}

Parser<CommandInfo> CommandBuilder::createMainParser(const CommandRegistry& registry) {
    return choice(createCommandParsers(registry));
}

} // namespace parser
} // namespace worm_picker