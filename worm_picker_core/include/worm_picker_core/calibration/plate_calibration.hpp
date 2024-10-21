// plate_calibration.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
//
// Licensed under the Apache License, Version 2.0 (the "License");

#ifndef PLATE_CALIBRATION_HPP
#define PLATE_CALIBRATION_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <map>


// ROS Service and Action includes
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <worm_picker_custom_msgs/srv/task_command.hpp>
#include <moveit_task_constructor_msgs/action/execute_task_solution.hpp>

// MoveIt Task Constructor includes
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>

// MoveIt and TF includes
#include <moveit/robot_model/robot_model.h>
#include <tf2/LinearMath/Quaternion.h>
#include <geometry_msgs/msg/pose_stamped.hpp>

class PlateCalibration
{
public:
    explicit PlateCalibration(int argc, char **argv);
    rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getNodeBase() { return calibration_node_->get_node_base_interface(); }

    struct Point {
        std::map<std::string, double> joint_positions;
        
        Point() = default;
        Point(double joint1, double joint2, double joint3, double joint4, double joint5, double joint6);
    };

private:
    void setupServices();
    void createMoveToPlateTask(const Point& point, 
                               double velocity_scaling_factor, 
                               double acceleration_scaling_factor);
    void executeCurrentTask(moveit::task_constructor::Task& current_task);
    void handleUserInput(const std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Request> request,
                         std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Response> response);
    void processNextPlate();

    rclcpp::Node::SharedPtr calibration_node_;
    rclcpp_action::Client<moveit_task_constructor_msgs::action::ExecuteTaskSolution>::SharedPtr task_execution_client_;
    rclcpp::Service<worm_picker_custom_msgs::srv::TaskCommand>::SharedPtr task_command_service_;

    // moveit::task_constructor::Task current_task_;

    std::vector<Point> points_;
    std::vector<Point>::iterator current_point_it_;
    
    bool calibration_active_;
};

#endif // PLATE_CALIBRATION_HPP