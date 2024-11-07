import os

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from moveit_configs_utils import MoveItConfigsBuilder


def generate_launch_description() -> LaunchDescription:
    """Generate launch description for worm picker robot with MoveIt Task Constructor integration."""

    declared_arguments = [
        DeclareLaunchArgument(
            "use_sim",
            default_value="true",
            description="Start in simulation mode using fake hardware",
        ),
        DeclareLaunchArgument(
            "use_rviz",
            default_value="true",
            description="Start RViz2 automatically with this launch file",
        ),
    ]

    return LaunchDescription(declared_arguments + [OpaqueFunction(function=launch_setup)])


def launch_setup(context, *args, **kwargs):
    """Set up the launch description with proper context handling."""

    use_sim = LaunchConfiguration("use_sim")
    use_rviz = LaunchConfiguration("use_rviz")

    use_sim_value = use_sim.perform(context).lower() == "true"

    pkg_worm_picker_moveit = get_package_share_directory("worm_picker_moveit_config")
    pkg_worm_picker_description = get_package_share_directory("worm_picker_description")

    config_files = {
        "robot_urdf": os.path.join(
            pkg_worm_picker_description, "urdf", "worm_picker_robot.urdf.xacro"
        ),
        "robot_srdf": os.path.join(
            pkg_worm_picker_moveit, "config", "worm_picker_robot.srdf"
        ),
        "kinematics_yaml": os.path.join(
            pkg_worm_picker_moveit, "config", "kinematics.yaml"
        ),
        "moveit_controllers_sim": os.path.join(
            pkg_worm_picker_moveit, "config", "moveit_controllers_sim.yaml"
        ),
        "moveit_controllers_real": os.path.join(
            pkg_worm_picker_moveit, "config", "moveit_controllers_real.yaml"
        ),
        "ros2_controllers_sim": os.path.join(
            pkg_worm_picker_moveit, "config", "ros2_controllers_sim.yaml"
        ),
        "rviz_config": os.path.join(
            pkg_worm_picker_moveit, "rviz", "moveit_task_desktop.rviz"
        ),
    }

    for name, path in config_files.items():
        if not os.path.exists(path):
            raise FileNotFoundError(f"Required file '{name}' not found at: {path}")

    if use_sim_value:
        moveit_controllers_path = config_files["moveit_controllers_sim"]
    else:
        moveit_controllers_path = config_files["moveit_controllers_real"]

    moveit_config = (
        MoveItConfigsBuilder("worm_picker_robot", package_name="worm_picker_moveit_config")
        .robot_description(
            file_path=config_files["robot_urdf"],
            mappings={"use_sim": "true" if use_sim_value else "false"},
        )
        .robot_description_semantic(file_path=config_files["robot_srdf"])
        .robot_description_kinematics(file_path=config_files["kinematics_yaml"])
        .trajectory_execution(file_path=moveit_controllers_path)
        .planning_pipelines(pipelines=["ompl", "pilz_industrial_motion_planner"])
        .to_moveit_configs()
    )

    planning_scene_monitor_parameters = {
        "publish_planning_scene": True,
        "publish_geometry_updates": True,
        "publish_state_updates": True,
        "publish_transforms_updates": True,
    }

    move_group_capabilities = {
        "capabilities": "move_group/ExecuteTaskSolutionCapability"
    }

    nodes = [
        # Move Group Node
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
        # RViz
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
            ],
        ),
        # Static TF Publisher
        Node(
            package="tf2_ros",
            executable="static_transform_publisher",
            name="static_transform_publisher",
            output="log",
            arguments=["0", "0", "0", "0", "0", "0", "world", "base_link"],
        ),
        # Robot State Publisher
        Node(
            package="robot_state_publisher",
            executable="robot_state_publisher",
            name="robot_state_publisher",
            output="both",
            parameters=[
                moveit_config.robot_description,
            ],
        ),
        # ROS 2 Control Node (Simulation Only)
        Node(
            condition=IfCondition(use_sim),
            package="controller_manager",
            executable="ros2_control_node",
            parameters=[
                moveit_config.robot_description,
                config_files["ros2_controllers_sim"],
            ],
            output="both",
        ),
        # Controller Spawner for Joint State Broadcaster (Simulation Only)
        Node(
            condition=IfCondition(use_sim),
            package="controller_manager",
            executable="spawner",
            arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
            output="screen",
        ),
        # Controller Spawner for Joint Trajectory Controller (Simulation Only)
        Node(
            condition=IfCondition(use_sim),
            package="controller_manager",
            executable="spawner",
            arguments=["joint_trajectory_controller", "--controller-manager", "/controller_manager"],
            output="screen",
        ),
        # Worm Picker Robot Node
        Node(
            package="worm_picker_core",
            executable="worm_picker_robot",
            output="screen",
            parameters=[
                moveit_config.to_dict(),
            ],
        ),
    ]

    return nodes