// task_data_structure.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
// Additional Contributions: Fang-Yen Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");

#include "worm_picker_core/tasks/task_factory.hpp"
#include "worm_picker_core/tasks/generation/task_generator.hpp"

TaskFactory::TaskFactory(const rclcpp::Node::SharedPtr& node) 
    : worm_picker_node_(node)
{ 
    if (!worm_picker_node_) {
        throw NullNodeException("TaskFactory initialization failed: worm_picker_node_ is null.");
    }

    parseData();
    setupPlanningScene();
}

void TaskFactory::parseData() 
{
    const std::string workstation_input_directory = "/worm-picker/worm_picker_description/program_data/data_files/workstation_data.json";
    const std::string hotel_input_directory = "worm-picker/worm_picker_description/program_data/data_files/hotel_data.json";
    
    WorkstationDataParser workstation_parser(workstation_input_directory);
    workstation_data_map_ = workstation_parser.getWorkstationDataMap();

    HotelDataParser hotel_parser(hotel_input_directory);
    hotel_data_map_ = hotel_parser.getHotelDataMap(); 
    
    logDataMaps(); 
}

void TaskFactory::setupPlanningScene() 
{
    TaskGenerator tasks_plans(workstation_data_map_, hotel_data_map_);
    task_data_map_ = tasks_plans.getGeneratedTaskPlans(); 

    auto addMoveToPointData = [this](
        const std::string& name, double x, double y, double z, double qx, double qy, double qz, double qw,
        double velocity_scaling = 0.1, double acceleration_scaling = 0.1) {
        auto move_to_point_data = std::make_shared<MoveToPointData>(
            x, y, z, qx, qy, qz, qw, velocity_scaling, acceleration_scaling);
        stage_data_map_[name] = move_to_point_data;
    };

    auto addMoveToJointData = [this](
        const std::string& name, double j1, double j2, double j3, double j4, double j5, double j6,
        double velocity_scaling = 0.1, double acceleration_scaling = 0.1) {
        auto move_to_joint_data = std::make_shared<MoveToJointData>(
            j1, j2, j3, j4, j5, j6, velocity_scaling, acceleration_scaling);
        stage_data_map_[name] = move_to_joint_data;
    };

    auto addMoveRelativeData = [this](
        const std::string& name, double dx, double dy, double dz,
        double velocity_scaling = 0.1, double acceleration_scaling = 0.1) {
        auto move_relative_data = std::make_shared<MoveRelativeData>(
            dx, dy, dz, velocity_scaling, acceleration_scaling);
        stage_data_map_[name] = move_relative_data;
    };

    auto addTaskData = [this](
        const std::string& name, const std::initializer_list<std::string>& stage_names) {
        task_data_map_[name] = TaskData(stage_data_map_, stage_names);
    };

    // Parameters:
    double hotel_number = 1;  // Currently not used
    double slot_hotel_number = 1;
    double flat_manipulator_angle = -36.0;
    double initial_arc_hotel = -56.9;
    double hotel_to_hotel_angle = 19.4;
    double base_z_position = 0.39075;
    double plate_to_plate_hotel = 0.026925;

    double z_displacement = (slot_hotel_number - 1) * plate_to_plate_hotel;
    double arc_hotel_displacement = (hotel_number - 1) * hotel_to_hotel_angle;

    // Test Points & Joints: 
    addMoveToPointData("homePoint", 
        0.37452, 0.00000, 0.44938, 0.70712, 0.0000, 0.70710, 0.00000
    );
    addMoveToPointData("pointA", 
        0.58638, 0.00000, 0.50499, 0.70711, 0.70711, 0.00000, 0.00000
    );
    addMoveToJointData("jointS", 
        10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1
    );

    // Configuration Points & Joints:
    addMoveToJointData("home", 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1
    );
    addMoveToJointData("homeJoint", 
        0.0, 0.0, 0.0, 0.0, -30.0, 0.0, 0.1, 0.1
    );

    // Plate pick and place from hotel: hotel_number = 1, slot_hotel_number = 1 as base
    // Flat manipulator position
    addMoveToJointData("point1", 
        0.0, 0.0, 0.0, 0.0, flat_manipulator_angle, 0.0, 0.2, 0.1
    );
    // Facing plate hotel
    addMoveToJointData("point2", 
        initial_arc_hotel - arc_hotel_displacement, 0.0, 0.0, 0.0, 
        flat_manipulator_angle, 0.0, 0.2, 0.1
    );
    // Below plate level
    addMoveToPointData("point3",  
        0.20225, -0.31025, base_z_position + z_displacement, 
        0.91163, 0.27090, -0.08805, -0.29630, 0.20000, 0.10000
    ); 
    // Forward - below plate
    addMoveToPointData("point4",  
        0.24286, -0.37257, base_z_position + z_displacement, 
        0.91162, 0.27089, -0.08809, -0.29633, 0.05000, 0.10000
    );
    // Pick up plate
    addMoveToPointData("point5",  
        0.24286, -0.37257, 0.40110 + z_displacement, 
        0.91163, 0.27089, -0.08805, -0.29631, 0.05000, 0.10000
    );
    // Retrieve plate
    addMoveToPointData("point6",  
        0.17422, -0.26728, 0.40110 + z_displacement, 
        0.91162, 0.27087, -0.08806, -0.29635, 0.20000, 0.10000
    );
    // Center robot
    addMoveToPointData("point7",  
        0.31905, 0.00000, 0.40110 + z_displacement, 
        0.67248, 0.67246, -0.21860, -0.21860, 0.10000, 0.10000
    );

    addMoveRelativeData("move_relative_x", 0.1, 0.0, 0.0);
    addMoveRelativeData("move_relative_y", 0.0, 0.1, 0.0);
    addMoveRelativeData("move_relative_z", 0.0, 0.0, 0.1);

    addTaskData("home", { "home" });
    addTaskData("homePoint", { "homePoint" });
    addTaskData("homeJoint", { "homeJoint" });
    addTaskData("pointA", { "pointA" });
    addTaskData("point1", { "point1" });
    addTaskData("point2", { "point2" });
    addTaskData("point3", { "point3" });
    addTaskData("point4", { "point4" });
    addTaskData("point5", { "point5" });
    addTaskData("point6", { "point6" });
    addTaskData("point7", { "point7" });
    addTaskData("jointS", { "jointS" });
    addTaskData("pickUpPlate", 
        { "home", "point1", "point2", "point3", "point4", "point5", "point6", "point7", "home" }
    );
    addTaskData("move_relative_x", { "move_relative_x" });
    addTaskData("move_relative_y", { "move_relative_y" });
    addTaskData("move_relative_z", { "move_relative_z" });
}

moveit::task_constructor::Task TaskFactory::createTask(const std::string& command) 
{
    if (!worm_picker_node_) {
        throw NullNodeException("TaskFactory::createTask failed: node_ is null.");
    }

    Task current_task;
    current_task.stages()->setName("dynamic_task");
    current_task.loadRobotModel(worm_picker_node_);

    const std::string arm_group_name = "gp4_arm";
    current_task.setProperty("group", arm_group_name);

    const std::string controller_name = "follow_joint_trajectory";
    TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {controller_name};
    current_task.setProperty("trajectory_execution_info", execution_info);
    
    auto current_state_stage = std::make_unique<CurrentStateStage>("current");
    current_task.add(std::move(current_state_stage));

    auto it = task_data_map_.find(command);
    if (it == task_data_map_.end()) {
        throw TaskCommandNotFoundException(
            "TaskFactory::createTask failed: Command '" + command + "' not found."
        );
    }
    
    int stage_counter = 1;
    const TaskData& task_data = it->second;
    for (const auto& stage_ptr : task_data.stages) {
        std::string stage_name = "stage_" + std::to_string(stage_counter++);
        switch (stage_ptr->getType()) {
            case StageType::MOVE_TO_JOINT: 
            {
                auto move_to_joint_data = std::static_pointer_cast<MoveToJointData>(stage_ptr);
                addMoveToJointStage(current_task, stage_name + "_joint_move", move_to_joint_data);
                break;
            }
            case StageType::MOVE_TO_POINT: 
            {
                auto move_to_point_data = std::static_pointer_cast<MoveToPointData>(stage_ptr);
                addMoveToPointStage(current_task, stage_name + "_pose_move", move_to_point_data);
                break;
            }
            case StageType::MOVE_RELATIVE: 
            {
                auto move_relative_data = std::static_pointer_cast<MoveRelativeData>(stage_ptr);
                addMoveRelativeStage(current_task, stage_name + "_relative_move", move_relative_data);
                break;
            }
            default:
            {
                throw UnknownStageTypeException(
                    "TaskFactory::createTask failed: Unknown StageType."
                );
            }
        }
    }

    return current_task;
}

void TaskFactory::addMoveToJointStage(Task& task, const std::string& name, 
                                      const std::shared_ptr<MoveToJointData>& move_to_joint_data) 
{
    auto joint_interpolation_planner = std::make_shared<JointInterpolationPlanner>();
    joint_interpolation_planner->setMaxVelocityScalingFactor(move_to_joint_data->velocity_scaling_factor);
    joint_interpolation_planner->setMaxAccelerationScalingFactor(move_to_joint_data->acceleration_scaling_factor);
    
    auto current_stage = std::make_unique<MoveToStage>(name, joint_interpolation_planner);
    current_stage->setGoal(move_to_joint_data->joint_positions);
    current_stage->setGroup("gp4_arm");
    current_stage->setIKFrame("eoat_tcp");

    const std::string controller_name = "follow_joint_trajectory";
    TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {controller_name};
    current_stage->setProperty("trajectory_execution_info", execution_info);

    if (!current_stage) {
        throw StageCreationFailedException(
            "TaskFactory::addMoveToJointStage failed to create stage: " + name
        );
    }

    task.add(std::move(current_stage));
}

void TaskFactory::addMoveToPointStage(Task& task, const std::string& name, 
                                      const std::shared_ptr<MoveToPointData>& move_to_point_data) 
{
    geometry_msgs::msg::PoseStamped target_pose;
    target_pose.header.frame_id = "base_link";
    target_pose.header.stamp = worm_picker_node_->now();
    target_pose.pose.position.x = move_to_point_data->x;
    target_pose.pose.position.y = move_to_point_data->y;
    target_pose.pose.position.z = move_to_point_data->z;
    target_pose.pose.orientation.x = move_to_point_data->qx;
    target_pose.pose.orientation.y = move_to_point_data->qy;
    target_pose.pose.orientation.z = move_to_point_data->qz;
    target_pose.pose.orientation.w = move_to_point_data->qw;
    
    auto cartesian_planner = std::make_shared<CartesianPath>();
    cartesian_planner->setMaxVelocityScalingFactor(move_to_point_data->velocity_scaling_factor);
    cartesian_planner->setMaxAccelerationScalingFactor(move_to_point_data->acceleration_scaling_factor);
    cartesian_planner->setStepSize(.01);
    cartesian_planner->setMinFraction(0.0);

    auto current_stage = std::make_unique<MoveToStage>(name, cartesian_planner);
    current_stage->setGoal(target_pose);
    current_stage->setGroup("gp4_arm"); 
    current_stage->setIKFrame("eoat_tcp");

    const std::string controller_name = "follow_joint_trajectory";
    TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {controller_name};
    current_stage->setProperty("trajectory_execution_info", execution_info);

    if (!current_stage) {
        throw StageCreationFailedException(
            "TaskFactory::addMoveToPointStage failed to create stage: " + name
        );
    }

    task.add(std::move(current_stage));
}

void TaskFactory::addMoveRelativeStage(Task& task, const std::string& name, 
                                       const std::shared_ptr<MoveRelativeData>& move_relative_data) 
{
    geometry_msgs::msg::Vector3Stamped direction_vector;
    direction_vector.header.frame_id = "eoat_tcp";
    direction_vector.header.stamp = worm_picker_node_->now();
    direction_vector.vector.x = move_relative_data->dx;
    direction_vector.vector.y = move_relative_data->dy;
    direction_vector.vector.z = move_relative_data->dz;

    auto cartesian_planner = std::make_shared<CartesianPath>();
    cartesian_planner->setMaxVelocityScalingFactor(move_relative_data->velocity_scaling_factor);
    cartesian_planner->setMaxAccelerationScalingFactor(move_relative_data->acceleration_scaling_factor);
    cartesian_planner->setStepSize(.01);
    cartesian_planner->setMinFraction(0.0);

    auto current_stage = std::make_unique<MoveRelativeStage>(name, cartesian_planner);
    current_stage->setDirection(direction_vector);
    current_stage->setGroup("gp4_arm"); 
    current_stage->setIKFrame("eoat_tcp");

    const std::string controller_name = "follow_joint_trajectory";
    TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {controller_name};
    current_stage->setProperty("trajectory_execution_info", execution_info);

    if (!current_stage) {
        throw StageCreationFailedException(
            "TaskFactory::addMoveRelativeStage failed to create stage: " + name
        );
    }

    task.add(std::move(current_stage));
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
                        workstation_data.coordinate.position_x, 
                        workstation_data.coordinate.position_y, 
                        workstation_data.coordinate.position_z);
            RCLCPP_INFO(worm_picker_node_->get_logger(), "*   Orientation (qx, qy, qz, qw): (%f, %f, %f, %f)", 
                        workstation_data.coordinate.orientation_x, 
                        workstation_data.coordinate.orientation_y, 
                        workstation_data.coordinate.orientation_z, 
                        workstation_data.coordinate.orientation_w);
        }
        RCLCPP_INFO(worm_picker_node_->get_logger(), "********************************************************\n");
    }
}
