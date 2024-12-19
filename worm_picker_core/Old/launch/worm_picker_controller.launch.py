import os

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition, UnlessCondition
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from moveit_configs_utils import MoveItConfigsBuilder


def generate_launch_description() -> LaunchDescription:
    """Generate launch description for worm picker robot with MotoROS2 integration."""

    # 1. Declare launch arguments
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

    # 2. Return the launch description with an OpaqueFunction
    return LaunchDescription(declared_arguments + [OpaqueFunction(function=launch_setup)])


def launch_setup(context, *args, **kwargs):
    """Set up the launch description with proper context handling."""
    # 3. Get launch configurations
    use_sim = LaunchConfiguration("use_sim").perform(context)
    use_rviz = LaunchConfiguration("use_rviz").perform(context)

    # 4. Get package paths
    pkg_worm_picker_moveit = get_package_share_directory("worm_picker_moveit_config")
    pkg_worm_picker_description = get_package_share_directory("worm_picker_description")

    # 5. Define configuration file paths
    config_files = {
        "robot_urdf": os.path.join(pkg_worm_picker_description, "urdf", "worm_picker_robot.urdf.xacro"),
        "robot_srdf": os.path.join(pkg_worm_picker_moveit, "config", "worm_picker_robot.srdf"),
        "moveit_controllers_sim": os.path.join(pkg_worm_picker_moveit, "config", "moveit_controllers_sim.yaml"),
        "moveit_controllers_real": os.path.join(pkg_worm_picker_moveit, "config", "moveit_controllers_real.yaml"),
        "ros2_controllers_sim": os.path.join(pkg_worm_picker_moveit, "config", "ros2_controllers_sim.yaml"),
        "rviz_config": os.path.join(pkg_worm_picker_moveit, "rviz", "moveit_task_desktop.rviz"),
    }

    # 6. Verify files exist
    for name, path in config_files.items():
        if not os.path.exists(path):
            raise FileNotFoundError(f"Required file '{name}' not found at: {path}")

    # 7. Select the appropriate MoveIt controllers configuration
    if use_sim.lower() == 'true':
        moveit_controllers_path = config_files["moveit_controllers_sim"]
    else:
        moveit_controllers_path = config_files["moveit_controllers_real"]

    # 8. Create MoveIt configuration
    moveit_config = (
        MoveItConfigsBuilder("worm_picker_robot", package_name="worm_picker_moveit_config")
        .robot_description(file_path=config_files["robot_urdf"])
        .robot_description_semantic(file_path=config_files["robot_srdf"])
        .trajectory_execution(file_path=moveit_controllers_path)
        .planning_pipelines(pipelines=["ompl"])
        .to_moveit_configs()
    )

    # 9. Convert use_sim to a boolean
    use_sim_bool = use_sim.lower() == 'true'
    use_rviz_bool = use_rviz.lower() == 'true'

    move_group_capabilities = {
        "capabilities": "move_group/ExecuteTaskSolutionCapability"
    }

    # 10. Define nodes
    nodes = [
        # Robot State Publisher
        Node(
            package="robot_state_publisher",
            executable="robot_state_publisher",
            name="robot_state_publisher",
            output="screen",
            parameters=[
                moveit_config.robot_description,
                {"use_sim_time": use_sim_bool},
            ],
        ),

        # Static TF Publisher
        Node(
            package="tf2_ros",
            executable="static_transform_publisher",
            name="static_transform_publisher",
            arguments=["0", "0", "0", "0", "0", "0", "world", "base_link"],
        ),

        # RViz
        Node(
            condition=IfCondition(use_rviz),
            package="rviz2",
            executable="rviz2",
            name="rviz2",
            output="screen",
            arguments=["-d", config_files["rviz_config"]],
            parameters=[
                moveit_config.robot_description,
                moveit_config.robot_description_semantic,
                {"use_sim_time": use_sim_bool},
            ],
        ),

        # Move Group Node
        Node(
            package="moveit_ros_move_group",
            executable="move_group",
            name="move_group",
            output="screen",
            parameters=[
                moveit_config.to_dict(),
                move_group_capabilities,
                {"use_sim_time": use_sim_bool},
            ],
        ),

        # Joint State Publisher (Simulation Only)
        Node(
            package="joint_state_publisher",
            executable="joint_state_publisher",
            name="joint_state_publisher",
            condition=IfCondition(use_sim),
            parameters=[
                moveit_config.robot_description,
                {"use_sim_time": use_sim_bool},
            ],
            output="screen",
        ),

        # ROS 2 Control Node (Simulation Only)
        Node(
            package="controller_manager",
            executable="ros2_control_node",
            parameters=[
                moveit_config.robot_description,
                config_files["ros2_controllers_sim"],
                {"use_sim_time": use_sim_bool},
            ],
            condition=IfCondition(use_sim),
            output="screen",
        ),

        # Controller Spawners (Simulation Only)
        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
            condition=IfCondition(use_sim),
            output="screen",
        ),
        Node(
            package="controller_manager",
            executable="spawner",
            arguments=["joint_trajectory_controller", "--controller-manager", "/controller_manager"],
            condition=IfCondition(use_sim),
            output="screen",
        ),

        Node(
            package="worm_picker_core",
            executable="worm_picker_robot",
            output="screen",
            parameters=[
                moveit_config.to_dict(),
                move_group_capabilities,
            ],
        ),
    ]

    return nodes
