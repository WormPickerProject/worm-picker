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
    current_task.stages()->setName(command);
    current_task.loadRobotModel(worm_picker_node_);

    current_task.setProperty("group", "gp4_arm");
    current_task.setProperty("ik_frame", "eoat_tcp");

    TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {"follow_joint_trajectory"};
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

    for (const auto& stage_ptr : task_data.getStages()) {
        std::string stage_name = "stage_" + std::to_string(stage_counter++);
        auto stage = stage_ptr->createStage(stage_name, worm_picker_node_);
        if (!stage) {
            throw StageCreationFailedException("Failed to create stage: " + stage_name);
        }
        current_task.add(std::move(stage));
    }

    return current_task;
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
