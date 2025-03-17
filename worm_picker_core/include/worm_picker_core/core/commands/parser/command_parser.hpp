#pragma once

#include <string>
#include <vector>
#include <optional>
#include <unordered_map>
#include <regex>
#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/core/commands/parser/parser_core.hpp"
#include "worm_picker_core/core/commands/command_info.hpp"

namespace worm_picker::parser {

//=======================================
// Command-Specific Types
//=======================================

// Result of parsing the variable argument N= prefix
struct VariableArgResult {
    size_t multiplier;
    std::vector<std::string> remainingArgs;
};

// Speed override parameters
struct SpeedOverride {
    double velocity;
    double acceleration;
};

//=======================================
// Command Registry
//=======================================

class CommandRegistry {
public:
    CommandRegistry() = default;
    
    // Load commands from node parameters
    void loadFromNode(const rclcpp::Node::SharedPtr& node) {
        loadCommandsFromParameter(node, "commands.zero_arg", 0);
        loadCommandsFromParameter(node, "commands.one_arg", 1);
        loadCommandsFromParameter(node, "commands.two_arg", 2);
        loadCommandsFromParameter(node, "commands.three_arg", 3);
        loadCommandsFromParameter(node, "commands.four_arg", 4);
        loadCommandsFromParameter(node, "commands.eight_arg", 8);
        
        // Load variable-arg commands
        auto variableCommands = param_utils::getParameter<std::vector<std::string>>(node, "commands.variable_arg");
        if (variableCommands) {
            for (const auto& command : variableCommands.value()) {
                // Find the base config for each variable command
                auto baseArg = getBaseArgCount(command);
                if (baseArg > 0) {
                    registerCommand(command, baseArg, true, baseArg);
                }
            }
        }
    }
    
    // Query methods
    bool hasCommand(const std::string& command) const {
        return commandToBaseArgCount_.find(command) != commandToBaseArgCount_.end();
    }
    
    size_t getBaseArgCount(const std::string& command) const {
        auto it = commandToBaseArgCount_.find(command);
        return (it != commandToBaseArgCount_.end()) ? it->second : 0;
    }
    
    bool isVariable(const std::string& command) const {
        auto it = isVariableCommand_.find(command);
        return (it != isVariableCommand_.end()) ? it->second : false;
    }
    
    size_t getVariableBaseCount(const std::string& command) const {
        auto it = variableCommandBaseCount_.find(command);
        return (it != variableCommandBaseCount_.end()) ? it->second : 0;
    }
    
    std::vector<std::string> getAllCommands() const {
        std::vector<std::string> result;
        result.reserve(commandToBaseArgCount_.size());
        
        for (const auto& [command, _] : commandToBaseArgCount_) {
            result.push_back(command);
        }
        
        return result;
    }
    
    // Register commands programmatically
    void registerCommand(
        const std::string& command, 
        size_t baseArgCount, 
        bool isVariable = false,
        size_t variableBaseCount = 0)
    {
        commandToBaseArgCount_[command] = baseArgCount;
        
        if (isVariable) {
            isVariableCommand_[command] = true;
            variableCommandBaseCount_[command] = variableBaseCount;
        }
    }

private:
    std::unordered_map<std::string, size_t> commandToBaseArgCount_;
    std::unordered_map<std::string, bool> isVariableCommand_;
    std::unordered_map<std::string, size_t> variableCommandBaseCount_;
    
    void loadCommandsFromParameter(
        const rclcpp::Node::SharedPtr& node, 
        const std::string& paramName, 
        size_t baseArgCount)
    {
        auto commands = param_utils::getParameter<std::vector<std::string>>(node, paramName);
        if (commands) {
            for (const auto& command : commands.value()) {
                registerCommand(command, baseArgCount);
                RCLCPP_INFO(node->get_logger(), 
                    "Registered %zu-arg command: %s", baseArgCount, command.c_str());
            }
        }
    }
};

//=======================================
// Command Parsers
//=======================================

// Parse the base command (everything before the first colon)
inline Parser<std::string> baseCommandParser() {
    return token(':');
}

// Parse a list of arguments (colon-separated)
inline Parser<std::vector<std::string>> argumentsParser() {
    auto colonParser = character(':');
    return sepBy(token(':'), colonParser);
}

// Check if the last two arguments can be a valid speed override
inline bool checkSpeedOverride(const std::vector<std::string>& args, double& velocity, double& acceleration) {
    if (args.size() < 2) {
        return false;
    }
    
    try {
        size_t idx = args.size() - 2;
        velocity = std::stod(args[idx]);
        acceleration = std::stod(args[idx + 1]);
        
        // Validate range (0, 1]
        if (velocity <= 0 || velocity > 1 || acceleration <= 0 || acceleration > 1) {
            return false;
        }
        
        return true;
    } catch (...) {
        return false;
    }
}

// Parse speed override parameters directly from arguments
inline std::optional<SpeedOverride> parseSpeedOverrideFromArgs(const std::vector<std::string>& args, size_t baseArgCount) {
    // Check if we have exactly baseArgCount + 2 arguments
    if (args.size() != baseArgCount + 2) {
        return std::nullopt;
    }
    
    double velocity, acceleration;
    if (checkSpeedOverride(args, velocity, acceleration)) {
        return SpeedOverride{velocity, acceleration};
    }
    
    return std::nullopt;
}

// Parse the "N=X" variable argument pattern using regex
inline Parser<VariableArgResult> variableArgParser() {
    return [](ParserInput input) -> ParserResult<VariableArgResult> {
        static const std::regex nPattern(R"(N=(\d+))");
        
        if (input.atEnd()) {
            return ParserResult<VariableArgResult>::error(
                "At " + input.positionInfo() + ": Unexpected end of input");
        }
        
        std::string str(input.remainder());
        std::smatch match;
        
        if (!std::regex_search(str, match, nPattern)) {
            return ParserResult<VariableArgResult>::error(
                "At " + input.positionInfo() + ": Expected 'N=' prefix");
        }
        
        // Extract the number after "N="
        int multiplier = std::stoi(match[1]);
        if (multiplier <= 0) {
            return ParserResult<VariableArgResult>::error(
                "At " + input.positionInfo() + ": Invalid multiplier: must be positive");
        }
        
        // Skip past the "N=X" token
        size_t nLength = match[0].length();
        ParserInput afterN = input.advance(nLength);
        
        // Parse remaining arguments
        if (afterN.atEnd() || afterN.current() != ':') {
            return ParserResult<VariableArgResult>::error(
                "At " + input.positionInfo() + ": Expected ':' after N= token");
        }
        
        auto argsResult = argumentsParser()(afterN.advance());
        if (!argsResult.isSuccess()) {
            return ParserResult<VariableArgResult>::error(argsResult.error());
        }
        
        auto [args, nextInput] = argsResult.value();
        
        return ParserResult<VariableArgResult>::success({
            {static_cast<size_t>(multiplier), args}, nextInput
        });
    };
}

// Helper function to parse command name
inline Parser<std::string> parseCommandName(const std::string& expectedCommand) {
    return [expectedCommand](ParserInput input) -> ParserResult<std::string> {
        auto commandResult = baseCommandParser()(input);
        if (!commandResult.isSuccess()) {
            return commandResult;
        }
        
        auto [actualCommand, afterCommand] = commandResult.value();
        if (actualCommand != expectedCommand) {
            return ParserResult<std::string>::error(
                "At " + input.positionInfo() + ": Expected command '" + expectedCommand + 
                "', got '" + actualCommand + "'");
        }
        
        return ParserResult<std::string>::success({actualCommand, afterCommand});
    };
}

// Helper function to validate argument count (including potential speed override)
inline bool validateArgCount(const std::vector<std::string>& args, size_t expectedCount, 
                            std::string& errorMsg, const ParserInput& input, const std::string& commandName) {
    // We need to allow for speed override which adds 2 more arguments
    if (args.size() < expectedCount && args.size() != expectedCount + 2) {
        errorMsg = "At " + input.positionInfo() + ": Expected " + std::to_string(expectedCount) + 
                   " arguments for command '" + commandName + "', got " + std::to_string(args.size());
        return false;
    }
    return true;
}

// Helper function to parse arguments
inline Parser<std::vector<std::string>> parseArguments(size_t expectedCount, const std::string& commandName) {
    return [expectedCount, commandName](ParserInput input) -> ParserResult<std::vector<std::string>> {
        if (input.atEnd() || input.current() != ':') {
            if (expectedCount == 0) {
                return ParserResult<std::vector<std::string>>::success({std::vector<std::string>{}, input});
            }
            return ParserResult<std::vector<std::string>>::error(
                "At " + input.positionInfo() + ": Expected ':' followed by " + 
                std::to_string(expectedCount) + " arguments for command '" + commandName + "'");
        }
        
        auto argsResult = argumentsParser()(input.advance());
        if (!argsResult.isSuccess()) {
            return argsResult;
        }
        
        auto [args, rest] = argsResult.value();
        std::string errorMsg;
        if (!validateArgCount(args, expectedCount, errorMsg, input, commandName)) {
            return ParserResult<std::vector<std::string>>::error(errorMsg);
        }
        
        return ParserResult<std::vector<std::string>>::success({args, rest});
    };
}

// Parse a specific command with fixed arguments
inline Parser<CommandInfo> commandParser(const std::string& commandName, size_t baseArgCount) {
    return [commandName, baseArgCount](ParserInput input) -> ParserResult<CommandInfo> {
        // Parse command name
        auto commandResult = parseCommandName(commandName)(input);
        if (!commandResult.isSuccess()) {
            return ParserResult<CommandInfo>::error(commandResult.error());
        }
        
        auto [_, afterCommand] = commandResult.value();
        
        // Parse arguments
        std::vector<std::string> args;
        ParserInput afterArgs = afterCommand;
        
        if (baseArgCount > 0 || afterCommand.current() == ':') {
            auto argsResult = argumentsParser()(afterCommand.advance());
            if (!argsResult.isSuccess()) {
                return ParserResult<CommandInfo>::error(argsResult.error());
            }
            
            auto [parsedArgs, rest] = argsResult.value();
            args = parsedArgs;
            afterArgs = rest;
            
            // Make sure we have at least the base arguments
            if (args.size() < baseArgCount) {
                return ParserResult<CommandInfo>::error(
                    "At " + afterCommand.positionInfo() + ": Expected at least " + 
                    std::to_string(baseArgCount) + " arguments for command '" + commandName + 
                    "', got " + std::to_string(args.size()));
            }
        }
        
        // Create command info
        CommandInfo info;
        info.setBaseCommand(commandName);
        info.setBaseArgsAmount(baseArgCount);
        info.setArgs(args);
        
        // Check for speed override
        auto speedOverride = parseSpeedOverrideFromArgs(args, baseArgCount);
        if (speedOverride) {
            auto logger = rclcpp::get_logger("CommandParser");
            RCLCPP_DEBUG(logger, "Found speed override for command '%s': %f, %f", 
                commandName.c_str(), speedOverride->velocity, speedOverride->acceleration);
            info.setSpeedOverride(std::make_pair(speedOverride->velocity, speedOverride->acceleration));
        }
        
        return ParserResult<CommandInfo>::success({info, afterArgs});
    };
}

// Parse a command with variable arguments
inline Parser<CommandInfo> variableCommandParser(const std::string& commandName, size_t baseArgPerGroup) {
    return [commandName, baseArgPerGroup](ParserInput input) -> ParserResult<CommandInfo> {
        // Parse command name
        auto commandResult = parseCommandName(commandName)(input);
        if (!commandResult.isSuccess()) {
            return ParserResult<CommandInfo>::error(commandResult.error());
        }
        
        auto [_, afterCommand] = commandResult.value();
        
        // Check for colon
        if (afterCommand.atEnd() || afterCommand.current() != ':') {
            return ParserResult<CommandInfo>::error(
                "At " + afterCommand.positionInfo() + ": Expected ':' after command");
        }
        
        ParserInput afterColon = afterCommand.advance();
        
        // Try to parse as variable arg format
        auto varResult = variableArgParser()(afterColon);
        
        if (varResult.isSuccess()) {
            auto [varInfo, afterVar] = varResult.value();
            size_t newBaseArgCount = varInfo.multiplier * baseArgPerGroup;
            auto logger = rclcpp::get_logger("CommandParser");
            
            RCLCPP_DEBUG(logger, "Variable command '%s': N=%zu, baseArgPerGroup=%zu, newBaseArgCount=%zu, args=%zu", 
                commandName.c_str(), varInfo.multiplier, baseArgPerGroup, newBaseArgCount, 
                varInfo.remainingArgs.size());
            
            // Validate that we have the right number of arguments
            std::string errorMsg;
            if (!validateArgCount(varInfo.remainingArgs, newBaseArgCount, errorMsg, afterColon, commandName)) {
                return ParserResult<CommandInfo>::error(errorMsg);
            }
            
            // Create command info
            CommandInfo info;
            info.setBaseCommand(commandName);
            info.setBaseArgsAmount(newBaseArgCount);
            info.setArgs(varInfo.remainingArgs);
            
            // Check for speed override
            auto speedOverride = parseSpeedOverrideFromArgs(varInfo.remainingArgs, newBaseArgCount);
            if (speedOverride) {
                RCLCPP_DEBUG(logger, "Found speed override for variable command '%s': %f, %f", 
                    commandName.c_str(), speedOverride->velocity, speedOverride->acceleration);
                info.setSpeedOverride(std::make_pair(speedOverride->velocity, speedOverride->acceleration));
            }
            
            return ParserResult<CommandInfo>::success({info, afterVar});
        } else {
            // If we can't parse as variable, try as a fixed command
            return commandParser(commandName, baseArgPerGroup)(input);
        }
    };
}

//=======================================
// Command Builder Helper
//=======================================

class CommandBuilder {
public:
    // Create parsers for all registered commands
    static std::vector<Parser<CommandInfo>> createCommandParsers(const CommandRegistry& registry) {
        std::vector<Parser<CommandInfo>> parsers;
        
        for (const auto& commandName : registry.getAllCommands()) {
            if (registry.isVariable(commandName)) {
                parsers.push_back(variableCommandParser(commandName, registry.getVariableBaseCount(commandName)));
            } else {
                parsers.push_back(commandParser(commandName, registry.getBaseArgCount(commandName)));
            }
        }
        
        return parsers;
    }
    
    // Create the main parser that tries all command parsers
    static Parser<CommandInfo> createMainParser(const CommandRegistry& registry) {
        return choice(createCommandParsers(registry));
    }
};

} // namespace worm_picker::parser