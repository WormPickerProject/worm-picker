#include "worm_picker_core/core/commands/parser/command_parser.hpp"
#include <algorithm>
#include <sstream>

namespace worm_picker {
namespace parser {

//----------------------------------------
// CommandRegistry Implementation
//----------------------------------------

void CommandRegistry::loadFromNode(const rclcpp::Node::SharedPtr& node) {
    loadCommandsFromParameter(node, "commands.zero_arg", 0);
    loadCommandsFromParameter(node, "commands.one_arg", 1);
    loadCommandsFromParameter(node, "commands.two_arg", 2);
    loadCommandsFromParameter(node, "commands.three_arg", 3);
    loadCommandsFromParameter(node, "commands.four_arg", 4);
    loadCommandsFromParameter(node, "commands.eight_arg", 8);

    // Load variable-argument commands
    auto variableCommands = param_utils::getParameter<std::vector<std::string>>(node, "commands.variable_arg");
    if (variableCommands) {
        for (const auto& command : variableCommands.value()) {
            auto baseArg = getBaseArgCount(command);
            if (baseArg > 0) {
                registerCommand(command, baseArg, true, baseArg);
            }
        }
    }
}

bool CommandRegistry::hasCommand(const std::string& command) const {
    return commandToBaseArgCount_.find(command) != commandToBaseArgCount_.end();
}

size_t CommandRegistry::getBaseArgCount(const std::string& command) const {
    auto it = commandToBaseArgCount_.find(command);
    return (it != commandToBaseArgCount_.end()) ? it->second : 0;
}

bool CommandRegistry::isVariable(const std::string& command) const {
    auto it = isVariableCommand_.find(command);
    return (it != isVariableCommand_.end()) ? it->second : false;
}

size_t CommandRegistry::getVariableBaseCount(const std::string& command) const {
    auto it = variableCommandBaseCount_.find(command);
    return (it != variableCommandBaseCount_.end()) ? it->second : 0;
}

std::vector<std::string> CommandRegistry::getAllCommands() const {
    std::vector<std::string> result;
    result.reserve(commandToBaseArgCount_.size());
    for (const auto& pair : commandToBaseArgCount_) {
        result.push_back(pair.first);
    }
    return result;
}

void CommandRegistry::registerCommand(const std::string& command,
                                        size_t baseArgCount,
                                        bool isVariable,
                                        size_t variableBaseCount) {
    commandToBaseArgCount_[command] = baseArgCount;
    if (isVariable) {
        isVariableCommand_[command] = true;
        variableCommandBaseCount_[command] = variableBaseCount;
    }
}

void CommandRegistry::loadCommandsFromParameter(const rclcpp::Node::SharedPtr& node,
                                                  const std::string& paramName,
                                                  size_t baseArgCount) {
    auto commands = param_utils::getParameter<std::vector<std::string>>(node, paramName);
    if (commands) {
        for (const auto& command : commands.value()) {
            registerCommand(command, baseArgCount);
            RCLCPP_INFO(node->get_logger(), "Registered %zu-arg command: %s", baseArgCount, command.c_str());
        }
    }
}

//----------------------------------------
// Basic Parsers and Helpers
//----------------------------------------

// Use the preexisting token() parser to extract the base command (up to the first colon)
Parser<std::string> baseCommandParser() {
    return token(':');
}

// Split the input into colon-separated tokens
Parser<std::vector<std::string>> argumentsParser() {
    auto colonParser = character(':');
    return sepBy(token(':'), colonParser);
}

// Ensure that the base command matches the expected string.
Parser<std::string> parseCommandName(const std::string& expectedCommand) {
    return [expectedCommand](ParserInput input) -> ParserResult<std::string> {
        auto commandResult = baseCommandParser()(input);
        if (!commandResult.isSuccess()) {
            return ParserResult<std::string>::error(commandResult.error());
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

// Helper to parse the colon following a command name.
Parser<ParserInput> parseColon() {
    return [](ParserInput input) -> ParserResult<ParserInput> {
        if (input.atEnd() || input.current() != ':') {
            return ParserResult<ParserInput>::error("At " + input.positionInfo() + ": Expected ':' after command name");
        }
        // Advance past the colon
        return ParserResult<ParserInput>::success({input.advance(), input.advance()});
    };
}

// Helper to parse an optional colon (succeeds with current input if no colon is present)
Parser<ParserInput> parseOptionalColon() {
    return [](ParserInput input) -> ParserResult<ParserInput> {
        if (input.atEnd() || input.current() != ':') {
            // No colon is present; succeed without consuming anything.
            return ParserResult<ParserInput>::success({input, input});
        }
        // If a colon is present, advance past it
        return ParserResult<ParserInput>::success({input.advance(), input.advance()});
    };
}
// Validate that the arguments vector has either exactly the expected number
// or the expected number plus 2 extra tokens for a speed override.
bool validateArguments(const std::vector<std::string>& args,
                       size_t expectedCount,
                       const ParserInput& input,
                       const std::string& commandName,
                       std::string& errorMsg) {
    if (args.size() != expectedCount && args.size() != expectedCount + 2) {
        std::ostringstream oss;
        oss << "At " << input.positionInfo() << ": Expected " << expectedCount 
            << " arguments for command '" << commandName << "', got " << args.size();
        errorMsg = oss.str();
        return false;
    }
    return true;
}

// Check for a valid speed override in the last two tokens.
std::optional<SpeedOverride> parseSpeedOverrideFromArgs(const std::vector<std::string>& args,
                                                        size_t baseArgCount) {
    if (args.size() != baseArgCount + 2) {
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

// Helper to build a CommandInfo.
CommandInfo buildCommandInfo(const std::string& commandName, 
                             size_t baseArgCount, 
                             const std::vector<std::string>& args) {
    CommandInfo info;
    info.setBaseCommand(commandName);
    info.setBaseArgsAmount(baseArgCount);
    info.setArgs(args);
    return info;
}

//----------------------------------------
// Variable Argument Parsing Helper
//----------------------------------------

// Parse the "N=X" prefix using a regex and then the remaining arguments.
static Parser<VariableArgResult> variableArgParser() {
    return [](ParserInput input) -> ParserResult<VariableArgResult> {
        static const std::regex nPattern(R"(N=(\d+))");
        
        if (input.atEnd()) {
            return ParserResult<VariableArgResult>::error("At " + input.positionInfo() + ": Unexpected end of input");
        }
        
        std::string str(input.remainder());
        std::smatch match;
        
        if (!std::regex_search(str, match, nPattern)) {
            return ParserResult<VariableArgResult>::error("At " + input.positionInfo() + ": Expected 'N=' prefix");
        }
        
        int multiplier = std::stoi(match[1]);
        if (multiplier <= 0) {
            return ParserResult<VariableArgResult>::error("At " + input.positionInfo() + ": Invalid multiplier: must be positive");
        }
        
        size_t nLength = match[0].length();
        ParserInput afterN = input.advance(nLength);
        if (afterN.atEnd() || afterN.current() != ':') {
            return ParserResult<VariableArgResult>::error("At " + input.positionInfo() + ": Expected ':' after N= token");
        }
        
        // Parse remaining arguments after the colon
        auto argsResult = argumentsParser()(afterN.advance());
        if (!argsResult.isSuccess()) {
            return ParserResult<VariableArgResult>::error(argsResult.error());
        }
        auto [args, nextInput] = argsResult.value();
        return ParserResult<VariableArgResult>::success({{static_cast<size_t>(multiplier), args}, nextInput});
    };
}

//----------------------------------------
// Command Parsers
//----------------------------------------

// Parse a fixed command (one without a variable "N=" prefix)
// This implementation chains the parsing of the command name and the colon.
Parser<CommandInfo> commandParser(const std::string& commandName, size_t baseArgCount) {
    return [commandName, baseArgCount](ParserInput input) -> ParserResult<CommandInfo> {
        // Combine command name with a colon parser that tries the mandatory colon first,
        // and if that fails, falls back to our optional colon parser.
        auto commandChain = combine(
            parseCommandName(commandName),
            orElse(parseColon(), parseOptionalColon()),
            [](std::string, ParserInput afterColon) { return afterColon; }
        );

        auto chainResult = commandChain(input);
        if (!chainResult.isSuccess()) {
            return ParserResult<CommandInfo>::error(chainResult.error());
        }
        auto [afterColon, _] = chainResult.value();

        // For zero-argument commands, if no colon was consumed,
        // return the command info immediately.
        if (baseArgCount == 0 && afterColon.atEnd()) {
            return ParserResult<CommandInfo>::success({buildCommandInfo(commandName, 0), afterColon});
        }        
        
        // Parse the colon-separated arguments.
        ParserInput argsInput = afterColon;
        auto argsResult = argumentsParser()(argsInput);
        if (!argsResult.isSuccess())
            return ParserResult<CommandInfo>::error(argsResult.error());
        
        auto [args, rest] = argsResult.value();
        std::string errorMsg;
        if (!validateArguments(args, baseArgCount, argsInput, commandName, errorMsg))
            return ParserResult<CommandInfo>::error(errorMsg);
        
        CommandInfo info = buildCommandInfo(commandName, baseArgCount, args);
        if (auto speedOverride = parseSpeedOverrideFromArgs(args, baseArgCount)) {
            info.setSpeedOverride(std::make_pair(speedOverride->velocity, speedOverride->acceleration));
        }
        
        return ParserResult<CommandInfo>::success({info, rest});
    };
}

// Parse a variable command that might start with an "N=X" prefix.
// If variable parsing fails, fall back to fixed command parsing.
Parser<CommandInfo> variableCommandParser(const std::string& commandName, size_t baseArgPerGroup) {
    return [commandName, baseArgPerGroup](ParserInput input) -> ParserResult<CommandInfo> {
        auto nameResult = parseCommandName(commandName)(input);
        if (!nameResult.isSuccess())
            return ParserResult<CommandInfo>::error(nameResult.error());
        
        auto [_, afterCommand] = nameResult.value();
        if (afterCommand.atEnd() || afterCommand.current() != ':') {
            return ParserResult<CommandInfo>::error("At " + afterCommand.positionInfo() +
                ": Expected ':' after command");
        }
        ParserInput afterColon = afterCommand.advance();
        
        auto varResult = variableArgParser()(afterColon);
        if (varResult.isSuccess()) {
            auto [varInfo, afterVar] = varResult.value();
            size_t newBaseArgCount = varInfo.multiplier * baseArgPerGroup;
            std::string errorMsg;
            if (!validateArguments(varInfo.remainingArgs, newBaseArgCount, afterColon, commandName, errorMsg))
                return ParserResult<CommandInfo>::error(errorMsg);
                        
            CommandInfo info = buildCommandInfo(commandName, newBaseArgCount, varInfo.remainingArgs);
            if (auto speedOverride = parseSpeedOverrideFromArgs(varInfo.remainingArgs, newBaseArgCount)) {
                info.setSpeedOverride(std::make_pair(speedOverride->velocity, speedOverride->acceleration));
            }
            return ParserResult<CommandInfo>::success({info, afterVar});
        } else {
            // Fallback to fixed command parsing if variable parsing fails.
            return commandParser(commandName, baseArgPerGroup)(input);
        }
    };
}

//----------------------------------------
// Command Builder Implementation
//----------------------------------------

std::vector<Parser<CommandInfo>> CommandBuilder::createCommandParsers(const CommandRegistry& registry) {
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

Parser<CommandInfo> CommandBuilder::createMainParser(const CommandRegistry& registry) {
    return choice(createCommandParsers(registry));
}

} // namespace parser
} // namespace worm_picker
