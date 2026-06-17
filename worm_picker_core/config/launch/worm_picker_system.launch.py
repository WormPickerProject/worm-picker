# worm_picker_system.launch.py
#
# Copyright (c) 2025
# SPDX-License-Identifier: Apache-2.0

from pathlib import Path
import time
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction, ExecuteProcess
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from moveit_configs_utils import MoveItConfigsBuilder


class WormPickerLauncher:
    """Encapsulates all logic needed to build the WormPicker launch description"""

    def __init__(self):
        self.use_sim_sub:  LaunchConfiguration | None = None
        self.use_rviz_sub: LaunchConfiguration | None = None

        self.use_sim_bool:  bool | None = None
        self.use_rviz_bool: bool | None = None
        self.use_massif:    bool | None = None
        self.interface:     str  | None = None
        self.terminal:      str  | None = None
        self.serial_device: str  | None = None
        self.serial_baud:   str  | None = None

        self.cfg:        dict[str, Path] = {}
        self.moveit_cfg  = None
        self.massif_prefix: str = ""

    @staticmethod
    def declare_arguments():
        """Return a list of DeclareLaunchArgument actions"""
        return [
            DeclareLaunchArgument("use_sim",    default_value="true",
                                  description="Start in simulation mode (fake hardware)"),
            DeclareLaunchArgument("use_rviz",   default_value="true",
                                  description="Automatically start RViz2"),
            DeclareLaunchArgument("use_massif", default_value="false",
                                  description="Run worm_picker_robot under Valgrind Massif"),
            DeclareLaunchArgument("interface",  default_value="none",
                                  description="Command interface: none | cli | network | both"),
            DeclareLaunchArgument("terminal",   default_value="gnome-terminal",
                                  description="Terminal emulator used to spawn interfaces"),
            DeclareLaunchArgument("serial_device", default_value="/dev/ttyUSB0",
                                  description="Serial device used by the command bridge"),
            DeclareLaunchArgument("serial_baud",   default_value="115200",
                                  description="Baud rate of the serial command bridge"),
        ]

    def _resolve_arguments(self, context):
        """Resolve substitutions that must be Python values"""
        self.use_sim_sub  = LaunchConfiguration("use_sim")
        self.use_rviz_sub = LaunchConfiguration("use_rviz")

        self.use_sim_bool  = LaunchConfiguration("use_sim").perform(context).lower() == "true"
        self.use_rviz_bool = LaunchConfiguration("use_rviz").perform(context).lower() == "true"
        self.use_massif    = LaunchConfiguration("use_massif").perform(context).lower() == "true"
        self.interface     = LaunchConfiguration("interface").perform(context).lower()
        self.terminal      = LaunchConfiguration("terminal").perform(context)
        self.serial_device = LaunchConfiguration("serial_device").perform(context)
        self.serial_baud   = LaunchConfiguration("serial_baud").perform(context)

    def _setup_config_paths(self):
        """Locate package resources and validate"""
        pkg_moveit = Path(get_package_share_directory("worm_picker_moveit_config"))
        pkg_desc   = Path(get_package_share_directory("worm_picker_description"))

        self.cfg = {
            "robot_urdf":              pkg_desc   / "urdf"   / "worm_picker_robot.urdf.xacro",
            "robot_srdf":              pkg_moveit / "config" / "worm_picker_robot.srdf",
            "kinematics_yaml":         pkg_moveit / "config" / "kinematics.yaml",
            "moveit_controllers_sim":  pkg_moveit / "config" / "moveit_controllers_sim.yaml",
            "moveit_controllers_real": pkg_moveit / "config" / "moveit_controllers_real.yaml",
            "ros2_controllers_sim":    pkg_moveit / "config" / "ros2_controllers_sim.yaml",
            "rviz_config":             pkg_moveit / "rviz"   / "wormpicker_config.rviz",
        }
        for name, path in self.cfg.items():
            if not path.exists():
                raise FileNotFoundError(f"Required file '{name}' not found at {path}")

    def _configure_moveit(self):
        """Create self.moveit_cfg (MoveItConfigs)"""
        controllers_file = (
            self.cfg["moveit_controllers_sim"] if self.use_sim_bool
            else self.cfg["moveit_controllers_real"]
        )
        
        self.moveit_cfg = (
            MoveItConfigsBuilder(
                "worm_picker_robot", package_name="worm_picker_moveit_config"
            )
            .robot_description(
                file_path=self.cfg["robot_urdf"].as_posix(),
                mappings={"use_sim": "true" if self.use_sim_bool else "false"},
            )
            .robot_description_semantic(
                file_path=self.cfg["robot_srdf"].as_posix()
            )
            .robot_description_kinematics(
                file_path=self.cfg["kinematics_yaml"].as_posix()
            )
            .trajectory_execution(
                file_path=controllers_file.as_posix()
            )
            .planning_pipelines(
                pipelines=["ompl", "pilz_industrial_motion_planner"]
            )
            .to_moveit_configs()
        )

    def _setup_massif(self):
        if not self.use_massif:
            return
        ts = time.strftime("%Y%m%d_%H%M%S")
        out_file = Path(f"/tmp/massif_worm_picker_robot_{ts}.out")
        self.massif_prefix = " ".join([
            "valgrind",
            "--tool=massif",
            "--stacks=yes",
            "--run-libc-freeres=no",
            f"--massif-out-file={out_file}",
        ]) + " "

    def _create_core_nodes(self):
        """ROS 2 nodes that are always launched"""
        psm_params = {
            "publish_planning_scene":     True,
            "publish_geometry_updates":   True,
            "publish_state_updates":      True,
            "publish_transforms_updates": True,
        }
        move_group_caps = {
            "capabilities": "move_group/ExecuteTaskSolutionCapability",
        }

        nodes: list = [
            Node(
                package="moveit_ros_move_group", executable="move_group",
                name="move_group", output="screen",
                parameters=[
                    self.moveit_cfg.to_dict(),
                    psm_params,
                    move_group_caps,
                ],
            ),
            Node(
                condition=IfCondition(self.use_rviz_sub),
                package="rviz2", executable="rviz2",
                output="screen",
                arguments=[
                    "-d", self.cfg["rviz_config"].as_posix(),
                    "--ros-args", "--log-level", "error"
                ],
                parameters=[
                    self.moveit_cfg.robot_description,
                    self.moveit_cfg.robot_description_semantic,
                    self.moveit_cfg.planning_pipelines,
                    self.moveit_cfg.robot_description_kinematics,
                    self.moveit_cfg.joint_limits,
                ],
            ),
            Node(
                package="tf2_ros", executable="static_transform_publisher",
                name="static_transform_publisher", output="log",
                arguments=["0", "0", "0", "0", "0", "0", "world", "base_link"],
            ),
            Node(
                package="robot_state_publisher", executable="robot_state_publisher",
                name="robot_state_publisher", output="both",
                parameters=[self.moveit_cfg.robot_description],
            ),
            Node(
                condition=IfCondition(self.use_sim_sub),
                package="controller_manager", executable="ros2_control_node",
                parameters=[
                    self.moveit_cfg.robot_description,
                    self.cfg["ros2_controllers_sim"].as_posix(),
                ],
            ),
            Node(
                condition=IfCondition(self.use_sim_sub),
                package="controller_manager", executable="spawner",
                arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
                output="screen",
            ),
            Node(
                condition=IfCondition(self.use_sim_sub),
                package="controller_manager", executable="spawner",
                arguments=["follow_joint_trajectory", "--controller-manager", "/controller_manager"],
                output="screen",
            ),
            Node(
                package="worm_picker_core", executable="worm_picker_robot",
                name="worm_picker_robot", output="screen",
                prefix=self.massif_prefix,
                parameters=[self.moveit_cfg.to_dict()],
            ),
        ]

        return nodes

    def _create_interface_nodes(self):
        """Spawn CLI / serial helpers in their own GNOME-terminal tabs/windows."""
        def spawn(title: str, exe: str, enabled: bool, args: str = "") -> ExecuteProcess:
            invocation = f"ros2 run worm_picker_core {exe} {args}".rstrip()
            return ExecuteProcess(
                condition=IfCondition("true" if enabled else "false"),
                cmd=[
                    self.terminal, "--wait", "--title", title, "--", "bash", "-c",
                    (
                        "source /opt/ros/humble/setup.bash && "
                        "source ~/ws_moveit2/install/setup.bash && "
                        "source ~/worm-picker/install/setup.bash && "
                        f"{invocation}"
                    ),
                ],
                shell=False,
                output="screen",
                sigterm_timeout="1.0",
                sigkill_timeout="2.0",
            )

        return [
            spawn("WormPicker CLI", "core_command_interface",
                  self.interface in {"cli", "both"}),
            spawn("WormPicker Serial", "command_networking",
                  self.interface in {"network", "both"},
                  f"{self.serial_device} {self.serial_baud}"),
        ]

    def launch_setup(self, context, *_, **__):
        """Called by OpaqueFunction — returns list/tuple of Actions."""
        self._resolve_arguments(context)
        self._setup_config_paths()
        self._configure_moveit()
        self._setup_massif()

        nodes = self._create_core_nodes()
        nodes.extend(self._create_interface_nodes())
        return nodes


def generate_launch_description() -> LaunchDescription:
    """Entrypoint required by the ROS 2 launch system."""
    launcher = WormPickerLauncher()

    def _setup(context, *args, **kwargs):
        return launcher.launch_setup(context, *args, **kwargs)

    return LaunchDescription(
        launcher.declare_arguments() + [OpaqueFunction(function=_setup)]
    )