// calibrations_state_machine.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef CALIBRATION_STATE_MACHINE_HPP
#define CALIBRATION_STATE_MACHINE_HPP

#include <fmt/format.h>
#include <rclcpp/rclcpp.hpp>
#include <worm_picker_custom_msgs/srv/calibration_command.hpp>
#include "worm_picker_core/calibration/robot_controller.hpp"

class CalibrationStateMachine {
public:
    using Pose = geometry_msgs::msg::PoseStamped;
    using PoseVector = std::vector<Pose>;
    using CalibrationCommandService = worm_picker_custom_msgs::srv::CalibrationCommand;
    using CalibrationCommandResponse = CalibrationCommandService::Response;
    using CalibrationCommandResponsePtr = std::shared_ptr<CalibrationCommandResponse>;
    
    enum class State { Idle, AwaitingAdjustment, Reviewing, Completed };
    enum class Command { Next, Return, Record, Redo, Done };

    struct CommandResult {
        bool success;
        std::string feedback;
    };

    struct ParsedCommand {
        Command command;
        std::optional<size_t> index;
    };

    CalibrationStateMachine(const rclcpp::Node::SharedPtr& node,
                            const std::shared_ptr<RobotController>& robot_controller);
    void processCommand(const std::string& command, CalibrationCommandResponsePtr response);

    const PoseVector& getRecordedPositions() const;
    State getCurrentState() const;

private:
    using OptionalCommand = std::optional<ParsedCommand>;
    using CommandHandler = std::function<CommandResult(const std::optional<size_t>&)>;
    using CommandHandlerMap = std::unordered_map<Command, CommandHandler>;

    OptionalCommand parseCommand(const std::string& command_str) const;
    bool isCommandValidInState(Command command) const;

    CommandResult handleMoveCommand(Command command, const std::optional<size_t>& idx);
    CommandResult handleRedoCommand(const std::optional<size_t>& idx);
    CommandResult handleRecordCommand(const std::optional<size_t>& idx);
    CommandResult handleDoneCommand(const std::optional<size_t>& idx);

    CommandResult handlePointRerecording(const Pose& pose, size_t idx);
    CommandResult handleNewPointRecording(const Pose& pose);

    bool moveRobotToPoint(size_t point_index);
    void updateState(State new_state);

    template<typename... Args>
    void log(rclcpp::Logger::Level level, fmt::format_string<Args...> format, Args&&... args) const 
    {
        auto message = fmt::format(format, std::forward<Args>(args)...);
        switch (level) {
            case rclcpp::Logger::Level::Info:
                RCLCPP_INFO(node_->get_logger(), "%s", message.c_str());
                break;
            case rclcpp::Logger::Level::Warn:
                RCLCPP_WARN(node_->get_logger(), "%s", message.c_str());
                break;
            case rclcpp::Logger::Level::Error:
                RCLCPP_ERROR(node_->get_logger(), "%s", message.c_str());
                break;
            default:
                RCLCPP_INFO(node_->get_logger(), "[Unknown] %s", message.c_str());
                break;
        }
    }

    rclcpp::Node::SharedPtr node_;
    std::shared_ptr<RobotController> robot_controller_;
    State state_{State::Idle};
    size_t current_point_index_{0};
    PoseVector recorded_positions_;
    const CommandHandlerMap command_handlers_;
};

#endif // CALIBRATION_STATE_MACHINE_HPP
