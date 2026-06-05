import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    config = os.path.join(
        get_package_share_directory("sonia_blackbox"), "config", "topic_list.yaml"
    )
    return LaunchDescription(
        [
            Node(
                package="sonia_blackbox",
                executable="sonia_blackbox",
                parameters=[config]
            )
        ]
    )