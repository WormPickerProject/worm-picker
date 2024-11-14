// worm_picker_controller.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tasks/controllers/worm_picker_controller.hpp"

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

int main(int argc, char **argv) 
{
    rclcpp::init(argc, argv);

    auto worm_picker_controller = std::make_shared<WormPickerController>(
        rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));
    
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(worm_picker_controller->getBaseInterface());

    executor.spin();

    executor.remove_node(worm_picker_controller->getBaseInterface());
    rclcpp::shutdown();

    return 0;
}