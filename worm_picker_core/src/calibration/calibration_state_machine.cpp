// calibrations_state_machine.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/calibration/calibration_state_machine.hpp"

CalibrationStateMachine::CalibrationStateMachine(const rclcpp::Node::SharedPtr& node,
                                                 const std::shared_ptr<RobotController>& robot_controller)
    : node_(node),
      robot_controller_(robot_controller),
      state_(State::Idle),
      current_point_index_(0)
{
}

void CalibrationStateMachine::processCommand(const std::string& command,
                                             const std::shared_ptr<worm_picker_custom_msgs::srv::CalibrationCommand::Response>& response)
{
    if (state_ == State::Completed) {
        response->success = false;
        response->feedback = "Calibration already completed.";
        return;
    }

    if (command == "next") {
        if (state_ == State::Idle || state_ == State::AwaitingAdjustment) {
            moveToNextPoint();
            response->success = true;
            response->feedback = "Moved to next calibration point.";
        } else {
            response->success = false;
            response->feedback = "Cannot process 'next' command right now.";
        }
    } else if (command == "retry") {
        if (state_ == State::AwaitingAdjustment) {
            retryCurrentPoint();
            response->success = true;
            response->feedback = "Retrying current calibration point.";
        } else {
            response->success = false;
            response->feedback = "Cannot process 'retry' command right now.";
        }
    } else if (command == "record") {
        if (state_ == State::AwaitingAdjustment) {
            recordCurrentPosition();
            response->success = true;
            response->feedback = "Position recorded.";
        } else {
            response->success = false;
            response->feedback = "Cannot process 'record' command right now.";
        }
    } else {
        response->success = false;
        response->feedback = "Unknown command.";
    }
}

void CalibrationStateMachine::moveToNextPoint()
{
    if (robot_controller_->moveToPoint(current_point_index_)) {
        state_ = State::AwaitingAdjustment;
        RCLCPP_INFO(node_->get_logger(), "Moved to point %zu. Awaiting user adjustment.", current_point_index_);
    } else {
        RCLCPP_ERROR(node_->get_logger(), "Failed to move to point %zu.", current_point_index_);
        state_ = State::Idle;
    }
}

void CalibrationStateMachine::retryCurrentPoint()
{
    if (robot_controller_->moveToPoint(current_point_index_)) {
        state_ = State::AwaitingAdjustment;
        RCLCPP_INFO(node_->get_logger(), "Retried point %zu. Awaiting user adjustment.", current_point_index_);
    } else {
        RCLCPP_ERROR(node_->get_logger(), "Failed to retry point %zu.", current_point_index_);
        state_ = State::Idle;
    }
}

void CalibrationStateMachine::recordCurrentPosition()
{
    auto pose_opt = robot_controller_->getCurrentPose();
    if (pose_opt) {
        recorded_positions_.push_back(*pose_opt);
        current_point_index_++;
        if (current_point_index_ >= robot_controller_->getTotalPoints()) {
            state_ = State::Completed;
            RCLCPP_INFO(node_->get_logger(), "Calibration completed.");
        } else {
            state_ = State::Idle;
        }
    } else {
        RCLCPP_ERROR(node_->get_logger(), "Failed to record position. Invalid pose.");
    }
}
