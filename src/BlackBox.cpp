#include "sonia_blackbox/BlackBox.hpp"

using std::placeholders::_1;
namespace sonia_blackbox{
    BlackBox::BlackBox(): Node("provider_blackbox")
    {
        battery_sub = create_subscription<sonia_common_ros2::msg::BatteryPowerMessages>("/provider_power/battery_voltages",10, std::bind(&BlackBox::BatteryCallback, this, _1));
        motor_sub =create_subscription<sonia_common_ros2::msg::MotorPowerMessages>("/provider_power/motor_voltages",10, std::bind(&BlackBox::MotorCallback, this, _1));
        dvl_sub = create_subscription<sonia_common_ros2::msg::BodyVelocityDVL>("/provider_dvl/dvl_velocity",10, std::bind(&BlackBox::DvlCallback, this, _1));
        depth_sub = create_subscription<std_msgs::msg::Float32>("provider_depth/depth",10, std::bind(&BlackBox::DepthCallback, this, _1));
        imu_sub = create_subscription<sensor_msgs::msg::Imu>("provider_imu/imu_info",10, std::bind(&BlackBox::ImuCallback, this, _1));
        
    }
    void BlackBox::BatteryCallback(const sonia_common_ros2::msg::BatteryPowerMessages &msg)
    {
    }

    void BlackBox::MotorCallback(const sonia_common_ros2::msg::MotorPowerMessages &msg)
    {
    }

    void BlackBox::DvlCallback(const sonia_common_ros2::msg::BodyVelocityDVL &msg)
    {
    }

    void BlackBox::DepthCallback(const std_msgs::msg::Float32 &msg)
    {
    }

    void BlackBox::ImuCallback(const sensor_msgs::msg::Imu &msg)
    {
    }

}

