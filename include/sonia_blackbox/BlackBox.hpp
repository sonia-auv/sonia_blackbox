#pragma once

#include <rclcpp/rclcpp.hpp>

namespace sonia_blackbox{
    class BlackBox : public rclcpp::Node
    {
        public:
            BlackBox();
            ~BlackBox() = default;
        private:


    };
}