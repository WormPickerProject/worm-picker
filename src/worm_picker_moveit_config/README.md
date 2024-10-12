# worm_picker_moveit_config

## Overview

The `worm_picker_moveit_config` package provides MoveIt 2 configuration files for the Worm Picker Robot. This includes the necessary configurations for motion planning, controllers, and robot descriptions to enable the robot to plan and execute movements within its workcell environment.

## Features

- **MoveIt 2 Integration:** Configurations for MoveIt 2, including planning pipelines and controllers.
- **Robot Description:** URDF/Xacro files defining the robot and its environment.
- **ROS 2 Control Integration:** Setup for ROS 2 control, enabling simulation and hardware interfaces.
- **RViz Configurations:** Predefined RViz settings for visualization and planning.

## Package Contents

- **`config/`:** Configuration files for MoveIt 2 and ROS 2 control.
  - `initial_positions.yaml`: Initial joint positions.
  - `joint_limits.yaml`: Joint limits for planning.
  - `kinematics.yaml`: Kinematics solver configurations.
  - `moveit_controllers.yaml`: MoveIt controller configurations.
  - `pilz_cartesian_limits.yaml`: Limits for the Pilz planner.
  - `ros2_controllers.yaml`: ROS 2 control configurations.
  - `worm_picker_moveit.ros2_control.xacro`: ROS 2 control Xacro macro.
  - `worm_picker.srdf`: Semantic Robot Description Format file.
- **`launch/`:** Launch files for starting the MoveIt setup assistant and other nodes.
- **`rviz/`:** RViz configuration files.
- **`urdf/`:** Xacro files for generating the robot URDF.
- **`CMakeLists.txt`:** Build configuration for the package.
- **`package.xml`:** Package metadata and dependencies.
- **`README.md`:** Documentation for the package.

## Dependencies

- **ROS 2 Packages:**
  - `moveit_ros_move_group`
  - `moveit_ros_planning_interface`
  - `moveit_planners_ompl`
  - `moveit_simple_controller_manager`
  - `controller_manager`
  - `robot_state_publisher`
  - `joint_state_publisher`
  - `rviz2`
  - `xacro`
  - `tf2_ros`
- **Other Packages:**
  - `worm_picker_description`: Contains the robot and workcell description.

Ensure all dependencies are installed and properly sourced before building or using this package.

## Installation

### Prerequisites

- **ROS 2:** Ensure you have a compatible ROS 2 distribution installed (e.g., Foxy, Galactic, Humble).
- **MoveIt 2:** Install MoveIt 2 for your ROS 2 distribution.

## Configuration

### Robot Description

The robot description is generated from Xacro files located in `worm_picker_description` and `worm_picker_moveit_config/urdf/`.  
The main URDF file is `worm_picker_moveit.urdf.xacro`.

### MoveIt Configuration

- **Planning Groups:** Defined in `worm_picker.srdf`.
- **Joint Limits:** Specified in `joint_limits.yaml`.
- **Kinematics:** Configured in `kinematics.yaml`.
- **Initial Positions:** Set in `initial_positions.yaml`.

### Controllers

- **MoveIt Controllers:** Configured in `moveit_controllers.yaml`.
- **ROS 2 Controllers:** Defined in `ros2_controllers.yaml`.

## Contribution

Contributions are welcome! Please follow the guidelines in the main repository's `CONTRIBUTING.md` file.

## License

This project is licensed under the **Apache-2.0** License. See the `LICENSE` file for details.

## Maintainers

- Logan Kaising - lkaising@outlook.com

