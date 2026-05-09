#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sonia_common_ros2/msg/node_status.hpp>
#include <sonia_common_ros2/srv/record_bag_service.hpp>
#include <rosbag2_transport/recorder.hpp>

namespace sonia_blackbox{

    class BlackBox : public rclcpp::Node
    {
        public:
            BlackBox();
            ~BlackBox() override = default;

        private:
            /**
             * @brief Process client requests for ros bag recordings.
             * @param request Request information from the client.
             * @param response Response from the server.
             */
            void processRecordRequest(const std::shared_ptr<sonia_common_ros2::srv::RecordBagService::Request> request, std::shared_ptr<sonia_common_ros2::srv::RecordBagService::Response> response);
            /**
             * @brief Publishes node information of its state and quality.
             */
            void publishStatus();

            std::shared_ptr<rosbag2_transport::Recorder> recorder_;

            rclcpp::TimerBase::SharedPtr timer_node_status_;
            rclcpp::Publisher<sonia_common_ros2::msg::NodeStatus>::SharedPtr pub_node_status_;
            rclcpp::Service<sonia_common_ros2::srv::RecordBagService>::SharedPtr box_service_;
            
            std::string save_path_;
            std::string filename_;
            bool is_recording_;
            sonia_common_ros2::msg::NodeStatus node_status_;
            
    };
}