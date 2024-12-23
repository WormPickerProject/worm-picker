cmake_minimum_required(VERSION 3.8)
project(worm_picker_core)

#
# ---------------------------
# C++ Standard and Build Type
# ---------------------------
#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

#
# ---------------------------
# Compiler Options
# ---------------------------
#
function(set_compiler_options)
  if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
  endif()
  add_compile_options(-g)
endfunction()
set_compiler_options()

#
# ---------------------------
# Find Dependencies
# ---------------------------
#
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(worm_picker_custom_msgs REQUIRED)

# MoveIt & TF
find_package(moveit_core REQUIRED)
find_package(moveit_msgs REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(moveit_task_constructor_core REQUIRED)
find_package(moveit_task_constructor_msgs REQUIRED)
find_package(moveit_task_constructor_visualization REQUIRED)
find_package(moveit_ros_planning REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2_eigen REQUIRED)

# Additional dependencies found in source code
find_package(fmt REQUIRED)
find_package(yaml-cpp REQUIRED)

# Misc
find_package(motoros2_interfaces REQUIRED)
find_package(std_srvs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(worm_picker_moveit_config REQUIRED)

# Export dependencies for downstream packages
ament_export_dependencies(
  rosidl_default_runtime
  rclcpp
  geometry_msgs
  moveit_core
  moveit_ros_planning_interface
  moveit_task_constructor_core
  moveit_task_constructor_msgs
  tf2
  tf2_geometry_msgs
  worm_picker_custom_msgs
  motoros2_interfaces
)

#
# ---------------------------
# Include Directories
# ---------------------------
#
include_directories(
  include
  ${moveit_core_INCLUDE_DIRS}
  ${moveit_ros_planning_interface_INCLUDE_DIRS}
  ${moveit_task_constructor_core_INCLUDE_DIRS}
  ${geometry_msgs_INCLUDE_DIRS}
  ${tf2_INCLUDE_DIRS}
  ${tf2_geometry_msgs_INCLUDE_DIRS}
)

#
# ---------------------------
# Group Repeated Dependencies
# ---------------------------
#
set(MOVEIT_DEPS
  moveit_core
  moveit_msgs
  moveit_ros_planning
  moveit_ros_planning_interface
  moveit_task_constructor_core
  moveit_task_constructor_msgs
  moveit_task_constructor_visualization
)

set(ROS_DEPS
  rclcpp
  tf2
  tf2_geometry_msgs
  tf2_eigen
  std_srvs
  geometry_msgs
)

set(WORM_PICKER_DEPS
  ${MOVEIT_DEPS}
  ${ROS_DEPS}
  worm_picker_custom_msgs
  motoros2_interfaces
)

#
# ---------------------------
# Library Setup
# ---------------------------
#
add_library(${PROJECT_NAME} SHARED
  # Infrastructure
  src/infrastructure/interface/cli/cal_command_interface.cpp
  src/infrastructure/interface/cli/core_command_interface.cpp
  src/infrastructure/interface/network/ros_command_client.cpp
  src/infrastructure/interface/network/tcp_socket_server.cpp
  src/infrastructure/parsers/calibration_points_parser.cpp
  src/infrastructure/parsers/defined_tasks_parser.cpp
  src/infrastructure/parsers/hotel_data_parser.cpp
  src/infrastructure/parsers/workstation_data_parser.cpp
  src/infrastructure/parsers/workstation_geometry_parser.cpp
  
  # System
  src/system/calibration/calibration_state_machine.cpp
  src/system/calibration/plate_position_analyzer.cpp
  src/system/calibration/robot_controller.cpp
  src/system/calibration/workstation_json_generator.cpp
  src/system/management/action_client_manager.cpp
  src/system/management/parameter_manager.cpp
  src/system/management/service_handler.cpp
  src/system/management/task_manager.cpp
  src/system/tasks/generation/base_task_generator.cpp
  src/system/tasks/generation/generate_hotel_task_generator.cpp
  src/system/tasks/generation/generate_relative_movement_task.cpp
  src/system/tasks/generation/generate_workstation_task_generator.cpp
  src/system/tasks/task_factory.cpp
  src/system/tasks/task_generator.cpp
  src/system/tasks/task_validator.cpp
  
  # Utils
  src/utils/execution_timer.cpp
  src/utils/timer_data_collector.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_compile_features(${PROJECT_NAME} PUBLIC c_std_99 cxx_std_20)

# Add dependencies to the library
ament_target_dependencies(${PROJECT_NAME}
  ${WORM_PICKER_DEPS}
  fmt
  yaml-cpp
)

#
# ---------------------------
# Executable Setup Function
# ---------------------------
#
function(add_worm_picker_executable target_name)
  cmake_parse_arguments(EXE "" "" "SOURCES;DEPS" ${ARGN})

  add_executable(${target_name} ${EXE_SOURCES})

  target_include_directories(${target_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )

  target_compile_features(${target_name} PUBLIC c_std_99 cxx_std_20)
  
  # Link against our main library
  target_link_libraries(${target_name}
    ${PROJECT_NAME}
  )

  if(EXE_DEPS)
    ament_target_dependencies(${target_name}
      ${EXE_DEPS}
    )
  endif()

  install(TARGETS ${target_name}
    DESTINATION lib/${PROJECT_NAME}
  )
endfunction()

#
# ---------------------------
# Executables
# ---------------------------
#

## Worm Picker Robot
add_worm_picker_executable(worm_picker_robot
  SOURCES
    src/apps/worm_picker_main.cpp
  DEPS
    ${WORM_PICKER_DEPS}
)

## Service Client (core_command_interface)
add_worm_picker_executable(core_command_interface
  SOURCES
    src/apps/core_command_interface_main.cpp
  DEPS
    rclcpp
    worm_picker_custom_msgs
)

## Service Client (calibration_command_interface)
add_worm_picker_executable(cal_command_interface
  SOURCES
    src/apps/cal_command_interface_main.cpp
  DEPS
    rclcpp
    worm_picker_custom_msgs
)

## Plate Calibration
add_worm_picker_executable(plate_calibration
  SOURCES
    src/apps/plate_calibration_main.cpp
  DEPS
    ${WORM_PICKER_DEPS}
)

#
# ---------------------------
# Install
# ---------------------------
#
install(
  TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
  DIRECTORY include/
  DESTINATION include
)

install(
  DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/
)

install(
  DIRECTORY config/
  DESTINATION share/${PROJECT_NAME}/
)

#
# ---------------------------
# Testing
# ---------------------------
#
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

#
# ---------------------------
# Package Export
# ---------------------------
#
ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(${WORM_PICKER_DEPS})
ament_package()