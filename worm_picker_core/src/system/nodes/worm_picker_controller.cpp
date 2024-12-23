// worm_picker_controller.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/system/nodes/worm_picker_controller.hpp"

WormPickerController::WormPickerController(const rclcpp::NodeOptions& options)
    : node_{std::make_shared<rclcpp::Node>("worm_picker_controller", options)}
{
    if (!node_) {
        throw std::runtime_error("Failed to create WormPicker controller node");
    }
    
    try {
        initializeComponents();
    } catch (const std::exception& e) {
        throw std::runtime_error(
            std::string("Failed to initialize WormPicker controller components: ") + e.what());
    }
}

void WormPickerController::initializeComponents() 
{
    parameter_manager_ = std::make_shared<ParameterManager>(node_);
    task_factory_ = std::make_shared<TaskFactory>(node_);
    timer_data_collector_ = std::make_shared<TimerDataCollector>(node_);
    action_client_manager_ = std::make_shared<ActionClientManager>(node_);
    task_manager_ = std::make_shared<TaskManager>(
        node_,
        task_factory_,
        timer_data_collector_
    );
    service_handler_ = std::make_shared<ServiceHandler>(
        node_,
        task_manager_,
        action_client_manager_
    );
}

WormPickerController::NodeBaseInterfacePtr WormPickerController::getBaseInterface() const 
{
    return node_->get_node_base_interface();
}