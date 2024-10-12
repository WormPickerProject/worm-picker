# ---------------------------
# worm_picker_custom_msgs CMake
# ---------------------------
cmake_minimum_required(VERSION 3.10)
project(worm_picker_custom_msgs)

# ---------------------------
# C++ Standard and Compiler Options
# ---------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

function(set_compiler_options)
  if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
  endif()
endfunction()

set_compiler_options()

# ---------------------------
# Find Dependencies
# ---------------------------
find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# ---------------------------
# Define Service Files
# ---------------------------
set(srv_files
  "srv/TaskCommand.srv"
)

# ---------------------------
# Generate ROSIDL Interfaces
# ---------------------------
rosidl_generate_interfaces(${PROJECT_NAME}
  ${srv_files}
)

# ---------------------------
# Package Export
# ---------------------------
ament_export_dependencies(rosidl_default_runtime)
ament_package()
