// plate_calibration.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/calibration/plate_calibration.hpp"

PlateCalibration::PlateCalibration(const rclcpp::NodeOptions& options) 
    : node_{std::make_shared<rclcpp::Node>("calibration_node", options)}
{
    declareParameters();
    initializeCalibrationPoints();
    setupServices();
}

void PlateCalibration::initializeCalibrationPoints() 
{
    points_ = {
        {0.00, 58.23, 59.02, 0.00, -30.35, -0.01},
        {-24.59, 42.54, 32.44, 0.01, -19.48, -0.02},
        {24.81, 42.54, 32.45, 0.01, -19.48, -0.02},
        {0.00, 0.00, 0.00, 0.00, 0.00, 0.00}
    };
    current_point_it_ = points_.begin();
}

void PlateCalibration::setupServices() 
{
    action_client_ = rclcpp_action::create_client<ExecTaskSolutionAction>(
        node_, "/execute_task_solution"
    );

    wait_thread_ = std::jthread{[this] { waitForServer(); }};

    task_command_service_ = node_->create_service<TaskCommandService>(
        "/task_command",
        [this](const std::shared_ptr<const TaskCommandRequest>& request,
               const std::shared_ptr<TaskCommandResponse>& response) {
            handleUserInput(request, response);
        }
    );
}

void PlateCalibration::waitForServer() 
{
    for (int retry_count = 0; rclcpp::ok() && retry_count < MAX_SERVER_RETRIES; ++retry_count) {
        if (action_client_->wait_for_action_server(SERVER_TIMEOUT)) {
            return;
        }
    }
}

PlateCalibration::Task PlateCalibration::createMoveToPlateTask(const MoveToJointData& point) const 
{
    auto task = createBaseTask("command");
    task.add(std::make_unique<CurrentStateStage>("current"));

    auto stage = point.createStage("move_to_target", node_);
    task.add(std::move(stage));

    return task;
}

PlateCalibration::Task PlateCalibration::createBaseTask(std::string_view command) const
{
    Task task;
    task.stages()->setName(std::string{command});
    task.loadRobotModel(node_);

    task.setProperty("group", "gp4_arm");
    const auto current_end_effector = 
        node_->get_parameter("end_effector").as_string();
    task.setProperty("ik_frame", current_end_effector);

    moveit::task_constructor::TrajectoryExecutionInfo execution_info;
    execution_info.controller_names = {"follow_joint_trajectory"};
    task.setProperty("trajectory_execution_info", execution_info);

    return task;
}

bool PlateCalibration::executeTask(Task& task) const 
{
    const auto logger = node_->get_logger();

    task.init();

    if (!task.plan(MAX_PLANNING_ATTEMPTS)) {
        RCLCPP_ERROR(logger, "Task planning failed");
        return false;
    }

    if (task.solutions().empty()) {
        RCLCPP_ERROR(logger, "No solutions found");
        return false;
    }

    const auto& solution = *task.solutions().front();
    task.introspection().publishSolution(solution);
    const auto result = task.execute(solution);

    if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
        RCLCPP_ERROR(logger, "Task execution failed");
        return false;
    }

    return true;
}

void PlateCalibration::handleUserInput(const std::shared_ptr<const TaskCommandRequest>& request,
                                       const std::shared_ptr<TaskCommandResponse>& response) 
{
    if (!calibration_active_) {
        RCLCPP_WARN(node_->get_logger(), "Calibration completed. No further commands accepted.");
        response->success = false;
        return;
    }

    if (request->command != "next") {
        RCLCPP_WARN(node_->get_logger(), "Unknown command: %s", request->command.c_str());
        response->success = false;
        return;
    }

    processNextPlate();
    response->success = true;
}

void PlateCalibration::processNextPlate() 
{
    if (current_point_it_ != points_.end()) {
        auto task = createMoveToPlateTask(*current_point_it_);
        bool success = executeTask(task);
        (void)success;
        ++current_point_it_;
    }
        
    if (current_point_it_ == points_.end()) {
        calibration_active_ = false;
    }
}

void PlateCalibration::declareParameters() 
{
    node_->declare_parameter("end_effector", DEFAULT_END_EFFECTOR);
}

int main(int argc, char **argv) 
{
    rclcpp::init(argc, argv);

    auto plate_calibration = std::make_shared<PlateCalibration>(
        rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));
    
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(plate_calibration->getNodeBase());

    executor.spin();

    executor.remove_node(plate_calibration->getNodeBase());
    rclcpp::shutdown();

    return 0;
}
