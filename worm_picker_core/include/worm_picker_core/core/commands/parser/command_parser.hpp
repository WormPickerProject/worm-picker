#pragma once
#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include <string>
#include <vector>
#include <optional>
#include <unordered_map>
#include <regex>
#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/core/commands/parser/parser_core.hpp"
#include "worm_picker_core/core/commands/command_info.hpp"

namespace worm_picker {
namespace parser {

//----------------------------------------
// Command-Specific Types
//----------------------------------------

// Holds the result from parsing a variable-argument prefix (e.g., "N=3")
struct VariableArgResult {
    size_t multiplier;
    std::vector<std::string> remainingArgs;
};

// Represents optional speed override parameters
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
    
    // Load commands from node parameters
    void loadFromNode(const rclcpp::Node::SharedPtr& node);
    
    // Query methods
    bool hasCommand(const std::string& command) const;
    size_t getBaseArgCount(const std::string& command) const;
    bool isVariable(const std::string& command) const;
    size_t getVariableBaseCount(const std::string& command) const;
    std::vector<std::string> getAllCommands() const;
    
    // Register commands programmatically
    void registerCommand(const std::string& command, size_t baseArgCount, bool isVariable = false, size_t variableBaseCount = 0);
    
private:
    std::unordered_map<std::string, size_t> commandToBaseArgCount_;
    std::unordered_map<std::string, bool> isVariableCommand_;
    std::unordered_map<std::string, size_t> variableCommandBaseCount_;
    
    void loadCommandsFromParameter(const rclcpp::Node::SharedPtr& node, const std::string& paramName, size_t baseArgCount);
};

//----------------------------------------
// Helper and Basic Parsers
//----------------------------------------

// Parse the base command (everything before the first colon)
Parser<std::string> baseCommandParser();

// Parse a list of colon-separated arguments
Parser<std::vector<std::string>> argumentsParser();

// Parse and verify that the command name matches the expected one
Parser<std::string> parseCommandName(const std::string& expectedCommand);

// Helper to parse the colon following a command name
Parser<ParserInput> parseColon();

// Helper to parse an optional colon (succeeds with current input if no colon is present)
Parser<ParserInput> parseOptionalColon();

// Validate that the argument list has either exactly the expected count
// or the expected count plus 2 (if a speed override is provided)
bool validateArguments(const std::vector<std::string>& args,
                       size_t expectedCount,
                       const ParserInput& input,
                       const std::string& commandName,
                       std::string& errorMsg);

// Extract speed override parameters from the argument list, if present
std::optional<SpeedOverride> parseSpeedOverrideFromArgs(const std::vector<std::string>& args,
                                                        size_t baseArgCount);

// Helper to build a CommandInfo.
CommandInfo buildCommandInfo(const std::string& commandName, 
                             size_t baseArgCount, 
                             const std::vector<std::string>& args = {});

//----------------------------------------
// Command Parsers
//----------------------------------------

// Parse a command with fixed arguments (without a variable "N=" prefix)
Parser<CommandInfo> commandParser(const std::string& commandName, size_t baseArgCount);

// Parse a command with variable arguments (with a prefix like "N=3")
Parser<CommandInfo> variableCommandParser(const std::string& commandName, size_t baseArgPerGroup);

//----------------------------------------
// Command Builder Helper
//----------------------------------------

class CommandBuilder {
public:
    // Create individual parsers for all registered commands
    static std::vector<Parser<CommandInfo>> createCommandParsers(const CommandRegistry& registry);
    // Create the main parser that tries all command parsers
    static Parser<CommandInfo> createMainParser(const CommandRegistry& registry);
};

} // namespace parser
} // namespace worm_picker

#endif // COMMAND_PARSER_HPP