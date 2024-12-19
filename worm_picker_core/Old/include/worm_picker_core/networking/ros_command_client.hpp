// ros_command_client.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef ROS_COMMAND_CLIENT_HPP
#define ROS_COMMAND_CLIENT_HPP

#include <csignal>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <unordered_map>
#include <functional>
#include <string>

// #include <launch/launch_description.hpp>
// #include <launch/launch_service.hpp>
// #include <launch/actions/execute_process.hpp>

#include <rclcpp/rclcpp.hpp> 
#include <worm_picker_custom_msgs/srv/task_command.hpp> 
#include <motoros2_interfaces/srv/start_traj_mode.hpp> 
#include <std_srvs/srv/trigger.hpp>

#include "worm_picker_core/networking/tcp_socket_server.hpp"

constexpr int DEFAULT_SOCKET_SERVER_PORT = 12345; // Defalut TCP socket server port number

/** 
 * @brief Class representing a ROS command client that interacts with a robot task 
 *        command service and handles incoming commands via a TCP socket server.
 */
class RosCommandClient : public std::enable_shared_from_this<RosCommandClient> 
{
public:
    /** 
     * @brief Constructs a new RosCommandClient object.
     * @param argc Argument count from the command line.
     * @param argv Argument vector from the command line.
     */
    RosCommandClient(int argc, char **argv);

    /** 
     * @brief Connects to the task command service and waits until it becomes available.
     */
    void connectToTaskCommandService();

    /** 
     * @brief Runs the TCP socket server that handles incoming commands on the specified port.
     * @param port Port number on which to run the socket server.
     */
    void runSocketServer(int server_port);

private:
    /** 
     * @brief Sets up command handlers for predefined commands received from the socket server.
     */
    void initializeSocketCommandHandlers();

    /** 
     * @brief Handles incoming commands from the socket server. 
     *        If the command exists in the map, executes the corresponding handler; 
     *        otherwise, sends the command as a task to the task command service.
     * @param received_command The command received as a string.
     * @param result_callback Callback function to handle the result of the command execution.
     */
    void handleReceivedSocketCommand(const std::string &received_command, std::function<void(bool)> result_callback);

    /** 
     * @brief Sends a service request asynchronously to the task command service with the provided command.
     * @param task_command_request The service request to send.
     * @param result_callback Callback function to handle the result of the service request.
     */
    void sendTaskCommandServiceRequest(const std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Request>& task_command_request, std::function<void(bool)> result_callback);

    rclcpp::Node::SharedPtr ros_node_instance_;  // Shared pointer to the ROS node
    rclcpp::Client<worm_picker_custom_msgs::srv::TaskCommand>::SharedPtr task_command_client_;  // Shared pointer to the TaskCommand service client
    rclcpp::Client<motoros2_interfaces::srv::StartTrajMode>::SharedPtr start_trajectory_mode_client_;  // Shared pointer to the StartTrajMode service client
    rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr stop_trajectory_mode_client_;  // Shared pointer to the Trigger service client

    std::unordered_map<std::string, std::function<void(std::function<void(bool)>)>> socket_command_function_map_;  // Map of socket commands to their handlers
};

#endif // ROS_COMMAND_CLIENT_HPP