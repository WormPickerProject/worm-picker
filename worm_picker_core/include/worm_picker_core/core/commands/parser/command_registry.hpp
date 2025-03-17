#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <rclcpp/rclcpp.hpp>

namespace worm_picker {
namespace parser {

class CommandRegistry {
public:
    // Load commands from node parameters
    void loadFromNode(const rclcpp::Node::SharedPtr& node);
    
    // Get the base argument count for a command
    size_t getBaseArgCount(const std::string& command) const;
    
    // Check if a command is a variable argument command
    bool isVariable(const std::string& command) const;
    
    // Get the base argument count per group for a variable command
    size_t getVariableBaseCount(const std::string& command) const;
    
    // Register a new command
    void registerCommand(const std::string& command, size_t baseArgCount, bool isVariable = false);
    
    // Get all registered commands
    std::vector<std::pair<std::string, size_t>> getAllCommands() const;
    
private:
    std::unordered_map<std::string, size_t> commandToBaseArgCount_;
    std::unordered_map<std::string, bool> isVariableCommand_;
    std::unordered_map<std::string, size_t> variableCommandBaseCount_;
};

}} // namespace worm_picker::parser