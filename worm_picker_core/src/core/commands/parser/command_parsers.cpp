#include "worm_picker_core/core/commands/parser/command_parsers.hpp"
#include <sstream>
#include <algorithm>

namespace worm_picker {
namespace parser {

Parser<std::string> baseCommandParser() {
    return token(':');
}

Parser<std::vector<std::string>> argumentsParser() {
    return [](ParserInput input) -> Result<std::vector<std::string>, std::string> {
        std::vector<std::string> args;
        ParserInput currentInput = input;
        
        while (!currentInput.atEnd()) {
            // Parse a colon
            if (currentInput.current() != ':') {
                return Result<std::vector<std::string>>::error(
                    "Expected ':', got '" + std::string(1, currentInput.current()) + "'");
            }
            
            // Advance past the colon
            currentInput = currentInput.advance();
            if (currentInput.atEnd()) {
                // Trailing colon, add empty argument
                args.push_back("");
                break;
            }
            
            // Parse the argument
            auto argResult = token(':')(currentInput);
            if (!argResult.isSuccess()) {
                return Result<std::vector<std::string>>::error(argResult.error());
            }
            
            args.push_back(argResult.value());
            
            // Advance past the argument
            currentInput = currentInput.advanceTo(
                currentInput.position + argResult.value().size());
        }
        
        return Result<std::vector<std::string>>::success(args);
    };
}

Parser<VariableArgResult> variableArgParser() {
    return [](ParserInput input) -> Result<VariableArgResult, std::string> {
        if (input.atEnd()) {
            return Result<VariableArgResult>::error("Unexpected end of input");
        }
        
        auto remainder = input.remainder();
        if (remainder.size() < 2 || remainder.substr(0, 2) != "N=") {
            return Result<VariableArgResult>::error(
                "Expected 'N=' prefix, got '" + 
                std::string(remainder.substr(0, std::min(size_t(2), remainder.size()))) + "'");
        }
        
        try {
            size_t processed = 0;
            size_t eqPos = remainder.find('=');
            if (eqPos == std::string::npos || eqPos + 1 >= remainder.size()) {
                return Result<VariableArgResult>::error("Malformed N= prefix");
            }
            
            std::string numStr = std::string(remainder.substr(eqPos + 1));
            size_t colonPos = numStr.find(':');
            if (colonPos != std::string::npos) {
                numStr = numStr.substr(0, colonPos);
            }
            
            int multiplier = std::stoi(numStr, &processed);
            
            if (processed == 0 || multiplier <= 0) {
                return Result<VariableArgResult>::error(
                    "Invalid multiplier after 'N=': " + numStr);
            }
            
            size_t nextColon = remainder.find(':', eqPos + 1 + processed);
            if (nextColon == std::string::npos) {
                return Result<VariableArgResult>::success({multiplier, {}});
            }
            
            auto argsInput = input.advanceTo(input.position + nextColon);
            auto argsResult = argumentsParser()(argsInput);
            if (!argsResult.isSuccess()) {
                return Result<VariableArgResult>::error(
                    "Failed to parse arguments after N=" + std::to_string(multiplier) + 
                    ": " + argsResult.error());
            }
            
            return Result<VariableArgResult>::success({multiplier, argsResult.value()});
        } catch (const std::exception& e) {
            return Result<VariableArgResult>::error(
                "Failed to parse multiplier: " + std::string(e.what()));
        }
    };
}

Parser<std::optional<SpeedOverride>> speedOverrideParser(size_t baseArgCount) {
    return [baseArgCount](ParserInput input) -> Result<std::optional<SpeedOverride>, std::string> {
        auto tokenizeResult = [](std::string_view text) -> std::vector<std::string> {
            std::vector<std::string> tokens;
            size_t start = 0;
            size_t pos = text.find(':');
            
            if (pos == std::string::npos) {
                tokens.push_back(std::string(text));
                return tokens;
            }
            
            tokens.push_back(std::string(text.substr(0, pos)));
            
            while (pos != std::string::npos) {
                start = pos + 1;
                pos = text.find(':', start);
                
                if (pos == std::string::npos) {
                    tokens.push_back(std::string(text.substr(start)));
                } else {
                    tokens.push_back(std::string(text.substr(start, pos - start)));
                }
            }
            
            return tokens;
        };
        
        std::vector<std::string> tokens = tokenizeResult(input.text);
        
        if (tokens.size() != baseArgCount + 1 + 2) {
            return Result<std::optional<SpeedOverride>>::success(std::nullopt);
        }
        
        try {
            double velocity = std::stod(tokens[baseArgCount + 1]);
            double acceleration = std::stod(tokens[baseArgCount + 2]);
            
            if (velocity <= 0.0 || velocity > 1.0 || acceleration <= 0.0 || acceleration > 1.0) {
                return Result<std::optional<SpeedOverride>>::error(
                    "Speed override values must be in range (0, 1]");
            }
            
            return Result<std::optional<SpeedOverride>>::success(
                SpeedOverride{velocity, acceleration});
        } catch (const std::exception& e) {
            return Result<std::optional<SpeedOverride>>::error(
                "Failed to parse speed override: " + std::string(e.what()));
        }
    };
}

Parser<std::pair<std::vector<std::string>, std::optional<SpeedOverride>>>
parseFixedCommand(const std::string& baseCommand, size_t baseArgCount) {
    return [baseCommand, baseArgCount](ParserInput input) 
        -> Result<std::pair<std::vector<std::string>, std::optional<SpeedOverride>>, std::string> {
        if (input.remainder().substr(0, baseCommand.size()) != baseCommand) {
            return Result<std::pair<std::vector<std::string>, std::optional<SpeedOverride>>>::error(
                "Expected base command '" + baseCommand + "'");
        }
        
        ParserInput argsInput = input.advanceTo(input.position + baseCommand.size());
        auto argsResult = argumentsParser()(argsInput);
        if (!argsResult.isSuccess()) {
            return Result<std::pair<std::vector<std::string>, std::optional<SpeedOverride>>>::error(
                "Failed to parse arguments: " + argsResult.error());
        }
        
        auto args = argsResult.value();
        if (args.size() != baseArgCount && args.size() != baseArgCount + 2) {
            std::stringstream ss;
            ss << "Invalid argument count for command '" << baseCommand << "': expected "
               << baseArgCount << " or " << (baseArgCount + 2) << " arguments, got " 
               << args.size();
            return Result<std::pair<std::vector<std::string>, std::optional<SpeedOverride>>>::error(
                ss.str());
        }
        
        auto speedResult = speedOverrideParser(baseArgCount)(input);
        if (!speedResult.isSuccess()) {
            return Result<std::pair<std::vector<std::string>, std::optional<SpeedOverride>>>::error(
                "Failed to parse speed override: " + speedResult.error());
        }
        
        return Result<std::pair<std::vector<std::string>, std::optional<SpeedOverride>>>::success(
            std::make_pair(args, speedResult.value()));
    };
}

Parser<std::pair<std::pair<std::vector<std::string>, size_t>, std::optional<SpeedOverride>>>
parseVariableCommand(const std::string& baseCommand, size_t baseArgPerGroup) {
    return [baseCommand, baseArgPerGroup](ParserInput input) 
        -> Result<std::pair<std::pair<std::vector<std::string>, size_t>, std::optional<SpeedOverride>>, std::string> {
        if (input.remainder().substr(0, baseCommand.size()) != baseCommand) {
            return Result<std::pair<std::pair<std::vector<std::string>, size_t>, std::optional<SpeedOverride>>>::error(
                "Expected base command '" + baseCommand + "'");
        }
        
        ParserInput varInput = input.advanceTo(input.position + baseCommand.size());
        if (varInput.atEnd() || varInput.current() != ':') {
            return Result<std::pair<std::pair<std::vector<std::string>, size_t>, std::optional<SpeedOverride>>>::error(
                "Expected ':' after base command");
        }
        
        varInput = varInput.advance();
        auto varResult = variableArgParser()(varInput);
        if (!varResult.isSuccess()) {
            return Result<std::pair<std::pair<std::vector<std::string>, size_t>, std::optional<SpeedOverride>>>::error(
                "Failed to parse variable arguments: " + varResult.error());
        }
        
        size_t newBaseArgCount = varResult.value().multiplier * baseArgPerGroup;
        
        auto args = varResult.value().remainingArgs;
        if (args.size() != newBaseArgCount && args.size() != newBaseArgCount + 2) {
            std::stringstream ss;
            ss << "Invalid argument count for variable command '" << baseCommand 
               << "': expected " << newBaseArgCount << " or " << (newBaseArgCount + 2) 
               << " arguments, got " << args.size();
            return Result<std::pair<std::pair<std::vector<std::string>, size_t>, std::optional<SpeedOverride>>>::error(
                ss.str());
        }
        
        auto speedResult = speedOverrideParser(newBaseArgCount)(input);
        if (!speedResult.isSuccess()) {
            return Result<std::pair<std::pair<std::vector<std::string>, size_t>, std::optional<SpeedOverride>>>::error(
                "Failed to parse speed override: " + speedResult.error());
        }
        
        return Result<std::pair<std::pair<std::vector<std::string>, size_t>, std::optional<SpeedOverride>>>::success(
            std::make_pair(std::make_pair(args, newBaseArgCount), speedResult.value()));
    };
}

}} // namespace worm_picker::parser