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

            /**
             * @brief Command to beginning recording for the blackbox.
             */
            void startBag();

            /**
             * @brief Command to end the recording for the blackbox.
             */
            void stopBag();

        private:
            
            /**
             * @brief Rotates bags, preserving the most recent bags and removing older ones.
             * @param save_path Directory where bags are saved
             */
            void rotateBags(const std::string save_path);

            /**
             * @brief Publishes node information of its state and quality.
             */
            void publishStatus();

            std::shared_ptr<rosbag2_transport::Recorder> recorder_;
            std::shared_ptr<rclcpp::executors::MultiThreadedExecutor> executor_;

            rclcpp::TimerBase::SharedPtr timer_node_status_;
            rclcpp::Publisher<sonia_common_ros2::msg::NodeStatus>::SharedPtr pub_node_status_;
            
            std::vector<std::string> sources_;
            sonia_common_ros2::msg::NodeStatus node_status_;

            static constexpr auto RECORDER_WAIT = std::chrono::milliseconds(150);
            static constexpr uint16_t SPLIT_DURATION = 3*60; //bag duration per split
            static constexpr size_t MAX_BAG_COUNT = 3; //Maximum of saved bags
            inline static const std::string RECORDER_NODE_NAME = "box_recorder"; //custom recorder node name

    };
} //namespace sonia_blackbox