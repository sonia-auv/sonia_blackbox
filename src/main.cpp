#include <rclcpp/rclcpp.hpp>

#include "sonia_blackbox/BlackBox.hpp"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto box = std::make_shared<sonia_blackbox::BlackBox>();
    rclcpp::spin(box);
    
    rclcpp::shutdown();
    return EXIT_SUCCESS;
}