// worm_picker_controller.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <ament_index_cpp/get_package_share_directory.hpp>
#include "worm_picker_core/utils/global_node.hpp"
#include "worm_picker_core/system/nodes/worm_picker_controller.hpp"

// Constructor
WormPickerController::WormPickerController(const rclcpp::NodeOptions& options)
    : node_{std::make_shared<rclcpp::Node>("worm_picker_controller", options)}
{
    if (!node_) {
        throw std::runtime_error("Failed to create WormPicker controller node");
    }
    
    // Set the global node for worm_picker
    // This allows other components to access the node instance globally.
    worm_picker::setGlobalNode(node_);
    
    try {
        initializeComponents();
    } catch (const std::exception& e) {
        throw std::runtime_error(
            std::string("Failed to initialize WormPicker controller components: ") + e.what());
    }
}

WormPickerController::~WormPickerController() noexcept 
{
    worm_picker::setGlobalNode(nullptr);
}

// Initialize components
// This function initializes the components of the WormPicker controller.
void WormPickerController::initializeComponents() 
{
    // returns: /home/logan/worm-picker/worm_picker_core directory of main executable
    const std::string package_share_dir = ament_index_cpp::get_package_share_directory("worm_picker_core");
    const auto yaml_path = package_share_dir + "/config/parameters/worm_picker_parameters.yaml";

    // Read config file and set parameters
    parameter_manager_ = std::make_shared<ParameterManager>(node_, yaml_path);

    // Creates task objects given command
    task_factory_ = std::make_shared<TaskFactory>(node_);

    // Creates a timer to collect data from the task manager
    timer_data_collector_ = std::make_shared<TimerDataCollector>(node_);

    // This class interfaces with the action server for executing task solutions
    action_client_manager_ = std::make_shared<ActionClientManager>(node_);
    
    // Creatation, Planning, and Execution of tasks
    task_manager_ = std::make_shared<TaskManager>(
        node_,
        task_factory_,
        timer_data_collector_
    );

    
    service_handler_ = std::make_shared<ServiceHandler>(
        node_,
        task_factory_,
        task_manager_,
        action_client_manager_
    );
}

WormPickerController::NodeBaseInterfacePtr WormPickerController::getBaseInterface() const 
{
    return node_->get_node_base_interface();
}