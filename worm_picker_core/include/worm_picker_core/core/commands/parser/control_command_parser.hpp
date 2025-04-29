// control_command_parser.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/core/result.hpp"
#include "worm_picker_core/core/commands/command_info.hpp"
#include "worm_picker_core/core/commands/parser/command_parser.hpp"

/**
 * @brief High-level command parser for robot control commands
 * 
 * This class provides a convenient interface for parsing robot command strings
 * using the underlying command parser infrastructure.
 */
class ControlCommandParser {
public:
    /**
     * @brief Construct a new command parser instance
     * @param node ROS2 node to load command configurations from
     */
    explicit ControlCommandParser(const rclcpp::Node::SharedPtr& node);
    
    /**
     * @brief Parse a command string into a CommandInfo object
     * @param command Command string to parse
     * @return Result object containing either a parsed CommandInfo or an error message
     */
    Result<CommandInfo> parse(const std::string& command);
    
private:
    worm_picker::parser::CommandRegistry registry_;
    worm_picker::parser::Parser<CommandInfo> mainParser_;
    rclcpp::Logger logger_{rclcpp::get_logger("ControlCommandParser")};
};