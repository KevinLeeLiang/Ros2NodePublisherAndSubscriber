#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"
int main ()
{
  auto t = rclcpp::Clock().now();
  std::cout << typeid (t.nanoseconds()).name() << std::endl;
  std_msgs::msg::Int64 time_last_;
  std::cout << typeid (time_last_).name() << std::endl;
  //time_last_(t.nanoseconds());
  long ll = t.nanoseconds();
  time_last_.data = t.nanoseconds();
  if (sizeof(typeid (time_last_).name()) == sizeof(typeid (t.nanoseconds()).name()))
    std::cout << "ok" <<std::endl;
  else 
    std::cout << "false" << std::endl;
  
  printf("[rclcpp::Clock().now()] sec:%lf nano:%ld, test:%ld", t.seconds(), t.nanoseconds(), time_last_.data);

//   auto t1 = std::chrono::system_clock::now(); 
//   time_t tt = std::chrono::system_clock::to_time_t ( t1 );
//   RCLCPP_INFO(this->get_logger(), "[std::chrono::system_clock::now()] sec:%ld", tt);

//   std::chrono::steady_clock::time_point td = std::chrono::steady_clock::now(); 
//   std::chrono::steady_clock::duration dtn = td.time_since_epoch();
//   double secs = dtn.count() * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
//   RCLCPP_INFO(this->get_logger(), "[std::chrono::steady_clock::now()] sec:%lf", secs);

//   auto t2 = this->get_clock()->now();
//   RCLCPP_INFO(this->get_logger(), "[get_clock()->now()] sec:%lf nano:%ld", t2.seconds(), t2.nanoseconds());

//   auto t3 = this->now();
//   RCLCPP_INFO(this->get_logger(), "[this->now()] sec:%lf nano:%ld", t3.seconds(), t3.nanoseconds());

  return 0;
}