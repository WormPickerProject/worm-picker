// dev_command_interface.hpp
//
// Copyright (c) 2024 Logan Kaising
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

    rclcpp::Node::SharedPtr node_;  // Shared pointer to the ROS node
    rclcpp::Client<worm_picker_custom_msgs::srv::TaskCommand>::SharedPtr client_;  // Shared pointer to the service client
    std::string service_name_;  // Name of the service
};

#endif // DEV_COMMAND_INTERFACE_HPP
