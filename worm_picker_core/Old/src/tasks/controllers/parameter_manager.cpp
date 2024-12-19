// parameter_manager.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tasks/controllers/parameter_manager.hpp"

const std::array<ParameterManager::ParameterDefinition, 15> ParameterManager::PARAMETER_DEFINITIONS{{
    {
        "workstation_config_file",
        rclcpp::ParameterValue("/worm-picker/worm_picker_description/program_data/data_files/workstation_data.json"),
        "Path to the workstation configuration file"
    },
    {
        "hotel_config_file",
        rclcpp::ParameterValue("/worm-picker/worm_picker_description/program_data/data_files/hotel_data.json"),
        "Path to the hotel configuration file"
    },
    {
        "defined_stages_file",
        rclcpp::ParameterValue("/worm-picker/worm_picker_description/program_data/data_files/defined_stages.json"),
        "Path to the defined stages configuration"
    },
    {
        "defined_tasks_file",
        rclcpp::ParameterValue("/worm-picker/worm_picker_description/program_data/data_files/defined_tasks.json"),
        "Path to the defined tasks configuration"
    },
    {
        "timer_log_path",
        rclcpp::ParameterValue("/worm-picker/worm_picker_description/program_data/timer_log"),
        "Path to store timer logs"
    },
    {
        "exec_task_action_name",
        rclcpp::ParameterValue("/execute_task_solution"),
        "Name of the task execution action"
    },
    {
        "task_command_service_name",
        rclcpp::ParameterValue("/task_command"),
        "Name of the task command service"
    },
    {
        "plate_mode_command",
        rclcpp::ParameterValue("plateMode"),
        "Command for plate mode operation"
    },
    {
        "worm_mode_command",
        rclcpp::ParameterValue("wormMode"),
        "Command for worm mode operation"
    },
    {
        "end_effector",
        rclcpp::ParameterValue("eoat_tcp"),
        "Current end effector for WormPicker (Default: eoat_tcp)"
    },
    {
        "plate_end_factor",
        rclcpp::ParameterValue("eoat_tcp"),
        "End effector factor for plate mode"
    },
    {
        "worm_end_factor",
        rclcpp::ParameterValue("wormpick_tcp"),
        "End effector factor for worm mode"
    },
    {
        "action_server_timeout_sec",
        rclcpp::ParameterValue(3),
        "Timeout for action server operations in seconds"
    },
    {
        "max_retries",
        rclcpp::ParameterValue(10),
        "Maximum number of retry attempts"
    },
    {
        "planning_attempts",
        rclcpp::ParameterValue(5),
        "Number of planning attempts"
    }
}};

ParameterManager::ParameterManager(const NodePtr& node) 
    : node_{node}
{
    declareParameters();
}

void ParameterManager::declareParameters() 
{
    for (const auto& param : PARAMETER_DEFINITIONS) {
        node_->declare_parameter(
            param.name,
            param.value,
            rcl_interfaces::msg::ParameterDescriptor().set__description(param.description)
        );
    }
}
