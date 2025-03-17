#include "worm_picker_core/core/commands/parser/new_command_parser.hpp"
#include "worm_picker_core/core/commands/parser/command_parsers.hpp"
#include "worm_picker_core/core/commands/parser/command_info_builder.hpp"
#include <fmt/format.h>

namespace worm_picker {
namespace parser {

NewCommandParser::NewCommandParser(const rclcpp::Node::SharedPtr& node) {
    registry_.loadFromNode(node);
    
    RCLCPP_INFO(logger_, "Initialized NewCommandParser with %zu commands", 
        registry_.getAllCommands().size());
}

Result<CommandInfo> NewCommandParser::parse(const std::string& command) {
    try {
        ParserInput input{command};
        
        auto baseCommandResult = baseCommandParser()(input);
        if (!baseCommandResult.isSuccess()) {
            return Result<CommandInfo>::error(
                fmt::format("Failed to parse base command: {}", baseCommandResult.error()));
        }
        
        const std::string& baseCommand = baseCommandResult.value();
        
        try {
            if (registry_.isVariable(baseCommand)) {
                size_t baseArgPerGroup = registry_.getVariableBaseCount(baseCommand);
                
                ParserInput argsInput = input.advanceTo(input.position + baseCommand.size());
                if (!argsInput.atEnd() && argsInput.current() == ':') {
                    ParserInput checkInput = argsInput.advance();
                    std::string nextArg;
                    
                    size_t colonPos = checkInput.remainder().find(':');
                    if (colonPos == std::string::npos) {
                        nextArg = std::string(checkInput.remainder());
                    } else {
                        nextArg = std::string(checkInput.remainder().substr(0, colonPos));
                    }
                    
                    if (nextArg.substr(0, 2) == "N=") {
                        auto varResult = parseVariableCommand(baseCommand, baseArgPerGroup)(input);
                        if (!varResult.isSuccess()) {
                            return Result<CommandInfo>::error(
                                fmt::format("Failed to parse variable command: {}", varResult.error()));
                        }
                        
                        auto& [argsPair, speedOverride] = varResult.value();
                        auto& [args, newBaseArgCount] = argsPair;
                        
                        CommandInfo info = CommandInfoBuilder::build(
                            baseCommand, args, newBaseArgCount, speedOverride);
                        
                        return Result<CommandInfo>::success(info);
                    }
                }
                
                auto fixedResult = parseFixedCommand(baseCommand, baseArgPerGroup)(input);
                if (!fixedResult.isSuccess()) {
                    return Result<CommandInfo>::error(
                        fmt::format("Failed to parse fixed command: {}", fixedResult.error()));
                }
                
                auto& [args, speedOverride] = fixedResult.value();
                
                CommandInfo info = CommandInfoBuilder::build(
                    baseCommand, args, baseArgPerGroup, speedOverride);
                
                return Result<CommandInfo>::success(info);
            } else {
                size_t baseArgCount = registry_.getBaseArgCount(baseCommand);
                
                auto fixedResult = parseFixedCommand(baseCommand, baseArgCount)(input);
                if (!fixedResult.isSuccess()) {
                    return Result<CommandInfo>::error(
                        fmt::format("Failed to parse fixed command: {}", fixedResult.error()));
                }
                
                auto& [args, speedOverride] = fixedResult.value();
                
                CommandInfo info = CommandInfoBuilder::build(
                    baseCommand, args, baseArgCount, speedOverride);
                
                return Result<CommandInfo>::success(info);
            }
        } catch (const std::exception& e) {
            return Result<CommandInfo>::error(
                fmt::format("Command '{}' not found in registry: {}", baseCommand, e.what()));
        }
    } catch (const std::exception& e) {
        return Result<CommandInfo>::error(
            fmt::format("Exception during parsing: {}", e.what()));
    }
}

}} // namespace worm_picker::parser