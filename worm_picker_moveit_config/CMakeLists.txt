# ---------------------------
# worm_picker_moveit_config CMake
# ---------------------------
cmake_minimum_required(VERSION 3.10)
project(worm_picker_moveit_config)

# ---------------------------
# C++ Standard and Build Type
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
find_package(xacro REQUIRED)

# ---------------------------
# Install Directories
# ---------------------------
install(DIRECTORY config rviz
  DESTINATION share/${PROJECT_NAME}
)

# ---------------------------
# Install Specific Files
# ---------------------------
install(FILES .setup_assistant
  DESTINATION share/${PROJECT_NAME}
)

# ---------------------------
# Package Export
# ---------------------------
ament_package()
