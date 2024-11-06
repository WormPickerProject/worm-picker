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
    setupPlanningScene();
}

void TaskFactory::declareParameters() {
    const std::vector<std::pair<std::string, rclcpp::ParameterValue>> default_parameters{
        {"workstation_config_file", rclcpp::ParameterValue(std::string(CONFIG_PATH) + "/workstation_data.json")},
        {"hotel_config_file", rclcpp::ParameterValue(std::string(CONFIG_PATH) + "/hotel_data.json")}
    };

    for (const auto& [name, default_value] : default_parameters) {
        worm_picker_node_->declare_parameter(name, default_value);
    }
}

void TaskFactory::parseData() 
{
    const auto workstation_file = worm_picker_node_->get_parameter("workstation_config_file").as_string();
    const auto hotel_file = worm_picker_node_->get_parameter("hotel_config_file").as_string();

    WorkstationDataParser workstation_parser(workstation_file);
    workstation_data_map_ = workstation_parser.getWorkstationDataMap();

    HotelDataParser hotel_parser(hotel_file);
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

    // Soon to be replaced with stages and tasks down below.
    double hotel_number = 1;
    double slot_hotel_number = 1;
    double flat_manipulator_angle = -36.0;
    double initial_arc_hotel = -56.9;
    double hotel_to_hotel_angle = 19.4;
    double base_z_position = 0.39075;
    double plate_to_plate_hotel = 0.026925;
    double z_displacement = (slot_hotel_number - 1) * plate_to_plate_hotel;
    double arc_hotel_displacement = (hotel_number - 1) * hotel_to_hotel_angle;

    addMoveToPointData("homePoint", 
        0.37452, 0.00000, 0.44938, 0.70712, 0.0000, 0.70710, 0.00000
    );
    addMoveToPointData("pointA", 
        0.58638, 0.00000, 0.50499, 0.70711, 0.70711, 0.00000, 0.00000
    );
    addMoveToJointData("jointS", 
        10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1
    );
    addMoveToJointData("home", 
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1
    );
    addMoveToJointData("homeJoint", 
        0.0, 0.0, 0.0, 0.0, -30.0, 0.0, 0.1, 0.1
    );
    addMoveToJointData("point1", 
        0.0, 0.0, 0.0, 0.0, flat_manipulator_angle, 0.0, 0.2, 0.1
    );
    addMoveToJointData("point2", 
        initial_arc_hotel - arc_hotel_displacement, 0.0, 0.0, 0.0, 
        flat_manipulator_angle, 0.0, 0.2, 0.1
    );
    addMoveToPointData("point3",  
        0.20225, -0.31025, base_z_position + z_displacement, 
        0.91163, 0.27090, -0.08805, -0.29630, 0.20000, 0.10000
    ); 
    addMoveToPointData("point4",  
        0.24286, -0.37257, base_z_position + z_displacement, 
        0.91162, 0.27089, -0.08809, -0.29633, 0.05000, 0.10000
    );
    addMoveToPointData("point5",  
        0.24286, -0.37257, 0.40110 + z_displacement, 
        0.91163, 0.27089, -0.08805, -0.29631, 0.05000, 0.10000
    );
    addMoveToPointData("point6",  
        0.17422, -0.26728, 0.40110 + z_displacement, 
        0.91162, 0.27087, -0.08806, -0.29635, 0.20000, 0.10000
    );
    addMoveToPointData("point7",  
        0.31905, 0.00000, 0.40110 + z_displacement, 
        0.67248, 0.67246, -0.21860, -0.21860, 0.10000, 0.10000
    );
    addMoveRelativeData("moveRelativeX", 0.1, 0.0, 0.0);
    addMoveRelativeData("moveRelativeY", 0.0, 0.1, 0.0);
    addMoveRelativeData("moveRelativeZ", 0.0, 0.0, 0.1);
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
    addTaskData("moveRelativeX", { "moveRelativeX" });
    addTaskData("moveRelativeY", { "moveRelativeY" });
    addTaskData("moveRelativeZ", { "moveRelativeZ" });
    addTaskData("pickUpPlate", 
        { "home", "point1", "point2", "point3", "point4", "point5", "point6", "point7", "home" }
    );

    // // Manually added stages. 
    // addMoveToJointData("home", 
    //     0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.1,  0.1
    // );
    // addMoveToPointData("coordPoint1",  
    //     0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.1,  0.1
    // );
    // addMoveToPointData("coordPoint2",  
    //     0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.1,  0.1
    // );
    // addMoveToPointData("coordPoint3",  
    //     0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.1,  0.1
    // );
    // addMoveToJointData("jointPoint1",  
    //     0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.1,  0.1
    // );
    // addMoveToJointData("jointPoint2",  
    //     0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.1,  0.1
    // );
    // addMoveToJointData("jointPoint3",  
    //     0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.1,  0.1
    // );
    // addMoveRelativeData("moveRelativeX", 0.1, 0.0, 0.0);
    // addMoveRelativeData("moveRelativeY", 0.0, 0.1, 0.0);
    // addMoveRelativeData("moveRelativeZ", 0.0, 0.0, 0.1);

    // // Manually added tasks. 
    // addTaskData("home", { "home" });
    // addTaskData("coordPoint1", { "coordPoint1" });
    // addTaskData("coordPoint2", { "coordPoint2" });
    // addTaskData("coordPoint3", { "coordPoint3" });
    // addTaskData("jointPoint1", { "jointPoint1" });
    // addTaskData("jointPoint2", { "jointPoint2" });
    // addTaskData("jointPoint3", { "jointPoint3" });
    // addTaskData("moveRelativeX", { "moveRelativeX" });
    // addTaskData("moveRelativeY", { "moveRelativeY" });
    // addTaskData("moveRelativeZ", { "moveRelativeZ" });
    // addTaskData("pointSequence", { "coordPoint1", "coordPoint2", "coordPoint3" });
    // addTaskData("jointSequence", { "jointPoint1", "jointPoint2", "jointPoint3" });
    // addTaskData("relativeSequence", { "moveRelativeX", "moveRelativeY", "moveRelativeZ" });
    // addTaskData("mixedPointJoint", { "coordPoint1", "jointPoint2", "coordPoint3" });
    // addTaskData("mixedPointRelative", { "coordPoint1", "moveRelativeX" "coordPoint2"});
    // addTaskData("mixedJointPoint", { "jointPoint1", "coordPoint2", "jointPoint3" });
    // addTaskData("mixedJointRelative", { "jointPoint1", "moveRelativeY", "jointPoint2" });
    // addTaskData("mixedRelativePoint", { "moveRelativex", "coordPoint1", "moveRelativeY" });
    // addTaskData("mixedRelativeJoint", { "moveRelativeY", "jointPoint1", "moveRelativeZ" });
    // addTaskData("allStageSequence", 
    //     {"home", "coordPoint1", "jointPoint1", "moveRelativeX", "coordPoint2", "jointPoint2",
    //      "moveRelativeY", "coordPoint3", "jointPoint3", "moveRelativeZ"}
    // );
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
