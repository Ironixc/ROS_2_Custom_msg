#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "custom_msg/msg/controller.hpp"
#include <chrono>
#include <memory>

class Talker : public rclcpp::Node {
public:
    Talker() : Node("talker"), count_(0) {
        // ACTION: Create both publishers inside the constructor
        publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);
        pub_pos = this->create_publisher<custom_msg::msg::Controller>("controller", 10);
        
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1), 
            std::bind(&Talker::timer_callback, this)
        );
    }

private:
    void timer_callback() {
        auto message = std_msgs::msg::String();
        message.data = "Hello ROS2 " + std::to_string(count_++);
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
    }

    // DECLARATIONS: Create the empty boxes here
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Publisher<custom_msg::msg::Controller>::SharedPtr pub_pos;
    rclcpp::TimerBase::SharedPtr timer_;
    custom_msg::msg::Controller controller_msg;
    int count_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Talker>());
    rclcpp::shutdown();
    return 0;
}