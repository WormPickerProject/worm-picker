// plate_calibration.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/calibration/plate_calibration.hpp"
#include <cmath>

PlateCalibration::Point::Point(
    double joint1, double joint2, double joint3, double joint4, double joint5, double joint6)
{
    const double deg_to_rad = M_PI / 180.0;

    joint_positions["joint_1"] = joint1 * deg_to_rad;
    joint_positions["joint_2"] = joint2 * deg_to_rad;
    joint_positions["joint_3"] = joint3 * deg_to_rad;
    joint_positions["joint_4"] = joint4 * deg_to_rad;
    joint_positions["joint_5"] = joint5 * deg_to_rad;
    joint_positions["joint_6"] = joint6 * deg_to_rad;
}

PlateCalibration::PlateCalibration(int argc, char **argv) 
    : calibration_active_(true)
{
    rclcpp::init(argc, argv);
    
    rclcpp::NodeOptions options;
    options.automatically_declare_parameters_from_overrides(true);

    calibration_node_ = std::make_shared<rclcpp::Node>("calibration_node", options);

    points_ = {
        {0.00, 58.23, 59.02, 0.00, -30.35, -0.01},
        {-24.59, 42.54, 32.44, 0.01, -19.48, -0.02},
        {24.81, 42.54, 32.45, 0.01, -19.48, -0.02},
        {0.00, 0.00, 0.00, 0.00, 0.00, 0.00}
    };

    current_point_it_ = points_.begin();

    setupServices();
}

void PlateCalibration::setupServices() 
{
    task_execution_client_ = rclcpp_action::create_client<
        moveit_task_constructor_msgs::action::ExecuteTaskSolution>(
            calibration_node_, 
            "/execute_task_solution"
    );
    
    task_execution_client_->wait_for_action_server(
        std::chrono::seconds(10)
    );

    task_command_service_ = calibration_node_->create_service<
        worm_picker_custom_msgs::srv::TaskCommand>(
            "/task_command", 
            [this](
                const std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Request> request, 
                std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Response> response
            ) {
                handleUserInput(request, response);
            }
    );
}

void PlateCalibration::createMoveToPlateTask(const Point& point, 
                                             double velocity_scaling_factor, 
                                             double acceleration_scaling_factor) 
{
    moveit::task_constructor::Task current_task;

    current_task.stages()->setName("plate");

    current_task.loadRobotModel(calibration_node_);

    const std::string arm_group_name = "gp4_arm";
    current_task.setProperty("group", arm_group_name);

    const std::string controller_name = "follow_joint_trajectory";
    moveit::task_constructor::TrajectoryExecutionInfo exec_info;
    exec_info.controller_names = {controller_name};
    current_task.setProperty("trajectory_execution_info", exec_info);

    auto current_state_stage = std::make_unique<
        moveit::task_constructor::stages::CurrentState>("current");
    current_task.add(std::move(current_state_stage));

    auto joint_interpolation_planner = std::make_shared<
        moveit::task_constructor::solvers::JointInterpolationPlanner>();
    joint_interpolation_planner->setMaxVelocityScalingFactor(velocity_scaling_factor);
    joint_interpolation_planner->setMaxAccelerationScalingFactor(acceleration_scaling_factor);
    
    auto stage = std::make_unique<
        moveit::task_constructor::stages::MoveTo>("move_to_target", joint_interpolation_planner);
    stage->setGoal(point.joint_positions);
    stage->setGroup(arm_group_name);
    stage->setIKFrame("eoat_tcp");
    stage->setProperty("trajectory_execution_info", exec_info);

    current_task.add(std::move(stage));

    executeCurrentTask(current_task);
}

void PlateCalibration::executeCurrentTask(moveit::task_constructor::Task& current_task) 
{
    current_task.init();

    if (!current_task.plan(10)) {
        RCLCPP_ERROR(calibration_node_->get_logger(), "Task planning failed");
        return;
    }

    if (current_task.solutions().empty()) {
        RCLCPP_ERROR(calibration_node_->get_logger(), "No solutions found");
        return;
    }

    current_task.introspection().publishSolution(*current_task.solutions().front());

    auto result = current_task.execute(*current_task.solutions().front());

    if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
        RCLCPP_ERROR(calibration_node_->get_logger(), "Task execution failed");
    }
}

void PlateCalibration::handleUserInput(
    const std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Request> request,
    std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Response> response) 
{
    if (!calibration_active_) {
        RCLCPP_WARN(calibration_node_->get_logger(), "Calibration completed. No further commands are accepted.");
        response->success = false;
        return;
    }

    if (request->command != "next") {
        RCLCPP_WARN(calibration_node_->get_logger(), "Unknown command: %s", request->command.c_str());
        response->success = false;
        return;
    }

    processNextPlate();
    response->success = true;

    // if (!calibration_active_) {
    //     RCLCPP_INFO(calibration_node_->get_logger(), "All points processed. Shutting down.");
    //     rclcpp::shutdown();
    // }
}

void PlateCalibration::processNextPlate() 
{
    if (current_point_it_ != points_.end()) {
        const auto& point = *current_point_it_;

        createMoveToPlateTask(point, 0.1, 0.1);

        current_point_it_++;
    }
        
    if (current_point_it_ == points_.end()) {
        calibration_active_ = false;
    }
}

int main(int argc, char **argv)
{
    auto plate_calibration = std::make_shared<PlateCalibration>(argc, argv);

    rclcpp::spin(plate_calibration->getNodeBase());

    return 0;
}