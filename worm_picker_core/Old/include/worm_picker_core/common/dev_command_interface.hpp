// dev_command_interface.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef DEV_COMMAND_INTERFACE_HPP
#define DEV_COMMAND_INTERFACE_HPP

#include <rclcpp/rclcpp.hpp> 
#include <worm_picker_custom_msgs/srv/task_command.hpp> 

class DevCommandInterface
{
public:
    DevCommandInterface(int argc, char **argv);
    void runCommandLoop();

private:
    void initializeROS(int argc, char **argv);
    void waitForService();
    std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Request> createRequest(const std::string& command) const;
    void sendRequest(const std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Request>& request) const;
    void receiveResponse(const rclcpp::Client<worm_picker_custom_msgs::srv::TaskCommand>::SharedFuture& result_future) const;
    
    // Type aliases
    using TaskCommandService = worm_picker_custom_msgs::srv::TaskCommand;

    rclcpp::Node::SharedPtr node_;  // Shared pointer to the ROS node
    rclcpp::Client<TaskCommandService>::SharedPtr client_;  // Shared pointer to the service client
    std::string service_name_;  // Name of the service
};

#endif // DEV_COMMAND_INTERFACE_HPP
