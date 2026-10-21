#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "custom_msg/msg/controller.hpp"

class Listener : public rclcpp::Node {
public:
    Listener() : Node("listener") {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "chatter", 10, [this](std_msgs::msg::String::SharedPtr msg) {
                RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
            });

        sub_controller = this->create_subscription<custom_msg::msg::Controller>( 
            "controller", 10, std::bind(&Listener::controllerCallback, this, std::placeholders::_1) 
        );  
    }

private:
    void controllerCallback(const custom_msg::msg::Controller::SharedPtr msg) { 
        uint8_t arr[20];  
        memcpy(arr + 3, &msg->velx, 4); 
        memcpy(arr + 7, &msg->vely, 4); 
        memcpy(arr + 11, &msg->angvel, 4); 
    }
    
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    rclcpp::Subscription<custom_msg::msg::Controller>::SharedPtr sub_controller;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Listener>());
    rclcpp::shutdown();
    return 0;
}