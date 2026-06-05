#include <rclcpp/rclcpp.hpp>

#include "sonia_blackbox/BlackBox.hpp"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto box = std::make_shared<sonia_blackbox::BlackBox>();

    auto executor = std::make_shared<rclcpp::executors::MultiThreadedExecutor>();
    
    box->setExecutor(executor);
    box->startBag();
    
    executor->add_node(box);
    executor->spin();

    box->stopBag();
    
    rclcpp::shutdown();
    return EXIT_SUCCESS;
}