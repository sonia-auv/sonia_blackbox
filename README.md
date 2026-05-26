# sonia_blackbox

*description here*

---

## Dependencies

### ROS 2 Distro

* Humble

### ROS 2 Packages

* `ament_cmake`
* `rclcpp`
* `std_msgs`
* `std_srvs`
* `sensor_msgs`

### Sonia packages

* `sonia_common_ros2`

---

## Node

* Name: `provider_blackbox`

---

## Registered Topics / Services / Actions

| Type       | Name                          | Direction      | Message/Service Type                     | Description                          |
| ---------- | ----------------------------- | -------------- | ---------------------------------------- | ------------------------------------ |
| Topic      | `/system_monitor/node_status` | Published      | `sonia_common_ros2/msg/NodeStatus`       | Message contains information of the state of a node |

---
## Build Instructions
To build the project, the following commands should be run directly from your ROS2 workspace.

```bash
colcon build --packages-select sonia_blackbox--symlink-install
source install/setup.bash
```
---

## Launch Instructions

### Default launch

```bash
ros2 launch sonia_blackbox launch.py
```

---

## Useful ROS 2 Commands

```bash
ros2 node list
ros2 node info /provider_blackbox
ros2 param list /provider_blackbox
```

---

## References

* [sonia_common_ros2](https://github.com/sonia-auv/sonia_common_ros2)

---