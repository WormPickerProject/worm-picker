// worm_picker_controller.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/system/tasks/task_factory.hpp"
#include "worm_picker_core/system/management/action_client_manager.hpp"
#include "worm_picker_core/system/management/parameter_manager.hpp"
#include "worm_picker_core/system/management/service_handler.hpp"
#include "worm_picker_core/system/management/task_manager.hpp"
#include "worm_picker_core/utils/execution_timer.hpp"
#include "worm_picker_core/utils/timer_data_collector.hpp"

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
    using NodeBaseInterfacePtr = rclcpp::node_interfaces::NodeBaseInterface::SharedPtr;

    explicit WormPickerController(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
    NodeBaseInterfacePtr getBaseInterface() const;

private:
    using NodePtr = rclcpp::Node::SharedPtr;
    using TaskFactoryPtr = std::shared_ptr<TaskFactory>;
    using ActionClientManagerPtr = std::shared_ptr<ActionClientManager>;
    using ParameterManagerPtr = std::shared_ptr<ParameterManager>;
    using ServiceHandlerPtr = std::shared_ptr<ServiceHandler>;
    using TaskManagerPtr = std::shared_ptr<TaskManager>;
    using TimerDataCollectorPtr = std::shared_ptr<TimerDataCollector>;

    void initializeComponents();

    NodePtr node_;
    TaskFactoryPtr task_factory_;
    ActionClientManagerPtr action_client_manager_;
    ParameterManagerPtr parameter_manager_;
    ServiceHandlerPtr service_handler_;
    TaskManagerPtr task_manager_;
    TimerDataCollectorPtr timer_data_collector_;
};
