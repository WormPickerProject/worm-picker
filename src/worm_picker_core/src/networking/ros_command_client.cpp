#include "worm_picker_core/networking/ros_command_client.hpp"

RosCommandClient::RosCommandClient(int argc, char **argv) 
{
    rclcpp::init(argc, argv);
    ros_node_instance_ = rclcpp::Node::make_shared("ros_command_client");

    task_command_client_ = ros_node_instance_->create_client<worm_picker_custom_msgs::srv::TaskCommand>("/task_command");
    start_trajectory_mode_client_ = ros_node_instance_->create_client<motoros2_interfaces::srv::StartTrajMode>("/start_traj_mode");
    stop_trajectory_mode_client_ = ros_node_instance_->create_client<std_srvs::srv::Trigger>("/stop_traj_mode");

    initializeSocketCommandHandlers();
}

void RosCommandClient::initializeSocketCommandHandlers() 
{
    auto self = shared_from_this();

    socket_command_function_map_["startWormPicker"] = [self](std::function<void(bool)> result_callback) { 
        RCLCPP_INFO(self->ros_node_instance_->get_logger(), "Start robot command received. Starting robot.");
        auto start_request = std::make_shared<motoros2_interfaces::srv::StartTrajMode::Request>();
        self->start_trajectory_mode_client_->async_send_request(start_request,
            [self, result_callback](rclcpp::Client<motoros2_interfaces::srv::StartTrajMode>::SharedFuture start_future) {
                auto start_result = start_future.get();
                result_callback(start_result->result_code.value == motoros2_interfaces::msg::MotionReadyEnum::READY);
            });
    };

    /* Does not work yet. 
        socket_command_function_map_["stopWormPicker"] = [self](std::function<void(bool)> result_callback) { 
            RCLCPP_INFO(self->ros_node_instance_->get_logger(), "Stop robot command received. Stopping robot.");
            auto stop_request = std::make_shared<std_srvs::srv::Trigger::Request>();
            self->stop_trajectory_mode_client_->async_send_request(stop_request,
                [self, result_callback](rclcpp::Client<std_srvs::srv::Trigger>::SharedFuture stop_future) {
                auto stop_result = stop_future.get();
                result_callback(stop_result->success);
            });
        };
    

        socket_command_function_map_["launchWormPickerApplication"] = [this](std::function<void(bool)> result_callback) {
            RCLCPP_INFO(ros_node_instance_->get_logger(), "Launch robot application command received. Launching application.");
            auto launch_service = std::make_shared<launch::LaunchService>(ros_node_instance_->get_context());
            auto launch_description = std::make_shared<launch::LaunchDescription>(
                std::vector<launch::Action::SharedPtr>{
                    std::make_shared<launch::actions::ExecuteProcess>(
                        std::vector<std::string>{"ros2", "launch", "wp_application", "moveit_gp4_rviz.launch.py"})
                });

            std::jthread([launch_service, launch_description]() {
                launch_service->include_launch_description(launch_description);
                launch_service->run();
            });
            result_callback(true);
        };
    */

    // socket_command_function_map_["launchWormPickerApplication"] = [this](std::function<void(bool)> result_callback) {
    //     RCLCPP_INFO(ros_node_instance_->get_logger(), "Launch robot application command received. Launching application.");
    //     std::jthread([]() {
    //         std::string command = "ros2 launch wp_application moveit_gp4_rviz.launch.py";
    //         system(command.c_str());
    //     });
    //     result_callback(true);
    // };

    socket_command_function_map_["quit"] = [self](std::function<void(bool)> result_callback) { 
        RCLCPP_INFO(self->ros_node_instance_->get_logger(), "Quit command received. Shutting down.");
        rclcpp::shutdown();
        result_callback(true);
    };
    
    socket_command_function_map_["q"] = socket_command_function_map_["quit"];
}

void RosCommandClient::connectToTaskCommandService() 
{
    rclcpp::Rate rate(0.2);
    while (rclcpp::ok() && !task_command_client_->wait_for_service(std::chrono::seconds(5))) {
        rate.sleep();
    }
    RCLCPP_INFO(ros_node_instance_->get_logger(), "Connected to task command service.");
}

void RosCommandClient::runSocketServer(int server_port) 
{
    auto socket_server_instance = std::make_unique<TcpSocketServer>(server_port);
    std::weak_ptr<RosCommandClient> weak_self_instance = shared_from_this();

    socket_server_instance->setCommandHandler([weak_self_instance](const std::string &received_command, std::function<void(bool)> result_callback) {
        auto self_instance = weak_self_instance.lock();
        if (self_instance) {
            self_instance->handleReceivedSocketCommand(received_command, result_callback);
        }
    });

    RCLCPP_INFO(ros_node_instance_->get_logger(), "Starting server.");
    socket_server_instance->startServer();

    rclcpp::executors::MultiThreadedExecutor ros_executor;
    ros_executor.add_node(ros_node_instance_);
    ros_executor.spin();

    RCLCPP_INFO(ros_node_instance_->get_logger(), "Stopping server.");
    socket_server_instance->stopServer();
}

void RosCommandClient::handleReceivedSocketCommand(const std::string &received_command, std::function<void(bool)> result_callback) 
{
    auto command_iterator = socket_command_function_map_.find(received_command);
    if (command_iterator != socket_command_function_map_.end()) {
        command_iterator->second(result_callback); 
    } else {
        auto task_command_request = std::make_shared<worm_picker_custom_msgs::srv::TaskCommand::Request>();
        task_command_request->command = received_command;
        sendTaskCommandServiceRequest(task_command_request, result_callback);
    }
}

void RosCommandClient::sendTaskCommandServiceRequest(const std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand::Request>& task_command_request, std::function<void(bool)> result_callback) 
{
    RCLCPP_INFO(ros_node_instance_->get_logger(), "Task command received. Tasking robot.");
    auto self = shared_from_this();
    task_command_client_->async_send_request(task_command_request, 
        [self, result_callback](rclcpp::Client<worm_picker_custom_msgs::srv::TaskCommand>::SharedFuture task_result_future) { 
            auto task_result = task_result_future.get();
            result_callback(task_result->success); 
        });
}

int main(int argc, char **argv) 
{
    auto ros_command_client_instance = std::make_shared<RosCommandClient>(argc, argv);
    
    std::jthread task_command_service_thread([&]() { 
        ros_command_client_instance->connectToTaskCommandService();
    });

    ros_command_client_instance->runSocketServer(DEFAULT_SOCKET_SERVER_PORT);
    
    return 0;
}