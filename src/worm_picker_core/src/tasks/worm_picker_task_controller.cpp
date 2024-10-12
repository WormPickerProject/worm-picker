// worm_picker_task_controller.cpp
//
// Copyright (c) 2024 Logan Kaising
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "worm_picker_core/tasks/worm_picker_task_controller.hpp"

WormPickerTaskController::WormPickerTaskController(const rclcpp::NodeOptions& options) 
    : worm_picker_node_{ std::make_shared<rclcpp::Node>("worm_picker_task_controller", options) },
      task_factory_{ std::make_shared<TaskFactory>(worm_picker_node_) } 
{
    setupService();
}

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr WormPickerTaskController::getNodeBaseInterface() 
{
    return worm_picker_node_->get_node_base_interface();
}

void WormPickerTaskController::setupService() 
{
    execute_task_action_client_ = rclcpp_action::create_client<
        moveit_task_constructor_msgs::action::ExecuteTaskSolution>(
            worm_picker_node_, 
            "/execute_task_solution"
    );

    execute_task_action_client_->wait_for_action_server(
        std::chrono::seconds(10)
    );

    task_command_service_ = worm_picker_node_->create_service<
        worm_picker_custom_msgs::srv::TaskCommand>(
            "/task_command",
            [this](
                const std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Request> request, 
                std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Response> response
            ) {
                handleTaskCommand(request, response);
            }
    );
}

void WormPickerTaskController::handleTaskCommand(
    const std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Request> request,
    std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Response> response) 
{
    RCLCPP_INFO(worm_picker_node_->get_logger(), "Received command: %s", request->command.c_str());
    response->success = doTask(request->command);
}

bool WormPickerTaskController::doTask(const std::string& command) 
{
    if (!rclcpp::ok()) return false;

    current_task_ = task_factory_->createTask(command);
    current_task_.init();

    if (!current_task_.plan(5)) {
        RCLCPP_ERROR(worm_picker_node_->get_logger(), "Task planning failed");
        return false;
    }

    current_task_.introspection().publishSolution(*current_task_.solutions().front());
    auto result = current_task_.execute(*current_task_.solutions().front());

    if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
        RCLCPP_ERROR(worm_picker_node_->get_logger(), "Task execution failed");
        return false;
    } else {
        return true; 
    }
}