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
    BlackBox::BlackBox(): Node("blackbox_provider"), is_recording_{false}
    {
        auto pwuid = getpwuid(getuid());
        if (pwuid == nullptr)
        {
            throw std::runtime_error("Can't find HOME directory");
        }
        //Generate list of node names to be monitored from a config file
        this->declare_parameter("node_list", rclcpp::PARAMETER_STRING_ARRAY);
        sources_ = this->get_parameter("topic_list").as_string_array();

        std::string path = pwuid->pw_dir;
        save_path_ = path + "/ssd/vault/";

        pub_node_status_ = this->create_publisher<sonia_common_ros2::msg::NodeStatus>("/system_monitor/node_status", 1);
        box_service_ = this->create_service<std_srvs::srv::Trigger>(
            "/provider_blackbox/record", std::bind(&BlackBox::processRecordRequest, this, _1, _2));
        timer_node_status_ = this->create_wall_timer(500ms, std::bind(&BlackBox::publishStatus, this));

        node_status_.node_name = this->get_name();
        node_status_.quality = sonia_common_ros2::msg::NodeStatus::Q_OK;
        node_status_.state = sonia_common_ros2::msg::NodeStatus::STATE_IDLE;
    }

    void BlackBox::processRecordRequest(
        const std::shared_ptr<std_srvs::srv::Trigger::Request> request, std::shared_ptr<std_srvs::srv::Trigger::Response> response)
    {
        if(!is_recording_){
            auto file_path = save_path_;
            auto writer = std::make_shared<rosbag2_cpp::Writer>();
            rosbag2_storage::StorageOptions options;
            options.max_bagfile_size = 500000000; //500Mb
            options.uri = file_path;
            options.storage_id = "mcap";

            rosbag2_transport::RecordOptions record_options;
            record_options.all = false;
            record_options.topics = sources_;
            record_options.rmw_serialization_format = "cdr";

            recorder_ = std::make_shared<rosbag2_transport::Recorder>(writer, options, record_options);

            recorder_->record();
            is_recording_ = true;
            response->message = "Recording started";

            node_status_.state = sonia_common_ros2::msg::NodeStatus::STATE_RUNNING;
        }
        else
        {
            recorder_->stop();
            is_recording_ = false;
            response->message = "Recording stopped, rosbag saved : ";
            node_status_.state = sonia_common_ros2::msg::NodeStatus::STATE_IDLE;
        }
    }

    void BlackBox::publishStatus()
    {
        node_status_.stamp = this->now();
        pub_node_status_->publish(node_status_);
    }
   
}

