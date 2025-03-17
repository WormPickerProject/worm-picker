cmake_minimum_required(VERSION 3.8)
project(worm_picker_core VERSION 0.1.0)

include(GNUInstallDirs)

option(BUILD_TESTING "Build tests" ON)

#
# ----------------------------------------------------------------------------
# C++ Standard & Build Type
# ----------------------------------------------------------------------------
#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

#
# ----------------------------------------------------------------------------
# Compiler Options Function
# ----------------------------------------------------------------------------
#
function(set_compiler_options target)
  if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${target} PRIVATE
      -Wall
      -Wextra
      -Wpedantic
      $<$<CONFIG:Debug>:-g>
      $<$<CONFIG:Release>:-O3>
    )
  endif()
endfunction()

#
# ----------------------------------------------------------------------------
# Find Dependencies
# ----------------------------------------------------------------------------
#
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(worm_picker_custom_msgs REQUIRED)
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
find_package(fmt REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(motoros2_interfaces REQUIRED)
find_package(std_srvs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(worm_picker_moveit_config REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(isaac_ros_cumotion_moveit REQUIRED)

#
# ----------------------------------------------------------------------------
# Group Common Dependencies
# ----------------------------------------------------------------------------
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
  ament_index_cpp
)

set(WORM_PICKER_DEPS
  ${MOVEIT_DEPS}
  ${ROS_DEPS}
  worm_picker_custom_msgs
  motoros2_interfaces
  fmt
  yaml-cpp
  nlohmann_json
  isaac_ros_cumotion_moveit
)

#
# ----------------------------------------------------------------------------
# Main Library
# ----------------------------------------------------------------------------
#
add_library(${PROJECT_NAME} SHARED
  src/core/commands/parser/basic_parsers.cpp
  src/core/commands/parser/command_info_builder.cpp
  src/core/commands/parser/command_parsers.cpp
  src/core/commands/parser/command_registry.cpp
  src/core/commands/parser/new_command_parser.cpp
  src/core/commands/command_config.cpp
  src/core/commands/command_info.cpp
  src/core/tasks/stages/move_relative_data.cpp
  src/core/tasks/stages/move_to_circle_data.cpp
  src/core/tasks/stages/move_to_joint_data.cpp
  src/core/tasks/stages/move_to_point_data.cpp
  src/core/tasks/stages/movement_data_base.cpp
  src/core/tasks/planner_factory.cpp
  src/core/tasks/task_data.cpp
  src/infrastructure/interface/cli/cal_command_interface.cpp
  src/infrastructure/interface/cli/core_command_interface.cpp
  src/infrastructure/interface/network/ros_command_client.cpp
  src/infrastructure/interface/network/tcp_socket_server.cpp
  src/infrastructure/parsers/calibration_points_parser.cpp
  src/infrastructure/parsers/command_parser.cpp
  src/infrastructure/parsers/defined_tasks_parser.cpp
  src/infrastructure/parsers/hotel_data_parser.cpp
  src/infrastructure/parsers/workstation_data_parser.cpp
  src/infrastructure/parsers/workstation_geometry_parser.cpp
  src/system/calibration/calibration_state_machine.cpp
  src/system/calibration/plate_position_analyzer.cpp
  src/system/calibration/robot_controller.cpp
  src/system/calibration/workstation_json_generator.cpp
  src/system/management/action_client_manager.cpp
  src/system/management/parameter_manager.cpp
  src/system/management/service_handler.cpp
  src/system/management/task_manager.cpp
  src/system/nodes/plate_calibration.cpp
  src/system/nodes/worm_picker_controller.cpp
  src/system/tasks/generation/generate_absolute_movement_task.cpp
  src/system/tasks/generation/generate_hotel_task_generator.cpp
  src/system/tasks/generation/generate_relative_movement_task.cpp
  src/system/tasks/generation/generate_transfer_task_generator.cpp
  src/system/tasks/generation/generate_workstation_task_generator.cpp
  src/system/tasks/task_factory.cpp
  src/system/tasks/task_generator.cpp
  src/system/tasks/task_validator.cpp
  src/utils/circular_constraint_calculator.cpp
  src/utils/circular_motion_utils.cpp
  src/utils/execution_timer.cpp
  src/utils/scoped_timer.cpp
  src/utils/timer_data_collector.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
set_compiler_options(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

ament_target_dependencies(
  ${PROJECT_NAME}
  ${WORM_PICKER_DEPS}
)

# Optionally link the cuMotion libraries if you have C++ code calling them:
# target_link_libraries(${PROJECT_NAME}
#   isaac_ros_cumotion_moveit::isaac_ros_cumotion_moveit
# )

#
# ----------------------------------------------------------------------------
# add_worm_picker_executable Function
# ----------------------------------------------------------------------------
#
function(add_worm_picker_executable target_name)
  cmake_parse_arguments(EXE "" "" "SOURCES;DEPS" ${ARGN})
  add_executable(${target_name} ${EXE_SOURCES})
  target_compile_features(${target_name} PUBLIC cxx_std_20)
  set_compiler_options(${target_name})
  target_link_libraries(${target_name} ${PROJECT_NAME})
  if(EXE_DEPS)
    ament_target_dependencies(${target_name} ${EXE_DEPS})
  endif()
  install(TARGETS ${target_name}
    RUNTIME DESTINATION lib/${PROJECT_NAME}
  )
endfunction()

#
# ----------------------------------------------------------------------------
# Executables
# ----------------------------------------------------------------------------
#
add_worm_picker_executable(worm_picker_robot
  SOURCES
    src/apps/worm_picker_main.cpp
  DEPS
    ${WORM_PICKER_DEPS}
)

add_worm_picker_executable(core_command_interface
  SOURCES
    src/apps/core_command_interface_main.cpp
  DEPS
    ${WORM_PICKER_DEPS}
)

add_worm_picker_executable(cal_command_interface
  SOURCES
    src/apps/cal_command_interface_main.cpp
  DEPS
    ${WORM_PICKER_DEPS}
)

add_worm_picker_executable(plate_calibration
  SOURCES
    src/apps/plate_calibration_main.cpp
  DEPS
    ${WORM_PICKER_DEPS}
)

add_worm_picker_executable(command_networking
  SOURCES
    src/apps/command_networking_main.cpp
  DEPS
    ${WORM_PICKER_DEPS}
)

add_worm_picker_executable(plate_calibration_test
  SOURCES
    src/system/calibration/plate_position_analyzer_test.cpp
  DEPS
    ${WORM_PICKER_DEPS}
)

#
# ----------------------------------------------------------------------------
# Install & Export
# ----------------------------------------------------------------------------
#
install(
  TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  DIRECTORY config/parameters/
  DESTINATION share/${PROJECT_NAME}/config/parameters
)

install(
  DIRECTORY config/launch/
  DESTINATION share/${PROJECT_NAME}/launch
)

# install(
#   DIRECTORY launch/
#   DESTINATION share/${PROJECT_NAME}/
# )

#
# ----------------------------------------------------------------------------
# Testing
# ----------------------------------------------------------------------------
#
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  find_package(ament_cmake_gtest REQUIRED)
  ament_lint_auto_find_test_dependencies()

  # ament_add_gtest(my_test test/my_test.cpp)
  # if(TARGET my_test)
  #   target_link_libraries(my_test PRIVATE ${PROJECT_NAME})
  #   ament_target_dependencies(my_test ${WORM_PICKER_DEPS})
  # endif()
endif()

#
# ----------------------------------------------------------------------------
# Final Package Export
# ----------------------------------------------------------------------------
#
ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(${WORM_PICKER_DEPS})
ament_package()