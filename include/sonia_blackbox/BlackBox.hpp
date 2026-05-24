#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sonia_common_ros2/msg/node_status.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <rosbag2_transport/recorder.hpp>

namespace sonia_blackbox{

    class BlackBox : public rclcpp::Node
    {
        public:
            BlackBox();
            ~BlackBox() override = default;

            /**
             * @brief Setter to add an internal node to the main multithreadedexecutor.
             * @param executor Passed executor.
             */
            void setExecutor(std::shared_ptr<rclcpp::executors::MultiThreadedExecutor> executor);

        private:
            /**
             * @brief Process client requests for ros bag recordings.
             * @param request Request information from the client.
             * @param response Response from the server.
             */
            void processRecordRequest(const std::shared_ptr<std_srvs::srv::Trigger::Request> request, std::shared_ptr<std_srvs::srv::Trigger::Response> response);
            /**
             * @brief Publishes node information of its state and quality.
             */
            void publishStatus();

            std::shared_ptr<rosbag2_transport::Recorder> recorder_;
            std::shared_ptr<rclcpp::executors::MultiThreadedExecutor> executor_;

            rclcpp::TimerBase::SharedPtr timer_node_status_;
            rclcpp::Publisher<sonia_common_ros2::msg::NodeStatus>::SharedPtr pub_node_status_;
            rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr box_service_;
            
            std::string save_path_;
            std::vector<std::string> sources_;
            std::atomic<bool> is_recording_;
            sonia_common_ros2::msg::NodeStatus node_status_;

            static constexpr auto RECORDER_WAIT = std::chrono::milliseconds(150);
            
    };
}