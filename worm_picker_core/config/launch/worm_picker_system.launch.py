import os
import time
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from moveit_configs_utils import MoveItConfigsBuilder


def generate_launch_description() -> LaunchDescription:
    declared_args = [
        DeclareLaunchArgument(
            "use_sim", default_value="true",
            description="Start in simulation mode using fake hardware",
        ),
        DeclareLaunchArgument(
            "use_rviz", default_value="true",
            description="Start RViz2 automatically",
        ),
        DeclareLaunchArgument(
            "use_massif", default_value="false",
            description="Run worm_picker_robot under Valgrind Massif",
        ),
    ]
    return LaunchDescription(declared_args + [OpaqueFunction(function=launch_setup)])


def launch_setup(context, *args, **kwargs):
    use_sim = LaunchConfiguration("use_sim")
    use_rviz = LaunchConfiguration("use_rviz")
    use_massif = LaunchConfiguration("use_massif")

    use_sim_val    = use_sim.perform(context).lower()    == "true"
    use_massif_val = use_massif.perform(context).lower() == "true"

    pkg_moveit = get_package_share_directory("worm_picker_moveit_config")
    pkg_desc   = get_package_share_directory("worm_picker_description")

    config_files = {
        "robot_urdf":             os.path.join(pkg_desc,  "urdf",  "worm_picker_robot.urdf.xacro"),
        "robot_srdf":             os.path.join(pkg_moveit,"config","worm_picker_robot.srdf"),
        "robot_xrdf":             os.path.join(pkg_moveit,"config","worm_picker_robot.xrdf.yaml"),
        "kinematics_yaml":        os.path.join(pkg_moveit,"config","kinematics.yaml"),
        "moveit_controllers_sim": os.path.join(pkg_moveit,"config","moveit_controllers_sim.yaml"),
        "moveit_controllers_real":os.path.join(pkg_moveit,"config","moveit_controllers_real.yaml"),
        "ros2_controllers_sim":   os.path.join(pkg_moveit,"config","ros2_controllers_sim.yaml"),
        "rviz_config":            os.path.join(pkg_moveit,"rviz",  "wormpicker_config.rviz"),
    }

    for name, path in config_files.items():
        if not os.path.exists(path):
            raise FileNotFoundError(f"Required file '{name}' not found at: {path}")

    controllers_file = (
        config_files["moveit_controllers_sim"]
        if use_sim_val
        else config_files["moveit_controllers_real"]
    )

    moveit_config = (
        MoveItConfigsBuilder("worm_picker_robot", package_name="worm_picker_moveit_config")
        .robot_description(
            file_path=config_files["robot_urdf"],
            mappings={"use_sim": "true" if use_sim_val else "false"},
        )
        .robot_description_semantic(file_path=config_files["robot_srdf"])
        .robot_description_kinematics(file_path=config_files["kinematics_yaml"])
        .trajectory_execution(file_path=controllers_file)
        .planning_pipelines(
            pipelines=[
                "ompl",
                "pilz_industrial_motion_planner",
            ]
        )
        .to_moveit_configs()
    )

    planning_scene_monitor_parameters = {
        "publish_planning_scene":     True,
        "publish_geometry_updates":   True,
        "publish_state_updates":      True,
        "publish_transforms_updates": True,
    }
    move_group_capabilities = {
        "capabilities": "move_group/ExecuteTaskSolutionCapability",
    }

    massif_prefix = ""
    if use_massif_val:
        ts       = time.strftime("%Y%m%d_%H%M%S")
        out_file = f"/tmp/massif_worm_picker_robot_{ts}.out"
        massif_prefix_parts = [
            "valgrind",
            "--tool=massif",
            "--stacks=yes",
            "--run-libc-freeres=no",
            f"--massif-out-file={out_file}",
        ]
        massif_prefix = " ".join(massif_prefix_parts) + " "
        print(f"Massif output file: {out_file}")

    nodes = [
        Node(
            package="moveit_ros_move_group",
            executable="move_group",
            name="move_group",
            output="screen",
            parameters=[
                moveit_config.to_dict(),
                planning_scene_monitor_parameters,
                move_group_capabilities,
            ],
        ),
        Node(
            condition=IfCondition(use_rviz),
            package="rviz2",
            executable="rviz2",
            name="rviz2",
            output="log",
            arguments=["-d", config_files["rviz_config"]],
            parameters=[
                moveit_config.robot_description,
                moveit_config.robot_description_semantic,
                moveit_config.planning_pipelines,
                moveit_config.robot_description_kinematics,
                moveit_config.joint_limits,
            ],
        ),
        Node(
            package="tf2_ros",
            executable="static_transform_publisher",
            name="static_transform_publisher",
            output="log",
            arguments=["0", "0", "0", "0", "0", "0", "world", "base_link"],
        ),
        Node(
            package="robot_state_publisher",
            executable="robot_state_publisher",
            name="robot_state_publisher",
            output="both",
            parameters=[moveit_config.robot_description],
        ),
        Node(
            condition=IfCondition(use_sim),
            package="controller_manager",
            executable="ros2_control_node",
            parameters=[
                moveit_config.robot_description,
                config_files["ros2_controllers_sim"],
            ],
        ),
        Node(
            condition=IfCondition(use_sim),
            package="controller_manager",
            executable="spawner",
            arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
            output="screen",
        ),
        Node(
            condition=IfCondition(use_sim),
            package="controller_manager",
            executable="spawner",
            arguments=["follow_joint_trajectory", "--controller-manager", "/controller_manager"],
            output="screen",
        ),
        Node(
            package="worm_picker_core",
            executable="worm_picker_robot",
            name="worm_picker_robot",
            output="screen",
            prefix=massif_prefix,
            parameters=[moveit_config.to_dict()],
        ),
    ]

    return nodes