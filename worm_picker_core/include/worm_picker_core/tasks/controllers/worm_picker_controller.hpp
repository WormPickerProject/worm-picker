// worm_picker_controller.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef WORM_PICKER_CONTROLLER_HPP
#define WORM_PICKER_CONTROLLER_HPP

#include <rclcpp/rclcpp.hpp>

#include "worm_picker_core/exceptions/exceptions.hpp"
#include "worm_picker_core/tasks/task_factory.hpp"
#include "worm_picker_core/tasks/controllers/action_client_manager.hpp"
#include "worm_picker_core/tasks/controllers/parameter_manager.hpp"
#include "worm_picker_core/tasks/controllers/service_handler.hpp"
#include "worm_picker_core/tasks/controllers/task_manager.hpp"
#include "worm_picker_core/tools/timing/execution_timer.hpp"
#include "worm_picker_core/tools/timing/timer_data_collector.hpp"

/**
 * @class WormPickerController
 * @brief Main controller for the WormPicker system
 * 
 * @details
 * Coordinates all major components of the WormPicker system including:
 * - Parameter management
 * - Task creation and execution
 * - Action client handling
 * - Service handling
 * - Timing data collection
 */
class WormPickerController {
public:
    // Public Type Aliases
    using NodeBaseInterfacePtr = rclcpp::node_interfaces::NodeBaseInterface::SharedPtr;

    /**
     * @brief Constructs a WormPicker controller
     * 
     * @param options ROS2 node options for configuration
     * @throws std::runtime_error if component initialization fails
     */
    explicit WormPickerController(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());

    /**
     * @brief Gets the base interface of the controller's node
     * 
     * @return Shared pointer to the node's base interface
     */
    NodeBaseInterfacePtr getBaseInterface() const;

private:
    // Private Type Aliases
    using NodePtr = rclcpp::Node::SharedPtr;
    using TaskFactoryPtr = std::shared_ptr<TaskFactory>;
    using ActionClientManagerPtr = std::shared_ptr<ActionClientManager>;
    using ParameterManagerPtr = std::shared_ptr<ParameterManager>;
    using ServiceHandlerPtr = std::shared_ptr<ServiceHandler>;
    using TaskManagerPtr = std::shared_ptr<TaskManager>;
    using TimerDataCollectorPtr = std::shared_ptr<TimerDataCollector>;

    /**
     * @brief Initializes all controller components in proper order
     * @throws std::runtime_error if initialization fails
     */
    void initializeComponents();

    // ROS 2 Components
    NodePtr node_;                                    ///< Main ROS2 node

    // WormPicker Components
    TaskFactoryPtr task_factory_;                     ///< Creates task instances
    ActionClientManagerPtr action_client_manager_;    ///< Manages action client connections
    ParameterManagerPtr parameter_manager_;           ///< Handles parameter management
    ServiceHandlerPtr service_handler_;               ///< Handles service requests
    TaskManagerPtr task_manager_;                     ///< Manages task execution
    TimerDataCollectorPtr timer_data_collector_;      ///< Collects timing data
};

#endif // WORM_PICKER_CONTROLLER_HPP
