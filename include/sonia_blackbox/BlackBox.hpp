#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sonia_common_ros2/msg/battery_power_messages.hpp>
#include <sonia_common_ros2/msg/motor_power_messages.hpp>
#include <sonia_common_ros2/msg/body_velocity_dvl.hpp>
#include <std_msgs/msg/float32.hpp>
#include <sensor_msgs/msg/imu.hpp>

namespace sonia_blackbox{

    class BlackBox : public rclcpp::Node
    {
        public:
            BlackBox();
            ~BlackBox() override = default;

        private:
            void BatteryCallback(const sonia_common_ros2::msg::BatteryPowerMessages &msg);
            void MotorCallback(const sonia_common_ros2::msg::MotorPowerMessages &msg);
            void DvlCallback(const sonia_common_ros2::msg::BodyVelocityDVL &msg);
            void DepthCallback(const std_msgs::msg::Float32 &msg);
            void ImuCallback(const sensor_msgs::msg::Imu &msg);

            rclcpp::Subscription<sonia_common_ros2::msg::BatteryPowerMessages>::SharedPtr battery_sub;
            rclcpp::Subscription<sonia_common_ros2::msg::MotorPowerMessages>::SharedPtr motor_sub;
            rclcpp::Subscription<sonia_common_ros2::msg::BodyVelocityDVL>::SharedPtr dvl_sub;
            rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub;
            rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr depth_sub;
    };
}