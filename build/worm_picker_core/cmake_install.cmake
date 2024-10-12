# Install script for directory: /home/logan/worm-picker/src/worm_picker_core

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/logan/worm-picker/install/worm_picker_core")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/worm_picker_robot" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/worm_picker_robot")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/worm_picker_robot"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core" TYPE EXECUTABLE FILES "/home/logan/worm-picker/build/worm_picker_core/worm_picker_robot")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/worm_picker_robot" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/worm_picker_robot")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/worm_picker_robot"
         OLD_RPATH "/home/logan/ws_moveit2/install/moveit_task_constructor_core/lib:/home/logan/worm-picker/install/worm_picker_custom_msgs/lib:/home/logan/ws_moveit2/install/moveit_task_constructor_visualization/lib:/home/logan/ws_moveit2/install/moveit_core/lib:/opt/ros/humble/lib/x86_64-linux-gnu:/home/logan/ws_moveit2/install/moveit_ros_visualization/lib:/home/logan/ws_moveit2/install/moveit_ros_robot_interaction/lib:/home/logan/ws_moveit2/install/moveit_ros_planning_interface/lib:/home/logan/ws_moveit2/install/moveit_ros_warehouse/lib:/home/logan/ws_moveit2/install/moveit_ros_move_group/lib:/home/logan/ws_moveit2/install/moveit_ros_planning/lib:/home/logan/ws_moveit2/install/moveit_ros_occupancy_map_monitor/lib:/home/logan/ws_moveit2/install/moveit_msgs/lib:/opt/ros/humble/lib:/home/logan/ws_moveit2/install/moveit_task_constructor_msgs/lib:/opt/ros/humble/opt/rviz_ogre_vendor/lib:/home/logan/ws_moveit2/install/rviz_marker_tools/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/worm_picker_robot")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/task_command_client" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/task_command_client")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/task_command_client"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core" TYPE EXECUTABLE FILES "/home/logan/worm-picker/build/worm_picker_core/task_command_client")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/task_command_client" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/task_command_client")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/task_command_client"
         OLD_RPATH "/opt/ros/humble/lib:/home/logan/worm-picker/install/worm_picker_custom_msgs/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/task_command_client")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/command_networking" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/command_networking")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/command_networking"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core" TYPE EXECUTABLE FILES "/home/logan/worm-picker/build/worm_picker_core/command_networking")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/command_networking" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/command_networking")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/command_networking"
         OLD_RPATH "/opt/ros/humble/lib:/home/logan/worm-picker/install/worm_picker_custom_msgs/lib:/home/logan/worm-picker/install/motoros2_interfaces/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/command_networking")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/plate_calibration" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/plate_calibration")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/plate_calibration"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core" TYPE EXECUTABLE FILES "/home/logan/worm-picker/build/worm_picker_core/plate_calibration")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/plate_calibration" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/plate_calibration")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/plate_calibration"
         OLD_RPATH "/home/logan/ws_moveit2/install/moveit_task_constructor_core/lib:/home/logan/worm-picker/install/worm_picker_custom_msgs/lib:/home/logan/ws_moveit2/install/moveit_task_constructor_visualization/lib:/home/logan/ws_moveit2/install/moveit_core/lib:/opt/ros/humble/lib/x86_64-linux-gnu:/home/logan/ws_moveit2/install/moveit_ros_visualization/lib:/home/logan/ws_moveit2/install/moveit_ros_robot_interaction/lib:/home/logan/ws_moveit2/install/moveit_ros_planning_interface/lib:/home/logan/ws_moveit2/install/moveit_ros_warehouse/lib:/home/logan/ws_moveit2/install/moveit_ros_move_group/lib:/home/logan/ws_moveit2/install/moveit_ros_planning/lib:/home/logan/ws_moveit2/install/moveit_ros_occupancy_map_monitor/lib:/home/logan/ws_moveit2/install/moveit_msgs/lib:/opt/ros/humble/lib:/home/logan/ws_moveit2/install/moveit_task_constructor_msgs/lib:/opt/ros/humble/opt/rviz_ogre_vendor/lib:/home/logan/ws_moveit2/install/rviz_marker_tools/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/worm_picker_core/plate_calibration")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/worm_picker_core/" TYPE DIRECTORY FILES "/home/logan/worm-picker/src/worm_picker_core/launch/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/home/logan/worm-picker/build/worm_picker_core/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/worm_picker_core")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/home/logan/worm-picker/build/worm_picker_core/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/worm_picker_core")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/worm_picker_core/environment" TYPE FILE FILES "/opt/ros/humble/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/worm_picker_core/environment" TYPE FILE FILES "/home/logan/worm-picker/build/worm_picker_core/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/worm_picker_core/environment" TYPE FILE FILES "/opt/ros/humble/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/worm_picker_core/environment" TYPE FILE FILES "/home/logan/worm-picker/build/worm_picker_core/ament_cmake_environment_hooks/path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/worm_picker_core" TYPE FILE FILES "/home/logan/worm-picker/build/worm_picker_core/ament_cmake_environment_hooks/local_setup.bash")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/worm_picker_core" TYPE FILE FILES "/home/logan/worm-picker/build/worm_picker_core/ament_cmake_environment_hooks/local_setup.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/worm_picker_core" TYPE FILE FILES "/home/logan/worm-picker/build/worm_picker_core/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/worm_picker_core" TYPE FILE FILES "/home/logan/worm-picker/build/worm_picker_core/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/worm_picker_core" TYPE FILE FILES "/home/logan/worm-picker/build/worm_picker_core/ament_cmake_environment_hooks/package.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/home/logan/worm-picker/build/worm_picker_core/ament_cmake_index/share/ament_index/resource_index/packages/worm_picker_core")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/worm_picker_core/cmake" TYPE FILE FILES "/home/logan/worm-picker/build/worm_picker_core/ament_cmake_export_dependencies/ament_cmake_export_dependencies-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/worm_picker_core/cmake" TYPE FILE FILES
    "/home/logan/worm-picker/build/worm_picker_core/ament_cmake_core/worm_picker_coreConfig.cmake"
    "/home/logan/worm-picker/build/worm_picker_core/ament_cmake_core/worm_picker_coreConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/worm_picker_core" TYPE FILE FILES "/home/logan/worm-picker/src/worm_picker_core/package.xml")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/logan/worm-picker/build/worm_picker_core/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
