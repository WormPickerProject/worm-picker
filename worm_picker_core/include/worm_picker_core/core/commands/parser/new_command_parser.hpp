#pragma once

#include "worm_picker_core/core/result.hpp"
#include "worm_picker_core/core/commands/command_info.hpp"
#include "worm_picker_core/core/commands/parser/parser_types.hpp"
#include "worm_picker_core/core/commands/parser/command_registry.hpp"

namespace worm_picker {
namespace parser {

class NewCommandParser {
public:
    // Constructor
    explicit NewCommandParser(const rclcpp::Node::SharedPtr& node);
    
    // Parse a command string
    Result<CommandInfo> parse(const std::string& command);
    
private:
    CommandRegistry registry_;
    rclcpp::Logger logger_{rclcpp::get_logger("NewCommandParser")};
};

}} // namespace worm_picker::parser