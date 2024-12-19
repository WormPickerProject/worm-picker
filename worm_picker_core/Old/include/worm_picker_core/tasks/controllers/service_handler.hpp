// service_handler.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef SERVICE_HANDLER_HPP
#define SERVICE_HANDLER_HPP

#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <worm_picker_custom_msgs/srv/task_command.hpp>

#include "worm_picker_core/tasks/controllers/task_manager.hpp"
#include "worm_picker_core/tasks/controllers/action_client_manager.hpp"

/**
 * @class ServiceHandler
 * @brief Handles ROS2 service requests for task execution
 * 
 * @details
 * Manages the creation and handling of ROS2 services for task command execution.
 * Coordinates between the TaskManager and ActionClientManager to process requests.
 */
class ServiceHandler {
public:
    // Public Type Aliases
    using NodePtr = rclcpp::Node::SharedPtr;
    using TaskManagerPtr = std::shared_ptr<TaskManager>;
    using ActionClientManagerPtr = std::shared_ptr<ActionClientManager>;

    /**
     * @brief Constructs a ServiceHandler
     * 
     * @param node ROS2 node to create services on
     * @param task_manager Task management component
     * @param action_client_manager Action client management component
     */
    ServiceHandler(const NodePtr& node, 
                   const TaskManagerPtr& task_manager, 
                   const ActionClientManagerPtr& action_client_manager);

private:
    // Private Type Aliases
    using TaskCommandService = worm_picker_custom_msgs::srv::TaskCommand;
    using TaskCommandRequest = TaskCommandService::Request;
    using TaskCommandResponse = TaskCommandService::Response;
    using TaskCommandServicePtr = rclcpp::Service<TaskCommandService>::SharedPtr;

    /**
     * @brief Handles incoming service requests
     * 
     * @param request The service request containing the task command
     * @param response The service response to be filled
     * @throws std::runtime_error if action server is not available
     */
    void handleServiceRequest(const std::shared_ptr<const TaskCommandRequest>& request,
                              const std::shared_ptr<TaskCommandResponse>& response);
    
    // ROS 2 Components
    NodePtr node_;                                    ///< ROS2 node handle
    TaskCommandServicePtr service_;                   ///< Service handle

    // WormPicker Components
    TaskManagerPtr task_manager_;                     ///< Task management component
    ActionClientManagerPtr action_client_manager_;    ///< Action client component
};

#endif // SERVICE_HANDLER_HPP
