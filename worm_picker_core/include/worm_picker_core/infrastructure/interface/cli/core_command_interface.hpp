// core_command_interface.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#ifndef CORE_COMMAND_INTERFACE_HPP
#define CORE_COMMAND_INTERFACE_HPP

#include <rclcpp/rclcpp.hpp>
#include <worm_picker_custom_msgs/srv/task_command.hpp>

namespace worm_picker {

class PointIdentifier {
public:
    explicit PointIdentifier(std::string value);
    const std::string& value() const noexcept { return value_; }
    static bool isValid(const std::string& value);

private:
    std::string value_;
};

template<typename T>
class Result {
public:
    static Result<T> success(T value) {
        return Result(std::move(value));
    }

    static Result<T> error(std::string message) {
        return Result(std::move(message));
    }
    
    bool isSuccess() const {
        return std::holds_alternative<T>(value_);
    }
    
    const T& value() const& {
        return std::get<T>(value_);
    }
    
    const std::string& error() const& {
        return std::get<std::string>(value_);
    }

private:
    std::variant<T, std::string> value_;
    explicit Result(T value) : value_(std::move(value)) {}
    explicit Result(std::string error) : value_(std::move(error)) {}
};

template<>
class Result<void> {
public:
    static Result<void> success() {
        return Result<void>(true);
    }
    
    static Result<void> error(std::string message) {
        return Result<void>(std::move(message));
    }
    
    bool isSuccess() const {
        return success_;
    }
    
    const std::string& error() const& {
        if (isSuccess()) {
            throw std::runtime_error("Cannot access error on successful result");
        }
        return error_message_;
    }

private:
    bool success_;
    std::string error_message_;
    explicit Result(bool success) : success_(success) {}
    explicit Result(std::string error) : success_(false), error_message_(std::move(error)) {}
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

#endif // CORE_COMMAND_INTERFACE_HPP