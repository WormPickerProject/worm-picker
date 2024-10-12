cmake_minimum_required(VERSION 3.8)
project(worm_picker_core)

# ---------------------------
# C++ Standard and Build Type
# ---------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# ---------------------------
# Compiler Options Function
# ---------------------------
function(set_compiler_options)
  if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
  endif()
  
  # Add debug symbols
  add_compile_options(-g)
endfunction()

set_compiler_options()

# ---------------------------
# Find Dependencies
# ---------------------------
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(worm_picker_custom_msgs REQUIRED)
find_package(moveit_core REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(moveit_task_constructor_core REQUIRED)
find_package(moveit_task_constructor_msgs REQUIRED)
find_package(moveit_task_constructor_visualization REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(motoros2_interfaces REQUIRED)
find_package(std_srvs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(worm_picker_moveit_config REQUIRED)

# Export dependencies for downstream packages
ament_export_dependencies(rosidl_default_runtime)

# ---------------------------
# Include Directories
# ---------------------------
include_directories(include)

# ---------------------------
# Executable Setup Function
# ---------------------------
function(add_worm_picker_executable target_name)
  cmake_parse_arguments(EXE "" "" "SOURCES;ARGS" ${ARGN})
  
  add_executable(${target_name} ${EXE_SOURCES})
  
  target_include_directories(${target_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  
  target_compile_features(${target_name} PUBLIC c_std_99 cxx_std_20)
  
  if(EXE_ARGS)
    ament_target_dependencies(${target_name} ${EXE_ARGS})
  else()
    message(WARNING "No dependencies provided for target ${target_name}")
  endif()
  
  install(TARGETS ${target_name}
    DESTINATION lib/${PROJECT_NAME}
  )
endfunction()

# ---------------------------
# Define Executables
# ---------------------------

## Worm Picker Robot
add_worm_picker_executable(worm_picker_robot
  SOURCES
    src/worm_picker_main.cpp 
    src/tasks/worm_picker_task_controller.cpp
    src/tasks/task_data_structure.cpp
    src/tasks/task_factory.cpp
  ARGS
    rclcpp
    moveit_core
    moveit_task_constructor_core
    moveit_ros_planning_interface
    moveit_task_constructor_msgs
    moveit_task_constructor_visualization
    geometry_msgs
    worm_picker_custom_msgs
    tf2
    tf2_geometry_msgs
)

## Service Client
add_worm_picker_executable(task_command_client
  SOURCES
    src/tools/command_client.cpp
  ARGS
    rclcpp
    worm_picker_custom_msgs
)

## Command Networking
add_worm_picker_executable(command_networking
  SOURCES
    src/networking/ros_command_client.cpp
    src/networking/tcp_socket_server.cpp
  ARGS
    rclcpp
    worm_picker_custom_msgs
    std_srvs
    motoros2_interfaces
)

## Plate Calibration
add_worm_picker_executable(plate_calibration
  SOURCES
    src/calibration/plate_calibration.cpp
  ARGS
    rclcpp
    moveit_core
    moveit_task_constructor_core
    moveit_ros_planning_interface
    moveit_task_constructor_msgs
    moveit_task_constructor_visualization
    geometry_msgs
    worm_picker_custom_msgs
    tf2
    tf2_geometry_msgs
)

# ---------------------------
# Install Launch Files
# ---------------------------
install(
  DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/
)

# ---------------------------
# Package Export
# ---------------------------
ament_package()
