// worm_picker_task_controller.hpp

#ifndef WORM_PICKER_TASK_CONTROLLER_HPP
#define WORM_PICKER_TASK_CONTROLLER_HPP

// ROS Core and Action includes
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

// ROS Service includes
#include <std_srvs/srv/trigger.hpp>
#include <worm_picker_custom_msgs/srv/task_command.hpp>

// MoveIt Task Constructor includes
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
#include <moveit_task_constructor_msgs/action/execute_task_solution.hpp>

// MoveIt Core and Planning includes
#include <moveit/robot_model/robot_model.h>
#include <moveit/planning_scene/planning_scene.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

// TF2 includes 
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2_eigen/tf2_eigen.hpp>

// Custom application includes
#include "worm_picker_core/tasks/task_data_structure.hpp"
#include "worm_picker_core/tasks/task_factory.hpp"

/**
 * @brief Class that manages the task creation, planning, and execution for the WormPicker project.
 */
class WormPickerTaskController 
{
public:
    /**
     * @brief Constructs the WormPickerTaskController object.
     * @param options Node options passed to the ROS 2 node.
     */
    WormPickerTaskController(const rclcpp::NodeOptions& options);

    /**
     * @brief Gets the NodeBaseInterface of the ROS node.
     * @return A shared pointer to the NodeBaseInterface.
     */
    rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getNodeBaseInterface();

private:
    /**
     * @brief Sets up the ROS service and action client for task commands and execution.
     */
    void setupService();

    /**
     * @brief Handles incoming task commands from the ROS service.
     * @param request The incoming task command request.
     * @param response The response to be sent back indicating success or failure.
     */
    void handleTaskCommand(const std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Request> request,
                           std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Response> response);

    /**
     * @brief Executes a task based on the provided command string.
     * @param command The task command as a string.
     * @return True if the task was successfully executed, otherwise false.
     */
    bool doTask(const std::string& command);

    rclcpp::Node::SharedPtr worm_picker_node_; // The ROS 2 node for the WormPicker system.
    rclcpp::Service<worm_picker_custom_msgs::srv::TaskCommand>::SharedPtr task_command_service_; // The ROS service for handling task command requests.
    rclcpp_action::Client<moveit_task_constructor_msgs::action::ExecuteTaskSolution>::SharedPtr execute_task_action_client_; // The ROS action client for executing task solutions.

    std::shared_ptr<TaskFactory> task_factory_; // A factory object for creating and managing tasks.
    moveit::task_constructor::Task current_task_; // The current task being processed.
};

#endif  // WORM_PICKER_TASK_CONTROLLER_HPP