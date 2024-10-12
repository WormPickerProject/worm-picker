// worm_picker_main.cpp
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