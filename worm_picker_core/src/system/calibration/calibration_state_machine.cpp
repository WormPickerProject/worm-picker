// calibrations_state_machine.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/system/calibration/calibration_state_machine.hpp"
 
CalibrationStateMachine::CalibrationStateMachine(
    const rclcpp::Node::SharedPtr& node,
    const std::shared_ptr<RobotController>& robot_controller) 
    : node_{node},
      robot_controller_{robot_controller}, 
      command_handlers_{
          {Command::Next, [this](const std::optional<std::string>& key) { 
            return handleMoveCommand(Command::Next, key); }},
          {Command::Return, [this](const std::optional<std::string>& key) { 
            return handleMoveCommand(Command::Return, key); }},
          {Command::Record, [this](const std::optional<std::string>& key) { 
            return handleRecordCommand(key); }},
          {Command::Redo, [this](const std::optional<std::string>& key) { 
            return handleRedoCommand(key); }},
          {Command::Done, [this](const std::optional<std::string>& key) { 
            return handleDoneCommand(key); }}
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

    const auto result = command_handlers_.at(parsed->command)(parsed->key);
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

    std::string possible_key;
    std::optional<std::string> key;
    if (iss >> possible_key) {
        key = possible_key;
    }

    return ParsedCommand{it->second, key};
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
CalibrationStateMachine::handleMoveCommand(Command command, const std::optional<std::string>&)
{
    const auto& order = robot_controller_->getPointsOrder();

    const auto& current_point = recorded_positions_.empty() 
        ? order.front() 
        : recorded_positions_.rbegin()->first;
        
    const auto& next_unrecorded_point = *std::ranges::find_if(order,
        [this](const auto& key) { return !recorded_positions_.contains(key); });

    const auto [action, point] = command == Command::Return
        ? std::pair{"Returned to", current_point}
        : std::pair{"Moved to", next_unrecorded_point};

    const bool success = moveRobotToPoint(point);

    return {
        success,
        success ? fmt::format("{} point '{}'.", action, point)
                : fmt::format("Failed to move to point '{}'.", point)
    };
}

CalibrationStateMachine::CommandResult 
CalibrationStateMachine::handleRedoCommand(const std::optional<std::string>& key)
{
    if (!key) {
        return {false, "No key specified for redo command."};
    }

    const auto points_map = robot_controller_->getPointsMap();
    if (points_map.find(*key) == points_map.end()) {
        return {false, fmt::format(
            "Invalid key '{}' for re-recording. Please choose a known key.", *key)};
    }

    const std::string& point_key = *key;
    if (!moveRobotToPoint(point_key)) {
        return {false, fmt::format("Failed to move to point '{}' for re-recording.", point_key)};
    }

    return {
        true, fmt::format("Ready to re-record point '{}'. Use 'record' when ready.", point_key)};
}

CalibrationStateMachine::CommandResult 
CalibrationStateMachine::handleRecordCommand(const std::optional<std::string>& key)
{
    auto pose = robot_controller_->getCurrentPose();
    if (!pose) {
        return {false, "Failed to record position. Invalid pose."};
    }

    if (state_ == State::Reviewing && key.has_value()) {
        return handlePointRerecording(*pose, *key);
    }

    return handleNewPointRecording(*pose);
}

CalibrationStateMachine::CommandResult 
CalibrationStateMachine::handleDoneCommand(const std::optional<std::string>&)
{
    const auto& order = robot_controller_->getPointsOrder();
    const std::string& home_key = order.back();
    if (!robot_controller_->moveToPoint(home_key)) {
        updateState(State::Idle);
        return {false, "Failed to move to home position."};
    }

    updateState(State::Completed);
    return {true, "Calibration completed. Robot moved to home position."};
}

CalibrationStateMachine::CommandResult 
CalibrationStateMachine::handlePointRerecording(const Pose& pose, const std::string& key) 
{
    recorded_positions_[key] = pose;
    return {true, fmt::format(
        "Point '{}' has been re-recorded. Would you like to redo another point or 'done'?",
        key)};
}

CalibrationStateMachine::CommandResult 
CalibrationStateMachine::handleNewPointRecording(const Pose& pose) 
{
    const auto& order = robot_controller_->getPointsOrder();
    
    const auto& next_unrecorded_point = *std::ranges::find_if(order,
        [this](const auto& key) { return !recorded_positions_.contains(key); });

    recorded_positions_[next_unrecorded_point] = pose;

    const bool isComplete = recorded_positions_.size() == order.size() - 1;
    updateState(isComplete ? State::Reviewing : State::Idle);

    return {
        true,
        isComplete 
            ? "All points recorded. Use 'redo <key>' to re-record, or 'done' to finalize."
            : fmt::format("Position recorded for point '{}'.", next_unrecorded_point)
    };
}

bool CalibrationStateMachine::moveRobotToPoint(const std::string& point_key) 
{
    if (!robot_controller_->moveToPoint(point_key)) {
        log(rclcpp::Logger::Level::Error, "Failed to move to point {}", point_key);
        return false;
    }

    if (state_ != State::Reviewing) {
        updateState(State::AwaitingAdjustment);
    }
    log(rclcpp::Logger::Level::Info, "Moved to point {}. Awaiting adjustment", point_key);
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

const std::map<std::string, CalibrationStateMachine::Pose>& 
CalibrationStateMachine::getRecordedPositions() const 
{ 
    return recorded_positions_; 
}

CalibrationStateMachine::State CalibrationStateMachine::getCurrentState() const 
{ 
    return state_; 
}