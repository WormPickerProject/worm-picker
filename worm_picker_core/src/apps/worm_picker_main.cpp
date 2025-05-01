// worm_picker_main.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/system/nodes/worm_picker_controller.hpp"

namespace 
{
    std::atomic_bool g_sigint{false};
    
    void sigintHandler(int) noexcept
    {
        g_sigint.store(true, std::memory_order_relaxed);
    }
} 

int main(int argc, char ** argv)
{
    rclcpp::InitOptions init_opts;
    init_opts.shutdown_on_signal = false;
    rclcpp::init(argc, argv, init_opts);
    std::signal(SIGINT, sigintHandler);

    {
        auto node_opt = rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true);
        auto controller = std::make_shared<WormPickerController>(node_opt);

        rclcpp::executors::MultiThreadedExecutor exec;
        exec.add_node(controller->getBaseInterface());
    
        while (rclcpp::ok() && !g_sigint.load(std::memory_order_relaxed)) {
          exec.spin_some(std::chrono::milliseconds{50});
        }
    
        exec.remove_node(controller->getBaseInterface());
        exec.cancel();
    } 

    rclcpp::shutdown();
    return 0;
}