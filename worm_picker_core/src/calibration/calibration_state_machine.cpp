// calibrations_state_machine.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/calibration/calibration_state_machine.hpp"
 
CalibrationStateMachine::CalibrationStateMachine(
    const rclcpp::Node::SharedPtr& node,
    const std::shared_ptr<RobotController>& robot_controller) 
    : node_{node},
      robot_controller_{robot_controller}, 
      command_handlers_{
          {Command::Next, [this](const std::optional<size_t>& idx) { 
            return handleMoveCommand(Command::Next, idx); }},
          {Command::Return, [this](const std::optional<size_t>& idx) { 
            return handleMoveCommand(Command::Return, idx); }},
          {Command::Record, [this](const std::optional<size_t>& idx) { 
            return handleRecordCommand(idx); }},
          {Command::Redo, [this](const std::optional<size_t>& idx) { 
            return handleRedoCommand(idx); }},
          {Command::Done, [this](const std::optional<size_t>& idx) { 
            return handleDoneCommand(idx); }}
      }
{
}

void CalibrationStateMachine::processCommand(const std::string& command_str, 
                                             CalibrationCommandResponsePtr response) 
{
    if (state_ == State::Completed) {
        response->success = false;
        response->feedback = "Calibration already completed.";
        return;
    }

    auto parsed = parseCommand(command_str);
    if (!parsed) {
        response->success = false;
        response->feedback = "Unknown command.";
        return;
    }

    if (!isCommandValidInState(parsed->command)) {
        response->success = false;
        response->feedback = "Invalid command for current state: " + command_str;
        return;
    }

    const auto result = command_handlers_.at(parsed->command)(parsed->index);
    response->success = result.success;
    response->feedback = result.feedback;
}

CalibrationStateMachine::OptionalCommand 
CalibrationStateMachine::parseCommand(const std::string& command_str) const
{
    std::istringstream iss(command_str);
    std::string cmd_token;
    if (!(iss >> cmd_token)) {
        return std::nullopt;
    }

    static const std::unordered_map<std::string, Command> COMMAND_MAP = {
        {"next", Command::Next},
        {"return", Command::Return},
        {"record", Command::Record},
        {"redo", Command::Redo},
        {"done", Command::Done}
    };

    auto it = COMMAND_MAP.find(cmd_token);
    if (it == COMMAND_MAP.end()) {
        return std::nullopt;
    }

    std::optional<size_t> idx;
    size_t temp_idx;
    if (iss >> temp_idx) {
        idx = temp_idx;
    }

    return ParsedCommand{it->second, idx};
}

bool CalibrationStateMachine::isCommandValidInState(Command command) const 
{
    switch (command) {
        case Command::Next:
            return state_ == State::Idle; 
        case Command::Return:
            return state_ == State::Idle || state_ == State::AwaitingAdjustment;
        case Command::Record:
            return state_ == State::AwaitingAdjustment || state_ == State::Reviewing; 
        case Command::Redo:
            return state_ == State::Reviewing; 
        case Command::Done:
            return state_ == State::Reviewing || state_ == State::Idle;
    }
    return false;
}

CalibrationStateMachine::CommandResult 
CalibrationStateMachine::handleMoveCommand(Command command, const std::optional<size_t>&)
{
    if (!moveRobotToPoint(current_point_index_)) {
        return {false, fmt::format("Failed to {} point {}.", 
            command == Command::Next ? "move to next" : "return to current",
            current_point_index_)};
    }
    
    return {true, fmt::format("{} point {}.", 
        command == Command::Next ? "Moved to next" : "Returning to current",
        current_point_index_)};
}

CalibrationStateMachine::CommandResult 
CalibrationStateMachine::handleRedoCommand(const std::optional<size_t>& idx)
{
    if (!idx) {
        return {false, "No index specified for redo command."};
    }

    size_t point_idx = *idx;
    if (point_idx >= recorded_positions_.size()) {
        return {false, fmt::format(
            "Invalid index {} for re-recording. Please choose an index between 0-{}.",
            point_idx, 
            recorded_positions_.size() - 1)};
    }

    if (!moveRobotToPoint(point_idx)) {
        return {false, fmt::format("Failed to move to point {} for re-recording.", point_idx)};
    }

    return {true, fmt::format("Ready to re-record point {}. Use 'record' when ready.", point_idx)};
}

CalibrationStateMachine::CommandResult 
CalibrationStateMachine::handleRecordCommand(const std::optional<size_t>& idx)
{
    auto pose = robot_controller_->getCurrentPose();
    if (!pose) {
        return {false, "Failed to record position. Invalid pose."};
    }

    if (state_ == State::Reviewing && idx.has_value()) {
        return handlePointRerecording(*pose, *idx);
    }

    return handleNewPointRecording(*pose);
}

CalibrationStateMachine::CommandResult 
CalibrationStateMachine::handleDoneCommand(const std::optional<size_t>&)
{
    size_t home_index = robot_controller_->getTotalPoints() - 1;
    if (!robot_controller_->moveToPoint(home_index)) {
        updateState(State::Idle);
        return {false, "Failed to move to home position."};
    }

    updateState(State::Completed);
    return {true, "Calibration completed. Robot moved to home position."};
}

CalibrationStateMachine::CommandResult 
CalibrationStateMachine::handlePointRerecording(const Pose& pose, size_t idx) 
{
    if (idx >= recorded_positions_.size()) {
        return {false, fmt::format("Invalid point index {}. Must be between 0-{}.", 
                                 idx, recorded_positions_.size() - 1)};
    }

    recorded_positions_[idx] = pose;
    return {true, fmt::format(
        "Point #{} has been re-recorded. Would you like to redo another point or 'done'?",
        idx)};
}

CalibrationStateMachine::CommandResult 
CalibrationStateMachine::handleNewPointRecording(const Pose& pose) 
{
    recorded_positions_.push_back(pose);
    current_point_index_++;

    if (current_point_index_ == robot_controller_->getTotalPoints() - 1) {
        updateState(State::Reviewing);
        return {true, "All points recorded. Would you like to re-record any point? "
                      "Use 'redo <index>' to re-record, or 'done' to finalize."};
    }

    updateState(State::Idle);
    return {true, "Position recorded."};
}

bool CalibrationStateMachine::moveRobotToPoint(size_t point_index) 
{
    if (!robot_controller_->moveToPoint(point_index)) {
        log(rclcpp::Logger::Level::Error, "Failed to move to point {}", point_index);
        return false;
    }

    if (state_ != State::Reviewing) {
        updateState(State::AwaitingAdjustment);
    }
    log(rclcpp::Logger::Level::Info, "Moved to point {}. Awaiting adjustment", point_index);
    return true;
}

void CalibrationStateMachine::updateState(State new_state) 
{
    if (state_ != new_state) {
        log(rclcpp::Logger::Level::Info, "State transition: {} -> {}", 
            static_cast<int>(state_), static_cast<int>(new_state));
        state_ = new_state;
    }
}

const CalibrationStateMachine::PoseVector& CalibrationStateMachine::getRecordedPositions() const 
{ 
    return recorded_positions_; 
}

CalibrationStateMachine::State CalibrationStateMachine::getCurrentState() const 
{ 
    return state_; 
}
