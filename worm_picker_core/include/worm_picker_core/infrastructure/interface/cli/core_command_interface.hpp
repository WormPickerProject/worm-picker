// core_command_interface.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <worm_picker_custom_msgs/srv/task_command.hpp>
#include "worm_picker_core/core/result.hpp"

namespace worm_picker {

class PointIdentifier {
public:
    explicit PointIdentifier(std::string value);
    const std::string& value() const noexcept { return value_; }
    static bool isValid(const std::string& value);

private:
    std::string value_;
};

class CoreCommandInterface {
public:
    using TaskCommand = worm_picker_custom_msgs::srv::TaskCommand;

    explicit CoreCommandInterface(rclcpp::Node::SharedPtr node);
    ~CoreCommandInterface();
    void runCommandLoop();

private:
    class Implementation;
    std::unique_ptr<Implementation> impl_;

    Result<void> processUserCommand(const std::string& command);
    Result<void> handleMoveAllPoints();
    Result<void> handleMoveRowPoints(const std::string& row);
    Result<void> handleMoveAllPlates();
    Result<void> handleMoveAllPlatesRandom();
    Result<void> handleMoveRowPlates(const std::string& row);
    Result<void> executeMovementSequence(const std::vector<PointIdentifier>& points);
    bool isValidRow(const std::string& row) const;
    std::vector<PointIdentifier> getRowPoints(char row) const;
};

} // namespace worm_picker