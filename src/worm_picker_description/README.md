# worm_picker_description

## Overview

The `worm_picker_description` package contains the robot and workcell description files for the Worm Picker Robot system configured with a Motoman GP4 robot arm. It provides Unified Robot Description Format (URDF) and Xacro files, as well as meshes required for simulation and visualization in ROS 2 environments.

This package is essential for anyone working with the Worm Picker Robot, as it defines the physical properties, kinematics, and visual representations of both the robot and its workspace.

## Features

- **Robot Model:** Detailed URDF/Xacro files for the Motoman GP4 robot arm.
- **Workcell Description:** Includes the workcell environment with all necessary components.
- **Meshes:** High-quality visual and collision meshes for accurate simulation and visualization.
- **Modularity:** Uses Xacro macros for easy modification and reuse.
- **Compatibility:** Designed for ROS 2 and MoveIt 2.

## Package Contents

- **`urdf/`:** Contains Xacro and URDF files defining the robot and workcell.
  - `common_colors.xacro`: Defines common colors used in materials.
  - `common_materials.xacro`: Defines material macros for the robot.
  - `gp4_macro.xacro`: Macro defining the Motoman GP4 robot.
  - `workcell_macro.xacro`: Macro defining the entire workcell environment.
  - `worm_picker_robot.urdf.xacro`: Main URDF file including the robot and workcell macros.
- **`meshes/`:** Contains 3D models used for visualization and collision.
  - **`robot/`:** Meshes for the robot arm.
    - `collision/`: Simplified meshes for collision checking.
    - `visual/`: Detailed meshes for visualization.
  - **`workcell/`:** Meshes for workcell components like the end-effector and workstation.
- **`config/`:** Configuration files for joint names, OPW parameters, and RViz visualization.
- **`CMakeLists.txt`:** Build configuration for the package.
- **`package.xml`:** Package metadata and dependencies.
- **`README.md`:** Documentation for the package.

## Dependencies

- **ROS 2 Packages:**
  - `xacro`: Required for processing Xacro files.
- **Other Packages:**
  - None explicitly, but intended to be used with MoveIt 2 and other ROS 2 packages.

Ensure all dependencies are installed and properly sourced before building or using this package.

## Usage

### Including the Robot Description in Your Project

To use the robot and workcell description in your own ROS 2 packages or launch files, include the `worm_picker_robot.urdf.xacro` file.

**Example:**

```xml
<robot name="my_worm_picker_robot" xmlns:xacro="http://ros.org/wiki/xacro">
  <xacro:include filename="$(find worm_picker_description)/urdf/worm_picker_robot.urdf.xacro" />
  <xacro:worm_picker_robot/>
</robot>
```

## Contribution
Contributions are welcome! Please follow the guidelines in the main repository's `CONTRIBUTING.md` file.

## License
This project is licensed under the MIT **Apache-2.0:**. See the `LICENSE` file for details.

## Maintainers
- Logan Kaising - lkaising@outlook.com
