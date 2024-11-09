// task_data_structure.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tasks/task_factory.hpp"
#include "worm_picker_core/tasks/generation/task_generator.hpp"

TaskFactory::TaskFactory(const rclcpp::Node::SharedPtr& node) 
    : worm_picker_node_(node)
{ 
    if (!worm_picker_node_) {
        throw TaskFactoryError(
            TaskFactoryError::ErrorCode::InvalidConfiguration,
            "TaskFactory initialization failed: worm_picker_node_ is null."
        );
    }

    declareParameters();
    parseData();
    initializeTaskMap();
}

void TaskFactory::declareParameters() 
{
    const std::vector<std::pair<std::string, rclcpp::ParameterValue>> default_parameters{
        {"workstation_config_file", 
         rclcpp::ParameterValue(std::string(CONFIG_PATH) + "/workstation_data.json")},
        
        {"hotel_config_file", 
         rclcpp::ParameterValue(std::string(CONFIG_PATH) + "/hotel_data.json")}
    };

    for (const auto& [name, default_value] : default_parameters) {
        worm_picker_node_->declare_parameter(name, default_value);
    }
}

void TaskFactory::parseData() 
{
    const auto workstation_file = worm_picker_node_
        ->get_parameter("workstation_config_file").as_string();
    const auto hotel_file = worm_picker_node_
        ->get_parameter("hotel_config_file").as_string();

    WorkstationDataParser workstation_parser(workstation_file);
    workstation_data_map_ = workstation_parser.getWorkstationDataMap();

    HotelDataParser hotel_parser(hotel_file);
    hotel_data_map_ = hotel_parser.getHotelDataMap(); 
    
    logDataMaps(); 
}

void TaskFactory::initializeTaskMap() 
{
    TaskGenerator tasks_plans(workstation_data_map_, hotel_data_map_);
    task_data_map_ = tasks_plans.getGeneratedTaskPlans();

    using Type = StageConfig::Type;
    static constexpr auto JOINT = Type::JOINT;
    static constexpr auto POINT = Type::POINT;
    static constexpr auto RELATIVE = Type::RELATIVE;

    const std::vector<StageConfig> stages = {
        {"home", JOINT, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
        {"jointPoint1", JOINT, {-2.0, -11.0, 21.0, 0.0, -62.0, 0.0}},
        {"jointPoint2", JOINT, {15.0, 7.0, 23.0, 18.0, -48.0, -20.0}},
        {"jointPoint3", JOINT, {-28.0, 28.0, 23.0, -43.0, -37.0, 52.0}},
        {"homeEndFactor", JOINT, {0.0, 0.0, 0.0, 0.0, 0.0, -30.0}},
        {"swapEndFactor:1", JOINT, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
        {"swapEndFactor:2", JOINT, {0.0, 0.0, 0.0, 0.0, 0.0, -90.0}},
        {"coordPoint1", POINT, {0.47424, 0.01732, 0.48122, 0.70712, 0.0, 0.7071, 0.0}},
        {"coordPoint2", POINT, {0.39007, -0.11781, 0.44918, 0.70712, 0.0, 0.7071, 0.0}},
        {"coordPoint3", POINT, {0.40111, 0.25094, 0.42120, 0.70712, 0.0, 0.7071, 0.0}},
        {"moveRelativeX", RELATIVE, {0.1, 0.0, 0.0}},
        {"moveRelativeY", RELATIVE, {0.0, 0.1, 0.0}},
        {"moveRelativeZ", RELATIVE, {0.0, 0.0, 0.1}}
    };

    const std::vector<TaskConfig> tasks = {
        {"home", { "home" }},
        {"coordPoint1", { "coordPoint1" }},
        {"coordPoint2", { "coordPoint2" }},
        {"coordPoint3", { "coordPoint3" }},
        {"jointPoint1", { "jointPoint1" }},
        {"jointPoint2", { "jointPoint2" }},
        {"jointPoint3", { "jointPoint3" }},
        {"homeEndFactor", { "homeEndFactor" }},
        {"swapEndFactor:1", { "swapEndFactor:1" }},
        {"swapEndFactor:2", { "swapEndFactor:2" }},
        {"moveRelativeX", { "moveRelativeX" }},
        {"moveRelativeY", { "moveRelativeY" }},
        {"moveRelativeZ", { "moveRelativeZ" }},
        {"pointSequence", {"coordPoint1", "coordPoint2", "coordPoint3"}},
        {"jointSequence", {"jointPoint1", "jointPoint2", "jointPoint3"}},
        {"relativeSequence", {"moveRelativeX", "moveRelativeY", "moveRelativeZ"}},
        {"mixedPointJoint", {"coordPoint1", "jointPoint2", "coordPoint3"}},
        {"mixedPointRelative", {"coordPoint1", "moveRelativeX", "coordPoint2"}},
        {"mixedJointPoint", {"jointPoint1", "coordPoint2", "jointPoint3"}},
        {"mixedJointRelative", {"jointPoint1", "moveRelativeY", "jointPoint2"}},
        {"mixedRelativePoint", {"moveRelativeX", "coordPoint1", "moveRelativeY"}},
        {"mixedRelativeJoint", {"moveRelativeY", "jointPoint1", "moveRelativeZ"}},
        {"allStageSequence", 
            {"home", "coordPoint1", "jointPoint1", "moveRelativeX", "coordPoint2", 
             "jointPoint2", "moveRelativeY", "coordPoint3", "jointPoint3", "moveRelativeZ"}}
    };

    for (const auto& stage : stages) {
        switch (stage.type) {
            case JOINT: {
                auto data = std::make_shared<MoveToJointData>(
                    stage.parameters[0], stage.parameters[1], stage.parameters[2],
                    stage.parameters[3], stage.parameters[4], stage.parameters[5],
                    stage.velocity_scaling, stage.acceleration_scaling
                );
                stage_data_map_[stage.name] = data;
                break;
            }
            case POINT: {
                auto data = std::make_shared<MoveToPointData>(
                    stage.parameters[0], stage.parameters[1], stage.parameters[2],
                    stage.parameters[3], stage.parameters[4], stage.parameters[5], 
                    stage.parameters[6], stage.velocity_scaling, stage.acceleration_scaling
                );
                stage_data_map_[stage.name] = data;
                break;
            }
            case RELATIVE: {
                auto data = std::make_shared<MoveRelativeData>(
                    stage.parameters[0], stage.parameters[1], stage.parameters[2],
                    stage.velocity_scaling, stage.acceleration_scaling
                );
                stage_data_map_[stage.name] = data;
                break;
            }
        }
    }

    for (const auto& task : tasks) {
        task_data_map_[task.name] = TaskData(stage_data_map_, task.stages);
    }
}

moveit::task_constructor::Task TaskFactory::createTask(std::string_view command) 
{
    if (!worm_picker_node_) {
        throw TaskFactoryError(
            TaskFactoryError::ErrorCode::InvalidConfiguration,
            "TaskFactory::createTask failed: node_ is null."
        );
    }

    auto task = createBaseTask(command);
    
    auto current_state_stage = std::make_unique<CurrentStateStage>("current");
    task.add(std::move(current_state_stage));

    auto it = task_data_map_.find(std::string(command));
    if (it == task_data_map_.end()) {
        throw TaskFactoryError(
            TaskFactoryError::ErrorCode::TaskCreationFailed,
            fmt::format("Command '{}' not found", command)
        );
    }
    
    const TaskData& task_data = it->second;
    int stage_counter = 1;

    for (const auto& stage_ptr : task_data.getStages()) {
        const std::string stage_name = fmt::format("stage_{}", stage_counter++);
        auto stage = stage_ptr->createStage(stage_name, worm_picker_node_);

        if (!stage) {
            throw TaskFactoryError(
                TaskFactoryError::ErrorCode::StageCreationFailed,
                fmt::format("Failed to create stage: {}", stage_name)
            );
        }

        task.add(std::move(stage));
    }

    return task;
}

moveit::task_constructor::Task TaskFactory::createBaseTask(std::string_view command) {
    Task task;
    task.stages()->setName(std::string(command));
    task.loadRobotModel(worm_picker_node_);
    
    task.setProperty("group", "gp4_arm");
    task.setProperty("ik_frame", "eoat_tcp");
    
    TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {"follow_joint_trajectory"};
    task.setProperty("trajectory_execution_info", execution_info);
    
    return task;
}

// Temporary functions:
void TaskFactory::logDataMaps() const 
{
    if (workstation_data_map_.empty()) {
        RCLCPP_INFO(worm_picker_node_->get_logger(), "\n");
        RCLCPP_INFO(worm_picker_node_->get_logger(), "********************************************************");
        RCLCPP_INFO(worm_picker_node_->get_logger(), "* Workstation Data Map is empty.");
        RCLCPP_INFO(worm_picker_node_->get_logger(), "********************************************************\n");
    } else {
        RCLCPP_INFO(worm_picker_node_->get_logger(), "\n");
        RCLCPP_INFO(worm_picker_node_->get_logger(), "********************************************************");
        RCLCPP_INFO(worm_picker_node_->get_logger(), "* Logging Workstation Data Map:");
        for (const auto& [workstation_id, workstation_data] : workstation_data_map_) {
            RCLCPP_INFO(worm_picker_node_->get_logger(), "* Workstation ID: %s", workstation_id.c_str());
            RCLCPP_INFO(worm_picker_node_->get_logger(), "*   Position (x, y, z): (%f, %f, %f)", 
                        workstation_data.getCoordinate().getPositionX(), 
                        workstation_data.getCoordinate().getPositionY(), 
                        workstation_data.getCoordinate().getPositionZ());
            RCLCPP_INFO(worm_picker_node_->get_logger(), "*   Orientation (qx, qy, qz, qw): (%f, %f, %f, %f)", 
                        workstation_data.getCoordinate().getOrientationX(), 
                        workstation_data.getCoordinate().getOrientationY(), 
                        workstation_data.getCoordinate().getOrientationZ(), 
                        workstation_data.getCoordinate().getOrientationW());
        }
        RCLCPP_INFO(worm_picker_node_->get_logger(), "********************************************************\n");
    }
}
