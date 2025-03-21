// control_command_parser.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/core/commands/parser/control_command_parser.hpp"

ControlCommandParser::ControlCommandParser(const rclcpp::Node::SharedPtr& node)
    : logger_(node->get_logger())
{
    registry_.loadFromNode(node);
    mainParser_ = worm_picker::parser::CommandBuilder::createMainParser(registry_);
    
    RCLCPP_INFO(logger_, "Initialized ControlCommandParser with %zu commands", 
        registry_.getAllCommands().size());
}

Result<CommandInfo> ControlCommandParser::parse(const std::string& command)
{
    try {
        worm_picker::parser::ParserInput input(command);
        auto result = mainParser_(input);
        
        if (result.isSuccess()) {
            auto [info, _] = result.value();
            return Result<CommandInfo>::success(info);
        } else {
            std::ostringstream oss;
            oss << "Failed to parse command '" << command << "': " << result.error();
            return Result<CommandInfo>::error(oss.str());
        }
    } catch (const std::exception& e) {
        std::ostringstream oss;
        oss << "Exception while parsing command '" << command << "': " << e.what();
        return Result<CommandInfo>::error(oss.str());
    }
}