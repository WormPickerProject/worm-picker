#ifndef COMMAND_CLIENT_HPP
#define COMMAND_CLIENT_HPP

#include <rclcpp/rclcpp.hpp> 
#include <worm_picker_custom_msgs/srv/task_command.hpp> 

class CommandClient 
{
public:
    CommandClient(int argc, char **argv);
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

#endif // COMMAND_CLIENT_HPP