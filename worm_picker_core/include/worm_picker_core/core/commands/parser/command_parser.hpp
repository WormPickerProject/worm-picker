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
/**
 * @brief Result structure for variable argument parsing
 */
struct VariableArgResult {
    std::size_t multiplier;
    std::vector<std::string> remaining_args;
};

/**
 * @brief Structure for speed override parameters
 */
struct SpeedOverride {
    double velocity;
    double acceleration;
};

//----------------------------------------
// Command Registry
//----------------------------------------

/**
 * @brief Registry for commands and their expected argument counts
 */
class CommandRegistry {
public:
    /** @brief Default constructor */
    CommandRegistry() = default;

    /**
     * @brief Load commands from a ROS2 node's parameters
     * @param node The ROS2 node containing command parameters
     */
    void loadFromNode(const rclcpp::Node::SharedPtr& node);
    
    /**
     * @brief Check if a command exists in the registry
     * @param command The command name to check
     * @return true if the command exists, false otherwise
     */
    bool hasCommand(const std::string& command) const noexcept;
    
    /**
     * @brief Get the base argument count for a command
     * @param command The command name
     * @return The base argument count, or 0 if command not found
     */
    std::size_t getBaseArgCount(const std::string& command) const noexcept;
    
    /**
     * @brief Check if a command accepts variable arguments
     * @param command The command name
     * @return true if variable arguments are accepted, false otherwise
     */
    bool isVariable(const std::string& command) const noexcept;
    
    /**
     * @brief Get the base count for a variable command
     * @param command The variable command name
     * @return The base count for variable arguments, or 0 if not found
     */
    std::size_t getVariableBaseCount(const std::string& command) const noexcept;
    
    /**
     * @brief Get all registered command names
     * @return Vector of all command names
     */
    std::vector<std::string> getAllCommands() const;
    
    /**
     * @brief Register a new command
     * @param command The command name
     * @param base_arg_count The base argument count
     * @param is_variable Whether the command accepts variable arguments
     * @param variable_base_count The base count for variable arguments
     */
    void registerCommand(const std::string& command, 
                         std::size_t base_arg_count,
                         bool is_variable = false, 
                         std::size_t variable_base_count = 0);
    
private:
    /**
     * @brief Load commands from a ROS2 parameter
     * @param node The ROS2 node
     * @param param_name The parameter name
     * @param base_arg_count The base argument count for these commands
     */
    void loadCommandsFromParameter(const rclcpp::Node::SharedPtr& node, 
                                   const std::string& param_name,
                                   std::size_t base_arg_count);

    std::unordered_map<std::string, std::size_t> command_to_base_arg_count_;
    std::unordered_map<std::string, bool> is_variable_command_;
    std::unordered_map<std::string, std::size_t> variable_command_base_count_;
};

//----------------------------------------
// Helper and Basic Parsers
//----------------------------------------

/**
 * @brief Parser for the base command name
 * @return Parser that extracts a command name
 */
Parser<std::string> baseCommandParser();

/**
 * @brief Parser for command arguments
 * @return Parser that extracts a vector of argument strings
 */
Parser<std::vector<std::string>> argumentsParser();

/**
 * @brief Parser for variable arguments
 * @return Parser that extracts a VariableArgResult object
 */
Parser<VariableArgResult> variableArgParser();

/**
 * @brief Parser for a specific command name
 * @param expected_command The expected command name
 * @return Parser that validates the command name
 */
Parser<std::string> parseCommandName(const std::string& expected_command);

/**
 * @brief Parser for a required colon separator
 * @return Parser that validates the colon is present
 */
Parser<ParserInput> parseColon();

/**
 * @brief Parser for an optional colon separator
 * @return Parser that consumes a colon if present
 */
Parser<ParserInput> parseOptionalColon();

/**
 * @brief Validate command arguments
 * @param args The parsed arguments
 * @param expected_count The expected argument count
 * @param input The parser input for error reporting
 * @param command_name The command name for error reporting
 * @param error_msg Output parameter for error message
 * @return true if validation succeeds, false otherwise
 */
bool validateArguments(const std::vector<std::string>& args,
                       std::size_t expected_count,
                       const ParserInput& input,
                       const std::string& command_name,
                       std::string& error_msg);

/**
 * @brief Parse speed override from trailing arguments
 * @param args The command arguments
 * @param base_arg_count The base argument count
 * @return The speed override if present, nullopt otherwise
 */
std::optional<SpeedOverride> parseSpeedOverrideFromArgs(
    const std::vector<std::string>& args,
    std::size_t base_arg_count);

/**
 * @brief Build a CommandInfo object
 * @param command_name The command name
 * @param base_arg_count The base argument count
 * @param args The command arguments
 * @return A constructed CommandInfo object
 */
CommandInfo buildCommandInfo(const std::string& command_name, 
                             std::size_t base_arg_count, 
                             const std::vector<std::string>& args = {});

//----------------------------------------
// Command Parsers
//----------------------------------------

/**
 * @brief Parser for a standard command
 * @param command_name The command name
 * @param base_arg_count The expected argument count
 * @return Parser that extracts a CommandInfo object
 */
Parser<CommandInfo> commandParser(const std::string& command_name, std::size_t base_arg_count);

/**
 * @brief Parser for a variable argument command
 * @param command_name The command name
 * @param base_arg_group The base argument group size
 * @return Parser that extracts a CommandInfo object
 */
Parser<CommandInfo> variableCommandParser(const std::string& command_name, std::size_t base_arg_group);

//----------------------------------------
// Command Builder Helper
//----------------------------------------

/**
 * @brief Utility class for building command parsers
 */
class CommandBuilder {
public:
    /**
     * @brief Create parsers for all commands in the registry
     * @param registry The command registry
     * @return Vector of command parsers
     */
    static std::vector<Parser<CommandInfo>> createCommandParsers(const CommandRegistry& registry);
    
    /**
     * @brief Create a main parser that tries all command parsers
     * @param registry The command registry
     * @return A combined parser for all commands
     */
    static Parser<CommandInfo> createMainParser(const CommandRegistry& registry);
};

} // namespace parser
} // namespace worm_picker