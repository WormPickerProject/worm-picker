#include "worm_picker_core/core/commands/parser/command_registry.hpp"
#include "worm_picker_core/utils/parameter_utils.hpp"
#include <fmt/format.h>

namespace worm_picker {
namespace parser {

void CommandRegistry::loadFromNode(const rclcpp::Node::SharedPtr& node) {
    const std::vector<std::pair<std::string, size_t>> configTypes = {
        {"commands.zero_arg", 0},
        {"commands.one_arg", 1},
        {"commands.two_arg", 2},
        {"commands.three_arg", 3},
        {"commands.four_arg", 4},
        {"commands.eight_arg", 8}
    };
    
    for (const auto& [paramKey, argCount] : configTypes) {
        if (auto names = param_utils::getParameter<std::vector<std::string>>(node, paramKey)) {
            for (const auto& name : names.value()) {
                registerCommand(name, argCount);
                
                RCLCPP_INFO(node->get_logger(), 
                    "Registered %zu-arg command: %s", argCount, name.c_str());
            }
        } else {
            RCLCPP_WARN(node->get_logger(), 
                "No commands found for key '%s'", paramKey.c_str());
        }
    }
    
    // Register variable argument commands
    if (auto names = param_utils::getParameter<std::vector<std::string>>(
            node, "commands.variable_arg")) {
        for (const auto& name : names.value()) {
            auto it = commandToBaseArgCount_.find(name);
            if (it != commandToBaseArgCount_.end()) {
                registerCommand(name, it->second, true);
                
                RCLCPP_INFO(node->get_logger(), 
                    "Registered variable command: %s (base count: %zu)", 
                    name.c_str(), it->second);
            } else {
                RCLCPP_WARN(node->get_logger(), 
                    "Variable command '%s' not found in any fixed-arg category", 
                    name.c_str());
            }
        }
    } else {
        RCLCPP_WARN(node->get_logger(), 
            "No commands found for key 'commands.variable_arg'");
    }
}

size_t CommandRegistry::getBaseArgCount(const std::string& command) const {
    auto it = commandToBaseArgCount_.find(command);
    if (it == commandToBaseArgCount_.end()) {
        throw std::runtime_error(
            fmt::format("Command '{}' not found in registry", command));
    }
    
    return it->second;
}

bool CommandRegistry::isVariable(const std::string& command) const {
    auto it = isVariableCommand_.find(command);
    if (it == isVariableCommand_.end()) {
        return false;
    }
    
    return it->second;
}

size_t CommandRegistry::getVariableBaseCount(const std::string& command) const {
    auto it = variableCommandBaseCount_.find(command);
    if (it == variableCommandBaseCount_.end()) {
        throw std::runtime_error(
            fmt::format("Variable command '{}' not found in registry", command));
    }
    
    return it->second;
}

void CommandRegistry::registerCommand(
    const std::string& command, size_t baseArgCount, bool isVariable) {
    
    commandToBaseArgCount_[command] = baseArgCount;
    isVariableCommand_[command] = isVariable;
    
    if (isVariable) {
        variableCommandBaseCount_[command] = baseArgCount;
    }
}

std::vector<std::pair<std::string, size_t>> CommandRegistry::getAllCommands() const {
    std::vector<std::pair<std::string, size_t>> result;
    
    for (const auto& [command, baseArgCount] : commandToBaseArgCount_) {
        result.emplace_back(command, baseArgCount);
    }
    
    return result;
}

}} // namespace worm_picker::parser