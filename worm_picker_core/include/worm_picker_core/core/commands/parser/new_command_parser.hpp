#pragma once

#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/core/result.hpp"
#include "worm_picker_core/core/commands/command_info.hpp"
#include "worm_picker_core/core/commands/parser/command_parser.hpp"
// #include "worm_picker_core/core/commands/parser/parser_types.hpp"
// #include "worm_picker_core/core/commands/parser/command_registry.hpp"

// namespace worm_picker {
// namespace parser {

// class NewCommandParser {
// public:
//     // Constructor
//     explicit NewCommandParser(const rclcpp::Node::SharedPtr& node);
    
//     // Parse a command string
//     Result<CommandInfo> parse(const std::string& command);
    
// private:
//     CommandRegistry registry_;
//     rclcpp::Logger logger_{rclcpp::get_logger("NewCommandParser")};
// };

// }} // namespace worm_picker::parser

namespace worm_picker::parser {

    class NewCommandParser {
    public:
        explicit NewCommandParser(const rclcpp::Node::SharedPtr& node) {
            registry_.loadFromNode(node);
            mainParser_ = CommandBuilder::createMainParser(registry_);
            
            RCLCPP_INFO(logger_, "Initialized NewCommandParser with %zu commands", 
                registry_.getAllCommands().size());
        }
        
        Result<CommandInfo> parse(const std::string& command) {
            try {
                ParserInput input(command);
                auto result = mainParser_(input);
                
                if (result.isSuccess()) {
                    auto [info, _] = result.value();
                    return Result<CommandInfo>::success(info);
                } else {
                    return Result<CommandInfo>::error(result.error());
                }
            } catch (const std::exception& e) {
                return Result<CommandInfo>::error(
                    std::string("Exception during parsing: ") + e.what());
            }
        }
    
    private:
        CommandRegistry registry_;
        Parser<CommandInfo> mainParser_;
        rclcpp::Logger logger_{rclcpp::get_logger("NewCommandParser")};
    };
    
    } // namespace worm_picker::parser