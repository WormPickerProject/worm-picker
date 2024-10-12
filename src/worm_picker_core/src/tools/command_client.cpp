#include "worm_picker_core/tools/command_client.hpp"

CommandClient::CommandClient(int argc, char **argv) 
    : service_name_("task_command")
{
    initializeROS(argc, argv);
}

void CommandClient::initializeROS(int argc, char **argv) 
{
    rclcpp::init(argc, argv);
    node_ = rclcpp::Node::make_shared("command_client");
    client_ = node_->create_client<worm_picker_custom_msgs::srv::TaskCommand>(service_name_);
    waitForService();
}

void CommandClient::waitForService() 
{
    while (!client_->wait_for_service(std::chrono::seconds(1))) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(node_->get_logger(), "Interrupted while waiting for the service. Exiting.");
            rclcpp::shutdown();
            exit(1);
        }
    }
    RCLCPP_INFO(node_->get_logger(), "Service '%s' is available.", service_name_.c_str());
}

std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Request> CommandClient::createRequest(const std::string& command) const 
{
    auto request = std::make_shared<worm_picker_custom_msgs::srv::TaskCommand::Request>();
    request->command = command;
    return request;
}

void CommandClient::sendRequest(const std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Request>& request) const 
{
    auto result_future = client_->async_send_request(request);
    receiveResponse(result_future.share());
}

void CommandClient::receiveResponse(const rclcpp::Client<worm_picker_custom_msgs::srv::TaskCommand>::SharedFuture& result_future) const 
{
    if (rclcpp::spin_until_future_complete(node_, result_future) == rclcpp::FutureReturnCode::SUCCESS) {
        auto result = result_future.get();
        if (!result->success) {
            RCLCPP_ERROR(node_->get_logger(), "Task execution failed.");
        }
    } else {
        RCLCPP_ERROR(node_->get_logger(), "Failed to call service.");
    }
}

void CommandClient::runCommandLoop() 
{
    std::string command;
    while (rclcpp::ok()) {
        std::cout << "Enter command (home, pointA, point1, point2, pickUpPlate, quit): ";
        std::cin >> command;

        if (command == "quit" || command == "q") {
            break;
        }

        auto request = createRequest(command);
        sendRequest(request);
    }
}

int main(int argc, char **argv) 
{
    auto command_client = std::make_shared<CommandClient>(argc, argv);
    command_client->runCommandLoop();

    rclcpp::shutdown();
    return 0;
}