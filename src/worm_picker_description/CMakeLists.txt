cmake_minimum_required(VERSION 3.8)
project(worm_picker_description)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(xacro REQUIRED)

# Install directories
install(DIRECTORY config meshes urdf
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
