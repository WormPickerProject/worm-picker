// plate_calibration.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef PLATE_CALIBRATION_HPP
#define PLATE_CALIBRATION_HPP

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <worm_picker_custom_msgs/srv/task_command.hpp>
#include <moveit_task_constructor_msgs/action/execute_task_solution.hpp>
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>

#include "worm_picker_core/stages/move_to_joint_data.hpp"

class PlateCalibration {
public:
    explicit PlateCalibration(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
    rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getNodeBase() const {
        return node_->get_node_base_interface();
    }

private:
    using TaskCommandService = worm_picker_custom_msgs::srv::TaskCommand;
    using TaskCommandRequest = TaskCommandService::Request;
    using TaskCommandResponse = TaskCommandService::Response;
    using ExecTaskSolutionAction = moveit_task_constructor_msgs::action::ExecuteTaskSolution;
    using Task = moveit::task_constructor::Task;
    using CurrentStateStage = moveit::task_constructor::stages::CurrentState;

    static constexpr int MAX_PLANNING_ATTEMPTS = 5;
    static constexpr int MAX_SERVER_RETRIES = 10;
    static constexpr auto SERVER_TIMEOUT = std::chrono::seconds{3};
    const std::string DEFAULT_END_EFFECTOR = "eoat_tcp";

    void setupServices();
    void initializeCalibrationPoints();
    Task createMoveToPlateTask(const MoveToJointData& point) const;
    bool executeTask(Task& task) const;
    void handleUserInput(const std::shared_ptr<const TaskCommandRequest>& request,
                         const std::shared_ptr<TaskCommandResponse>& response);
    void processNextPlate();
    Task createBaseTask(std::string_view command) const;
    void declareParameters();
    void waitForServer();

    rclcpp::Node::SharedPtr node_;
    rclcpp_action::Client<ExecTaskSolutionAction>::SharedPtr action_client_;
    rclcpp::Service<TaskCommandService>::SharedPtr task_command_service_;
    std::jthread wait_thread_;
    std::vector<MoveToJointData> points_;
    std::vector<MoveToJointData>::iterator current_point_it_;
    bool calibration_active_{true};
};

#endif // PLATE_CALIBRATION_HPP
