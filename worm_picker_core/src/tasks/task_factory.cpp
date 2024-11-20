// task_factory.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tasks/task_factory.hpp"
#include "worm_picker_core/tasks/generation/task_generator.hpp"
#include "worm_picker_core/tools/parsers/defined_tasks_parser.hpp"
#include "worm_picker_core/tasks/generation/generate_relative_movement_task.hpp"

TaskFactory::TaskFactory(const NodePtr& node) 
    : worm_picker_node_(node) 
{ 
    if (!worm_picker_node_) {
        throw std::runtime_error("TaskFactory initialization failed: worm_picker_node_ is null.");
    }

    initializeTaskMap();
}

TaskFactory::Task TaskFactory::createTask(std::string_view command) 
{
    auto task = createBaseTask(command);
    task.add(std::make_unique<CurrentStateStage>("current"));

    const TaskData task_data = [&] {
        if (command.starts_with("moveRelative:")) {
            return GenerateRelativeMovementTask::parseCommand(command);
        }
        
        auto it = task_data_map_.find(std::string{command});
        if (it == task_data_map_.end()) {
            throw std::invalid_argument(fmt::format("Command '{}' not found", command));
        }
        return it->second;
    }();

    int stage_counter{1};
    for (const auto& stage_ptr : task_data.getStages()) {
        const auto stage_name = fmt::format("stage_{}", stage_counter++);
        auto stage = stage_ptr->createStage(stage_name, worm_picker_node_);

        if (!stage) {
            throw std::runtime_error(fmt::format("Failed to create stage: {}", stage_name));
        }
        task.add(std::move(stage));
    }

    return task;
}

void TaskFactory::initializeTaskMap() 
{
    const auto workstation_config_file = 
        worm_picker_node_->get_parameter("workstation_config_file").as_string();
    const auto hotel_config_file = 
        worm_picker_node_->get_parameter("hotel_config_file").as_string();
    const auto defined_stages_file = 
        worm_picker_node_->get_parameter("defined_stages_file").as_string();
    const auto defined_tasks_file = 
        worm_picker_node_->get_parameter("defined_tasks_file").as_string();

    const WorkstationDataParser workstation_parser{workstation_config_file};
    const auto& workstation_data_map = workstation_parser.getWorkstationDataMap();

    const HotelDataParser hotel_parser{hotel_config_file};
    const auto& hotel_data_map = hotel_parser.getHotelDataMap();

    const DefinedTasksGenerator defined_tasks_parser{defined_stages_file, defined_tasks_file};
    const auto& defined_tasks_map = defined_tasks_parser.getDefinedTasksMap();

    const TaskGenerator task_plans{workstation_data_map, hotel_data_map};
    const auto& generated_task_map = task_plans.getGeneratedTaskPlans();

    task_data_map_.insert(defined_tasks_map.begin(), defined_tasks_map.end());
    task_data_map_.insert(generated_task_map.begin(), generated_task_map.end());

    logTaskMap(); // Temporary debug function
}

TaskFactory::Task TaskFactory::createBaseTask(std::string_view command) 
{
    Task task;
    task.stages()->setName(std::string{command});
    task.loadRobotModel(worm_picker_node_);
    
    task.setProperty("group", "gp4_arm");
    const std::string current_end_effector = 
        worm_picker_node_->get_parameter("end_effector").as_string();
    task.setProperty("ik_frame", current_end_effector);
    
    TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {"follow_joint_trajectory"};
    task.setProperty("trajectory_execution_info", execution_info);
    
    return task;
}

void TaskFactory::logTaskMap()
{
    auto logger = rclcpp::get_logger("TaskFactory");

    RCLCPP_INFO(logger, "*****************************************************************************");
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
                case StageType::MOVE_TO_JOINT: stage_type_str = "MOVE_TO_JOINT"; break;
                case StageType::MOVE_RELATIVE: stage_type_str = "MOVE_RELATIVE"; break;
                default: stage_type_str = "UNKNOWN"; break;
            }

            auto formatNumber = [](double value) -> std::string {
                char buffer[16];
                snprintf(buffer, sizeof(buffer), "%s%0.2f", (value >= 0 ? " " : ""), value);
                return std::string(buffer);
            };

            auto formatVelAcc = [](double value) -> std::string {
                char buffer[16];
                snprintf(buffer, sizeof(buffer), "%.2f", value);
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

    RCLCPP_INFO(logger, "*****************************************************************************");
}
