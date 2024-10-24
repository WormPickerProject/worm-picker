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
    const std::string input_directory = "/worm-picker/worm_picker_core/program_data/data_files/workstation_data.json";

    WorkstationDataParser parser(input_directory, worm_picker_node_);
    workstation_data_map_ = parser.getWorkstationDataMap();
}

void TaskFactory::setupPlanningScene() 
{
    auto addPointData = [this](const std::string& name, double x, double y, double z, double qx, double qy, double qz, double qw,
                               double velocity_scaling = 0.1, double acceleration_scaling = 0.1) {
        auto point_data = std::make_shared<MoveToData>(x, y, z, qx, qy, qz, qw, velocity_scaling, acceleration_scaling);
        stage_data_map_[name] = point_data;
    };

    auto addJointData = [this](const std::string& name, double j1, double j2, double j3, double j4, double j5, double j6,
                               double velocity_scaling = 0.1, double acceleration_scaling = 0.1) {
        auto joint_data = std::make_shared<JointData>(j1, j2, j3, j4, j5, j6, velocity_scaling, acceleration_scaling);
        stage_data_map_[name] = joint_data;
    };

    auto addTaskData = [this](const std::string& name, const std::initializer_list<std::string>& stage_names) {
        task_data_map_[name] = TaskData(stage_data_map_, stage_names);
    };

    /*Parameters:*/
    double hotel_nbr = 1; // currently not working
    double slot_hotel_nbr = 1;
    double flat_man_ang = -36.0;
    double init_arc_hotel = -56.9;
    double hotel_hotel_ang = 19.4;
    double base_z = 0.39075;
    double plate_plate_hotel = 0.026925;
    double z_disp = (slot_hotel_nbr - 1) * plate_plate_hotel;
    double arc_hotel_disp = (hotel_nbr - 1) * hotel_hotel_ang;

    /*Test Points&Joints:*/
    addPointData("homePoint",    0.46200,  0.00000,  0.50500,  0.70711,  0.70711,  0.00000,  0.00000);
    addPointData("pointA",       0.58638,  0.00000,  0.50499,  0.70711,  0.70711,  0.00000,  0.00000);
    addJointData("jointS", 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1);

    /*Configuration Points&Joints:*/
    // Zeroed joints
    addJointData("home", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1);

    /*Plate pick and place from hotel: hotel_nbr = 1, slot_hotel_nbr = 1 as base*/
    // Flat manipulator
    addJointData("point1", 0.0, 0.0, 0.0, 0.0, flat_man_ang, 0.0, 0.2, 0.1);
    // Facing plate hotel
    addJointData("point2", init_arc_hotel - arc_hotel_disp, 0.0, 0.0, 0.0, flat_man_ang, 0.0, 0.2, 0.1);
    // Below plate level
    addPointData("point3",  0.20225, -0.31025,  base_z + z_disp,  0.91163,  0.27090, -0.08805, -0.29630, 0.20000,  0.10000); // quaternion problem with generalizing on hotels
    // Forward - below plate
    addPointData("point4",  0.24286, -0.37257,  base_z + z_disp,  0.91162,  0.27089, -0.08809, -0.29633, 0.05000,  0.10000); // we just want the same point 2 queternion
    // Pick up plate
    addPointData("point5",  0.24286, -0.37257,  0.40110 + z_disp,  0.91163,  0.27089, -0.08805, -0.29631, 0.05000,  0.10000);
    // Retrieve plate
    addPointData("point6",  0.17422, -0.26728,  0.40110 + z_disp,  0.91162,  0.27087, -0.08806, -0.29635, 0.20000,  0.10000);
    // Center robot
    addPointData("point7",  0.31905,  0.00000,  0.40110 + z_disp,  0.67248,  0.67246, -0.21860, -0.21860, 0.10000,  0.10000);
    // Place plate on workstation ...

    /*Plate pick and place from workstation: slot 1 as base*/

    addTaskData("home", { 
        "home" 
    });
    addTaskData("pointA", { 
        "pointA" 
    });
    addTaskData("point1", { 
        "point1" 
    });
    addTaskData("point2", { 
        "point2" 
    });
    addTaskData("point3", { 
        "point3" 
    });
    addTaskData("point4", { 
        "point4" 
    });
    addTaskData("point5", { 
        "point5" 
    });
    addTaskData("point6", { 
        "point6" 
    });
    addTaskData("point7", { 
        "point7" 
    });
    addTaskData("jointS", { 
        "jointS" 
    });
    addTaskData("pickUpPlate", {
        "home",
        "point1",
        "point2",
        "point3",
        "point4",
        "point5",
        "point6",
        "point7",
        "home"
    });

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
            case StageType::JOINT:
                {
                    auto joint_data = std::static_pointer_cast<JointData>(stage_ptr);
                    addJointStage(current_task, stage_name + "_joint_move", joint_data);
                    break;
                }
            case StageType::MOVE_TO:
                {
                    auto move_to_data = std::static_pointer_cast<MoveToData>(stage_ptr);
                    addMoveToStage(current_task, stage_name + "_pose_move", move_to_data);
                    break;
                }
            default:
                throw UnknownStageTypeException(
                    "TaskFactory::createTask failed: Unknown StageType."
                );
        }
    }

    return current_task;
}

void TaskFactory::addJointStage(Task& task, const std::string& name, 
                                const std::shared_ptr<JointData>& joint_data) 
{
    auto joint_interpolation_planner = std::make_shared<JointInterpolationPlanner>();
    joint_interpolation_planner->setMaxVelocityScalingFactor(joint_data->velocity_scaling_factor);
    joint_interpolation_planner->setMaxAccelerationScalingFactor(joint_data->acceleration_scaling_factor);
    
    auto current_stage = std::make_unique<MoveToStage>(name, joint_interpolation_planner);
    current_stage->setGoal(joint_data->joint_positions);
    current_stage->setGroup("gp4_arm");
    current_stage->setIKFrame("eoat_tcp");

    const std::string controller_name = "follow_joint_trajectory";
    TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {controller_name};
    current_stage->setProperty("trajectory_execution_info", execution_info);

    if (!current_stage) {
        throw StageCreationFailedException(
            "TaskFactory::addJointStage failed to create stage: " + name
        );
    }

    task.add(std::move(current_stage));
}

void TaskFactory::addMoveToStage(Task& task, const std::string& name, 
                                 const std::shared_ptr<MoveToData>& move_to_data) 
{
    geometry_msgs::msg::PoseStamped target_pose;
    target_pose.header.frame_id = "base_link";
    target_pose.header.stamp = worm_picker_node_->now();
    target_pose.pose.position.x = move_to_data->x;
    target_pose.pose.position.y = move_to_data->y;
    target_pose.pose.position.z = move_to_data->z;
    target_pose.pose.orientation.x = move_to_data->qx;
    target_pose.pose.orientation.y = move_to_data->qy;
    target_pose.pose.orientation.z = move_to_data->qz;
    target_pose.pose.orientation.w = move_to_data->qw;
    
    auto cartesian_planner = std::make_shared<CartesianPath>();
    cartesian_planner->setMaxVelocityScalingFactor(move_to_data->velocity_scaling_factor);
    cartesian_planner->setMaxAccelerationScalingFactor(move_to_data->acceleration_scaling_factor);
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
            "TaskFactory::addMoveToStage failed to create stage: " + name
        );
    }

    task.add(std::move(current_stage));
}