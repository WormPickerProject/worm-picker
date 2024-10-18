# ---------------------------
# worm_picker_description CMake
# ---------------------------
cmake_minimum_required(VERSION 3.10)
project(worm_picker_description)

# ---------------------------
# C++ Standard and Compiler Options
# ---------------------------
set(CMAKE_CXX_STANDARD 17)
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
install(DIRECTORY config meshes urdf
  DESTINATION share/${PROJECT_NAME}
)

# ---------------------------
# Package Export
# ---------------------------
ament_package()

