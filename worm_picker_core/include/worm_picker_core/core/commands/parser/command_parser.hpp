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

// Parse the "N=X" variable argument pattern
inline Parser<VariableArgResult> variableArgParser() {
    return [](ParserInput input) -> ParserResult<VariableArgResult> {
        static const std::regex nPattern(R"(N=(\d+))");
        
        if (input.atEnd()) {
            return ParserResult<VariableArgResult>::error("Unexpected end of input");
        }
        
        std::string str(input.remainder());
        std::smatch match;
        
        if (!std::regex_search(str, match, nPattern)) {
            return ParserResult<VariableArgResult>::error("Expected 'N=' prefix");
        }
        
        // Extract the number after "N="
        int multiplier = std::stoi(match[1]);
        if (multiplier <= 0) {
            return ParserResult<VariableArgResult>::error("Invalid multiplier: must be positive");
        }
        
        // Skip past the "N=X" token
        size_t nLength = match[0].length();
        ParserInput afterN = input.advance(nLength);
        
        // Parse remaining arguments
        if (afterN.atEnd() || afterN.current() != ':') {
            return ParserResult<VariableArgResult>::error("Expected ':' after N= token");
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

// Parse speed override parameters
inline Parser<std::optional<SpeedOverride>> speedOverrideParser(size_t baseArgCount) {
    return [baseArgCount](ParserInput input) -> ParserResult<std::optional<SpeedOverride>> {
        // First, tokenize the entire input
        auto tokens = [&input]() -> std::vector<std::string> {
            std::vector<std::string> result;
            std::string_view text = input.text;
            size_t pos = 0;
            
            while (pos < text.length()) {
                size_t next = text.find(':', pos);
                if (next == std::string::npos) {
                    result.push_back(std::string(text.substr(pos)));
                    break;
                }
                
                result.push_back(std::string(text.substr(pos, next - pos)));
                pos = next + 1;
            }
            
            return result;
        }();
        
        // Check if we have the right number of tokens for speed override
        if (tokens.size() != baseArgCount + 2 + 1) {  // +1 for base command
            return ParserResult<std::optional<SpeedOverride>>::success({std::nullopt, input});
        }
        
        try {
            double velocity = std::stod(tokens[baseArgCount + 1]);
            double acceleration = std::stod(tokens[baseArgCount + 2]);
            
            // Validate range (0, 1]
            if (velocity <= 0 || velocity > 1 || acceleration <= 0 || acceleration > 1) {
                return ParserResult<std::optional<SpeedOverride>>::error(
                    "Speed override values must be in range (0, 1]");
            }
            
            // Calculate the position after parsing all arguments up to speed override
            size_t pos = 0;
            for (size_t i = 0; i <= baseArgCount; ++i) {
                pos += tokens[i].length() + 1;  // +1 for the colon
            }
            // -1 because the last argument doesn't have a colon
            if (pos > 0) pos--;
            
            ParserInput currentInput = input.skipTo(pos);
            
            return ParserResult<std::optional<SpeedOverride>>::success(
                std::make_pair(std::optional<SpeedOverride>{{velocity, acceleration}}, currentInput)
            );
            
        } catch (const std::exception& e) {
            return ParserResult<std::optional<SpeedOverride>>::error(
                "Failed to parse speed override: " + std::string(e.what()));
        }
    };
}

// Parse a specific command with fixed arguments
inline Parser<CommandInfo> commandParser(const std::string& commandName, size_t baseArgCount) {
    return [commandName, baseArgCount](ParserInput input) -> ParserResult<CommandInfo> {
        // First, check if the command name matches
        auto commandResult = baseCommandParser()(input);
        if (!commandResult.isSuccess()) {
            return ParserResult<CommandInfo>::error(commandResult.error());
        }
        
        auto [actualCommand, afterCommand] = commandResult.value();
        if (actualCommand != commandName) {
            return ParserResult<CommandInfo>::error(
                "Expected command '" + commandName + "', got '" + actualCommand + "'");
        }
        
        // Parse arguments
        ParserInput afterColon = afterCommand;
        if (!afterCommand.atEnd() && afterCommand.current() == ':') {
            afterColon = afterCommand.advance();
        } else {
            // No arguments, which is fine if baseArgCount is 0
            if (baseArgCount > 0) {
                return ParserResult<CommandInfo>::error(
                    "Expected " + std::to_string(baseArgCount) + " arguments for command '" + 
                    commandName + "'");
            }
        }
        
        std::vector<std::string> args;
        ParserInput afterArgs = afterColon;
        
        if (baseArgCount > 0) {
            auto argsResult = argumentsParser()(afterColon);
            if (!argsResult.isSuccess()) {
                return ParserResult<CommandInfo>::error(argsResult.error());
            }
            
            auto [parsedArgs, rest] = argsResult.value();
            args = parsedArgs;
            afterArgs = rest;
            
            // Check if we have enough arguments
            if (args.size() < baseArgCount) {
                return ParserResult<CommandInfo>::error(
                    "Expected " + std::to_string(baseArgCount) + " arguments for command '" + 
                    commandName + "', got " + std::to_string(args.size()));
            }
        }
        
        // Check for speed override
        auto overrideResult = speedOverrideParser(baseArgCount)(input);
        std::optional<SpeedOverride> speedOverride;
        
        if (overrideResult.isSuccess()) {
            auto [override, _] = overrideResult.value();
            speedOverride = override;
        }
        
        // Create command info
        CommandInfo info;
        info.setBaseCommand(commandName);
        info.setBaseArgsAmount(baseArgCount);
        info.setArgs(args);
        
        if (speedOverride) {
            info.setSpeedOverride(std::make_pair(speedOverride->velocity, speedOverride->acceleration));
        }
        
        return ParserResult<CommandInfo>::success({info, afterArgs});
    };
}

// Parse a command with variable arguments
inline Parser<CommandInfo> variableCommandParser(const std::string& commandName, size_t baseArgPerGroup) {
    return [commandName, baseArgPerGroup](ParserInput input) -> ParserResult<CommandInfo> {
        // First, check if the command name matches
        auto commandResult = baseCommandParser()(input);
        if (!commandResult.isSuccess()) {
            return ParserResult<CommandInfo>::error(commandResult.error());
        }
        
        auto [actualCommand, afterCommand] = commandResult.value();
        if (actualCommand != commandName) {
            return ParserResult<CommandInfo>::error(
                "Expected command '" + commandName + "', got '" + actualCommand + "'");
        }
        
        // Parse N= prefix
        ParserInput afterColon = afterCommand;
        if (!afterCommand.atEnd() && afterCommand.current() == ':') {
            afterColon = afterCommand.advance();
        } else {
            return ParserResult<CommandInfo>::error(
                "Expected 'N=' prefix for variable command '" + commandName + "'");
        }
        
        auto varResult = variableArgParser()(afterColon);
        if (!varResult.isSuccess()) {
            // If we can't parse as variable, try as a fixed command
            return commandParser(commandName, baseArgPerGroup)(input);
        }
        
        auto [varInfo, afterVar] = varResult.value();
        size_t newBaseArgCount = varInfo.multiplier * baseArgPerGroup;
        
        // Create a fixed parser with the new base arg count
        auto fixedParser = commandParser(commandName, newBaseArgCount);
        
        // Reconstruct the input without the "N=X" prefix
        std::string reconstructed = commandName + ":";
        for (const auto& arg : varInfo.remainingArgs) {
            reconstructed += arg + ":";
        }
        if (!reconstructed.empty()) {
            reconstructed.pop_back();  // Remove trailing ':'
        }
        
        ParserInput newInput(reconstructed);
        return fixedParser(newInput);
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