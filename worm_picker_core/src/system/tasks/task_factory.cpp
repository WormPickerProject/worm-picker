// task_factory.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/system/tasks/task_generator.hpp"
#include "worm_picker_core/system/tasks/generation/generate_relative_movement_task.hpp"
#include "worm_picker_core/system/tasks/generation/generate_absolute_movement_task.hpp"
#include "worm_picker_core/system/tasks/task_factory.hpp"
#include "worm_picker_core/infrastructure/parsers/defined_tasks_parser.hpp"
#include "worm_picker_core/core/tasks/stages/move_relative_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_joint_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_point_data.hpp"
#include "worm_picker_core/utils/parameter_utils.hpp"

TaskFactory::TaskFactory(const NodePtr& node)
  : node_(node),
    command_parser_(std::make_unique<CommandParser>(node))
{
  initializeTaskMap();
}

void TaskFactory::initializeTaskMap() 
{
    const auto& workstation = loadWorkstationData();
    const auto& hotel = loadHotelData();
    loadDefinedTasks(workstation, hotel);
    // logTaskMap();
}

TaskFactory::WorkstationDataMap TaskFactory::loadWorkstationData() 
{
    auto ws_config_path = param_utils::getParameter<std::string>(node_, "config_files.workstation");
    WorkstationDataParser workstation_parser{*ws_config_path};
    return(workstation_parser.getWorkstationDataMap());
}

TaskFactory::HotelDataMap TaskFactory::loadHotelData() 
{
    auto hotel_config_path = param_utils::getParameter<std::string>(node_, "config_files.hotel");
    HotelDataParser hotel_parser{*hotel_config_path};
    return(hotel_parser.getHotelDataMap());
}

void TaskFactory::loadDefinedTasks(const WorkstationDataMap& workstation, const HotelDataMap& hotel)
{
    auto defined_stages_path = param_utils::getParameter<std::string>(node_, "config_files.stages");
    auto defined_tasks_path  = param_utils::getParameter<std::string>(node_, "config_files.tasks");

    DefinedTasksGenerator defined_tasks_parser{*defined_stages_path, *defined_tasks_path};
    const auto& defined_tasks_map = defined_tasks_parser.getDefinedTasksMap();

    TaskGenerator task_plans{workstation, hotel};
    const auto& generated_task_map = task_plans.getGeneratedTaskPlans();

    task_data_map_.insert(defined_tasks_map.begin(), defined_tasks_map.end());
    task_data_map_.insert(generated_task_map.begin(), generated_task_map.end());
}

Result<TaskFactory::Task> TaskFactory::createTask(const std::string& command) 
{
    auto task = createBaseTask(command);
    task.add(std::make_unique<CurrentStateStage>("current"));

    auto parseCommand = [&]() -> Result<CommandInfo> {
        return command_parser_->parse(command);
    };
    auto getTaskData = [&](const CommandInfo& info) -> Result<TaskData> {
        // Temporary command info logging
        auto logger = rclcpp::get_logger("TaskFactory");
        RCLCPP_INFO(logger, "Command Info:");
        RCLCPP_INFO(logger, "  Base Command: %s", info.getBaseCommand().c_str());

        std::string args_str;
        for (const auto& arg : info.getArgs()) {
            args_str += arg + ", ";
        }
        if (!args_str.empty()) args_str.resize(args_str.size() - 2);
        RCLCPP_INFO(logger, "  Arguments: %s", args_str.c_str());

        if (info.getSpeedOverride()) {
            auto speed = info.getSpeedOverride().value();
            RCLCPP_INFO(logger, "  Speed Override: first = %f, second = %f", speed.first, speed.second);
        } else {
            RCLCPP_INFO(logger, "  Speed Override: none");
        }

        RCLCPP_INFO(logger, "  Base Command Key: %s", info.getBaseCommandKey().c_str());
        RCLCPP_INFO(logger, "  Base Args Amount: %zu", info.getBaseArgsAmount());
        // End of temporary command info logging
        
        return fetchTaskData(info); 
    };
    auto configureTask = [&](const TaskData& task_data) -> Task {
        return configureTaskWithStages(std::move(task), task_data, command);
    };

    return parseCommand()
        .flatMap(getTaskData)
        .map(configureTask);
}

TaskFactory::Task TaskFactory::createBaseTask(const std::string& command) 
{
    Task task;
    task.stages()->setName(command);
    task.loadRobotModel(node_);

    task.setProperty("group", "gp4_arm");
    auto ee_link = param_utils::getParameter<std::string>(node_, "end_effectors.current_factor");
    if (ee_link) {
        task.setProperty("ik_frame", *ee_link);
    }

    TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = { "follow_joint_trajectory" };
    task.setProperty("trajectory_execution_info", execution_info);

    return task;
}

Result<TaskData> TaskFactory::fetchTaskData(const CommandInfo& info) 
{
    auto fetchedTask = [&]() -> Result<TaskData> {
        if (info.getBaseCommand() == "moveRelative") {
            return GenerateRelativeMovementTask::parseCommand(info.getArgs());
        } else if (info.getBaseCommand() == "moveAbsolutePos" ||
                   info.getBaseCommand() == "moveAbsolutePose") {
            return GenerateAbsoluteMovementTask::parseCommand(node_, info);
        }
        auto it = task_data_map_.find(info.getBaseCommandKey());
        if (it == task_data_map_.end()) {
            return Result<TaskData>::error(
                fmt::format("Command '{}' not found", info.getBaseCommand()));
        }
        return Result<TaskData>::success(it->second);
    };

    return fetchedTask().flatMap([&](TaskData task) -> Result<TaskData> {
        if (info.getSpeedOverride()) {
            applySpeedOverrides(task, *info.getSpeedOverride());
        }
        return Result<TaskData>::success(task);
    });
}

void TaskFactory::applySpeedOverrides(TaskData& task_data, const SpeedOverride& override) 
{
    auto [velocity, acceleration] = override;
    for (auto& stage : task_data.getStages()) {
        if (auto* move_base = dynamic_cast<MovementDataBase*>(stage.get())) {
            move_base->setVelocityScalingFactor(velocity);
            move_base->setAccelerationScalingFactor(acceleration);
        }
    }
}

TaskFactory::Task TaskFactory::configureTaskWithStages(Task task, 
                                                       const TaskData& task_data,
                                                       const std::string& command)
{
    for (int stage_index = 1; const auto& stage_ptr : task_data.getStages()) {
        auto stage = stage_ptr->createStage(fmt::format("stage_{}", stage_index++), node_);
        task.add(std::move(stage));
    }
    
    logCreatedTask(command, task_data);
    return task;
}

const std::unordered_map<std::string, TaskData>& TaskFactory::getTaskDataMap() const
{
    return task_data_map_;
}

void TaskFactory::logTaskMap()
{
    auto logger = rclcpp::get_logger("TaskFactory");

    RCLCPP_INFO(logger, "************************************************************************");
    RCLCPP_INFO(logger, "* Task Data Map Contents:");

    for (const auto& task_entry : task_data_map_) {
        const std::string& task_name = task_entry.first;
        const TaskData& task_data = task_entry.second;

        RCLCPP_INFO(logger, "* Task '%s' Stages:", task_name.c_str());

        int stage_number = 1;
        for (const auto& stage_ptr : task_data.getStages()) {
            StageType stage_type = stage_ptr->getType();
            std::string stage_type_str;

            switch (stage_type) {
                case StageType::MOVE_TO_POINT: stage_type_str = "MOVE_TO_POINT"; break;
                case StageType::MOVE_TO_CIRCLE: stage_type_str = "MOVE_TO_CIRCLE"; break;
                case StageType::MOVE_TO_JOINT: stage_type_str = "MOVE_TO_JOINT"; break;
                case StageType::MOVE_RELATIVE: stage_type_str = "MOVE_RELATIVE"; break;
                default: stage_type_str = "UNKNOWN"; break;
            }

            auto formatNumber = [](double value) -> std::string {
                char buffer[16];
                snprintf(buffer, sizeof(buffer), "%s%0.4f", (value >= 0 ? " " : ""), value);
                return std::string(buffer);
            };

            auto formatVelAcc = [](double value) -> std::string {
                char buffer[16];
                snprintf(buffer, sizeof(buffer), "%.4f", value);
                return std::string(buffer);
            };

            int stage_num_len = std::to_string(stage_number).length();
            std::string continuation_indent(28 + (stage_num_len - 1), ' ');

            if (stage_type == StageType::MOVE_TO_POINT) {
                auto move_to_point_data = std::dynamic_pointer_cast<MoveToPointData>(stage_ptr);
                if (move_to_point_data) {
                    RCLCPP_INFO(logger, "*   [Stage %d] %s: Pos(%s, %s, %s)", 
                        stage_number,
                        stage_type_str.c_str(),
                        formatNumber(move_to_point_data->getX()).c_str(),
                        formatNumber(move_to_point_data->getY()).c_str(),
                        formatNumber(move_to_point_data->getZ()).c_str());
                    RCLCPP_INFO(logger, "*%sOri(%s, %s, %s, %s)",
                        continuation_indent.c_str(),
                        formatNumber(move_to_point_data->getQX()).c_str(),
                        formatNumber(move_to_point_data->getQY()).c_str(),
                        formatNumber(move_to_point_data->getQZ()).c_str(),
                        formatNumber(move_to_point_data->getQW()).c_str());
                    RCLCPP_INFO(logger, "*%sVel: %s; Acc: %s",
                        continuation_indent.c_str(),
                        formatVelAcc(move_to_point_data->getVelocityScalingFactor()).c_str(),
                        formatVelAcc(move_to_point_data->getAccelerationScalingFactor()).c_str());
                }
            } else if (stage_type == StageType::MOVE_TO_CIRCLE) {
                // TODO: Implement logging for MOVE_TO_CIRCLE
            } else if (stage_type == StageType::MOVE_TO_JOINT) {
                auto move_to_joint_data = std::dynamic_pointer_cast<MoveToJointData>(stage_ptr);
                if (move_to_joint_data) {
                    std::stringstream joints_ss;
                    joints_ss << "Joints(";
                    bool first = true;
                    for (const auto& joint_entry : move_to_joint_data->getJointPositions()) {
                        if (!first) joints_ss << ", ";
                        joints_ss << formatNumber(joint_entry.second);
                        first = false;
                    }
                    joints_ss << ")";
                    
                    RCLCPP_INFO(logger, "*   [Stage %d] %s: %s",
                        stage_number,
                        stage_type_str.c_str(),
                        joints_ss.str().c_str());
                    RCLCPP_INFO(logger, "*%sVel: %s; Acc: %s",
                        continuation_indent.c_str(),
                        formatVelAcc(move_to_joint_data->getVelocityScalingFactor()).c_str(),
                        formatVelAcc(move_to_joint_data->getAccelerationScalingFactor()).c_str());
                }
            } else if (stage_type == StageType::MOVE_RELATIVE) {
                auto move_relative_data = std::dynamic_pointer_cast<MoveRelativeData>(stage_ptr);
                if (move_relative_data) {
                    RCLCPP_INFO(logger, "*   [Stage %d] %s: Delta(%s, %s, %s)",
                        stage_number,
                        stage_type_str.c_str(),
                        formatNumber(move_relative_data->getDX()).c_str(),
                        formatNumber(move_relative_data->getDY()).c_str(),
                        formatNumber(move_relative_data->getDZ()).c_str());
                    RCLCPP_INFO(logger, "*%sVel: %s; Acc: %s",
                        continuation_indent.c_str(),
                        formatVelAcc(move_relative_data->getVelocityScalingFactor()).c_str(),
                        formatVelAcc(move_relative_data->getAccelerationScalingFactor()).c_str());
                }
            }

            stage_number++;
        }
        RCLCPP_INFO(logger, "*");
    }

    RCLCPP_INFO(logger, "************************************************************************");
}

void TaskFactory::logCreatedTask(const std::string& command, const TaskData& task_data)
{
    auto logger = rclcpp::get_logger("TaskFactory");

    RCLCPP_INFO(logger, "************************************************************************");
    RCLCPP_INFO(logger, "* Created Task: '%s'", command.c_str());

    int stage_number = 1;
    for (const auto& stage_ptr : task_data.getStages()) {
        StageType stage_type = stage_ptr->getType();
        std::string stage_type_str;

        switch (stage_type) {
            case StageType::MOVE_TO_POINT: stage_type_str = "MOVE_TO_POINT"; break;
            case StageType::MOVE_TO_CIRCLE: stage_type_str = "MOVE_TO_CIRCLE"; break;
            case StageType::MOVE_TO_JOINT: stage_type_str = "MOVE_TO_JOINT"; break;
            case StageType::MOVE_RELATIVE: stage_type_str = "MOVE_RELATIVE"; break;
            default: stage_type_str = "UNKNOWN"; break;
        }

        auto formatNumber = [](double value) -> std::string {
            char buffer[16];
            snprintf(buffer, sizeof(buffer), "%s%0.4f", (value >= 0 ? " " : ""), value);
            return std::string(buffer);
        };

        auto formatVelAcc = [](double value) -> std::string {
            char buffer[16];
            snprintf(buffer, sizeof(buffer), "%.4f", value);
            return std::string(buffer);
        };

        int stage_num_len = std::to_string(stage_number).length();
        std::string continuation_indent(28 + (stage_num_len - 1), ' ');

        if (stage_type == StageType::MOVE_TO_POINT) {
            auto move_to_point_data = std::dynamic_pointer_cast<MoveToPointData>(stage_ptr);
            if (move_to_point_data) {
                RCLCPP_INFO(logger, "*   [Stage %d] %s: Pos(%s, %s, %s)", 
                    stage_number,
                    stage_type_str.c_str(),
                    formatNumber(move_to_point_data->getX()).c_str(),
                    formatNumber(move_to_point_data->getY()).c_str(),
                    formatNumber(move_to_point_data->getZ()).c_str());
                RCLCPP_INFO(logger, "*%sOri(%s, %s, %s, %s)",
                    continuation_indent.c_str(),
                    formatNumber(move_to_point_data->getQX()).c_str(),
                    formatNumber(move_to_point_data->getQY()).c_str(),
                    formatNumber(move_to_point_data->getQZ()).c_str(),
                    formatNumber(move_to_point_data->getQW()).c_str());
                RCLCPP_INFO(logger, "*%sVel: %s; Acc: %s",
                    continuation_indent.c_str(),
                    formatVelAcc(move_to_point_data->getVelocityScalingFactor()).c_str(),
                    formatVelAcc(move_to_point_data->getAccelerationScalingFactor()).c_str());
            }
        } else if (stage_type == StageType::MOVE_TO_CIRCLE) {
            auto move_to_circle_data = std::dynamic_pointer_cast<MoveToCircleData>(stage_ptr);
            if (move_to_circle_data) {
                RCLCPP_INFO(logger, "*   [Stage %d] %s: Pos(%s, %s, %s)",
                    stage_number,
                    stage_type_str.c_str(),
                    formatNumber(move_to_circle_data->getX()).c_str(),
                    formatNumber(move_to_circle_data->getY()).c_str(),
                    formatNumber(move_to_circle_data->getZ()).c_str());
                RCLCPP_INFO(logger, "*%sOri(%s, %s, %s, %s)",
                    continuation_indent.c_str(),
                    formatNumber(move_to_circle_data->getQX()).c_str(),
                    formatNumber(move_to_circle_data->getQY()).c_str(),
                    formatNumber(move_to_circle_data->getQZ()).c_str(),
                    formatNumber(move_to_circle_data->getQW()).c_str());
                RCLCPP_INFO(logger, "*%sVel: %s; Acc: %s",
                    continuation_indent.c_str(),
                    formatVelAcc(move_to_circle_data->getVelocityScalingFactor()).c_str(),
                    formatVelAcc(move_to_circle_data->getAccelerationScalingFactor()).c_str());
            }
        } else if (stage_type == StageType::MOVE_TO_JOINT) {
            auto move_to_joint_data = std::dynamic_pointer_cast<MoveToJointData>(stage_ptr);
            if (move_to_joint_data) {
                std::stringstream joints_ss;
                joints_ss << "Joints(";
                bool first = true;
                for (const auto& joint_entry : move_to_joint_data->getJointPositions()) {
                    if (!first) joints_ss << ", ";
                    joints_ss << formatNumber(joint_entry.second);
                    first = false;
                }
                joints_ss << ")";
                
                RCLCPP_INFO(logger, "*   [Stage %d] %s: %s",
                    stage_number,
                    stage_type_str.c_str(),
                    joints_ss.str().c_str());
                RCLCPP_INFO(logger, "*%sVel: %s; Acc: %s",
                    continuation_indent.c_str(),
                    formatVelAcc(move_to_joint_data->getVelocityScalingFactor()).c_str(),
                    formatVelAcc(move_to_joint_data->getAccelerationScalingFactor()).c_str());
            }
        } else if (stage_type == StageType::MOVE_RELATIVE) {
            auto move_relative_data = std::dynamic_pointer_cast<MoveRelativeData>(stage_ptr);
            if (move_relative_data) {
                RCLCPP_INFO(logger, "*   [Stage %d] %s: Delta(%s, %s, %s)",
                    stage_number,
                    stage_type_str.c_str(),
                    formatNumber(move_relative_data->getDX()).c_str(),
                    formatNumber(move_relative_data->getDY()).c_str(),
                    formatNumber(move_relative_data->getDZ()).c_str());
                RCLCPP_INFO(logger, "*%sVel: %s; Acc: %s",
                    continuation_indent.c_str(),
                    formatVelAcc(move_relative_data->getVelocityScalingFactor()).c_str(),
                    formatVelAcc(move_relative_data->getAccelerationScalingFactor()).c_str());
            }
        }

        stage_number++;
    }
    
    RCLCPP_INFO(logger, "************************************************************************");
}