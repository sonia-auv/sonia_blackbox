#include <pwd.h>
#include <unistd.h>
#include <chrono>
#include <filesystem>
#include <rosbag2_storage/storage_options.hpp>
#include <rosbag2_transport/record_options.hpp>

#include "sonia_blackbox/BlackBox.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;
namespace sonia_blackbox{
    BlackBox::BlackBox(): Node("blackbox_provider")
    {
        //Generate list of node names to be monitored from a config file
        this->declare_parameter("topic_list", rclcpp::PARAMETER_STRING_ARRAY);
        sources_ = this->get_parameter("topic_list").as_string_array();

        auto pwuid = getpwuid(getuid());
        if (pwuid == nullptr)
        {
            throw std::runtime_error("Can't find HOME directory");
        }   

        std::string path = pwuid->pw_dir;
        save_path_ = path + "/ssd/vault/";

        pub_node_status_ = this->create_publisher<sonia_common_ros2::msg::NodeStatus>("/system_monitor/node_status", 1);
        timer_node_status_ = this->create_wall_timer(500ms, std::bind(&BlackBox::publishStatus, this));

        node_status_.node_name = this->get_name();
        node_status_.quality = sonia_common_ros2::msg::NodeStatus::Q_OK;
        node_status_.state = sonia_common_ros2::msg::NodeStatus::STATE_IDLE;
    }

    void BlackBox::setExecutor(std::shared_ptr<rclcpp::executors::MultiThreadedExecutor> executor)
    {
        executor_= executor;
    }

    void BlackBox::startBag()
    {
            auto file_path = save_path_ + "black_box";
            auto writer = std::make_shared<rosbag2_cpp::Writer>();
            rosbag2_storage::StorageOptions options;
            options.max_bagfile_duration = SPLIT_DURATION;
            options.uri = file_path;
            options.storage_id = "mcap";

            rosbag2_transport::RecordOptions record_options;
            record_options.all = false;
            record_options.topics = sources_;
            record_options.rmw_serialization_format = "cdr";

            recorder_ = std::make_shared<rosbag2_transport::Recorder>(writer, options, record_options, RECORDER_NODE_NAME);
            executor_->add_node(recorder_);

            recorder_->record();

            node_status_.state = sonia_common_ros2::msg::NodeStatus::STATE_RUNNING;
    }
    void BlackBox::stopBag()
    {
        recorder_->stop();
        std::this_thread::sleep_for(RECORDER_WAIT); //sleep to allow recorder to stop correctly
    
        executor_->remove_node(recorder_->get_node_base_interface());
        recorder_.reset();

        node_status_.state = sonia_common_ros2::msg::NodeStatus::STATE_IDLE;
    }

    void BlackBox::publishStatus()
    {
        node_status_.stamp = this->now();
        pub_node_status_->publish(node_status_);
    }
   
}

