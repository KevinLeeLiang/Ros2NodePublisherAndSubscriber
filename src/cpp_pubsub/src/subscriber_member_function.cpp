#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */
std_msgs::msg::Int64 time_last_;
auto t1 = rclcpp::Clock().now();


class TopicBComponent : public rclcpp::Node
{
  public:
    TopicBComponent()
    : Node("topica_componnet")
    {
      time_last_.data = t1.nanoseconds();
      publisher_ = this->create_publisher<std_msgs::msg::Int64>("topicB", 100);
      subscription_ = this->create_subscription<std_msgs::msg::Int64>(
                        "topicA", 100, std::bind(&TopicBComponent::topic_callback, this, _1));
      timer_ = this->create_wall_timer(
                        500ms, std::bind(&TopicBComponent::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      auto message = std_msgs::msg::Int64();
      t1 = rclcpp::Clock().now();
      message.data = t1.nanoseconds();
      RCLCPP_INFO(this->get_logger(), "topicB Publishing: '%d'", message.data - time_last_.data);
      publisher_->publish(message);
    }
    void topic_callback(const std_msgs::msg::Int64::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "I heard topicA: '%d'", msg->data);
      time_last_.data = msg->data;
    }
    rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr subscription_;
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TopicBComponent>());
  rclcpp::shutdown();
  return 0;
}
