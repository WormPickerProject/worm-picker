// worm_picker_main.cpp

#include "worm_picker_core/tasks/worm_picker_task_controller.hpp"

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  rclcpp::NodeOptions options;
  options.automatically_declare_parameters_from_overrides(true);

  auto worm_picker_node = std::make_shared<WormPickerTaskController>(options);
  rclcpp::executors::MultiThreadedExecutor executor;

  auto spin_thread = std::make_unique<std::thread>([&executor, &worm_picker_node]() {
    executor.add_node(worm_picker_node->getNodeBaseInterface());
    executor.spin();
    executor.remove_node(worm_picker_node->getNodeBaseInterface());
  });

  spin_thread->join();
  rclcpp::shutdown();
  return 0;
}