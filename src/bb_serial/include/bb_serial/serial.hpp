#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>

class bb_serial {
  public:
    bb_serial(ros::NodeHandle& nh, const ros::NodeHandle& nh_p);
    ~bb_serial();

  private:
    /**
     * @brief motorCb
     * @param msg, speed in rad/s
     * @param offset
     */
    void motorCb(const std_msgs::Float32::ConstPtr& msg, int offset);

    uint8_t computeSpeed(float speed, int offset = 0) const;

    ros::NodeHandle nh_;
    ros::NodeHandle nh_p_;

    std::shared_ptr<boost::asio::io_service>  ios;
    std::shared_ptr<boost::asio::serial_port> sp_;

    ros::Subscriber pub_left_motor_;
    ros::Subscriber pub_right_motor_;

    float max_vel_;
};

#endif  // SERIAL_HPP
