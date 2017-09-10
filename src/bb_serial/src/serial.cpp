#include "exception"

#include "bb_serial/serial.hpp"

bb_serial::bb_serial(ros::NodeHandle& nh, const ros::NodeHandle& nh_p)
  : nh_(nh)
  , nh_p_(nh_p) {
    max_vel_ = nh_p_.param<float>("max_velocity", 10.4719755f);

    ios_               = std::make_shared<boost::asio::io_service>();
    std::string device = nh_p_.param<std::string>("device", "/dev/ttyUSB0");
    try {
        sp_ = std::make_shared<boost::asio::serial_port>(*ios_, device);
    } catch (boost::system::system_error& e) {
        ROS_ERROR("Fail to create serial port: %s", e.what());
        throw std::exception();
        return;
    }

    sp_->set_option(boost::asio::serial_port::baud_rate(9600));

    pub_left_motor_ =
        nh_.subscribe<std_msgs::Float32>("hw/left_motor/command", 1, boost::bind(&bb_serial::motorCb, this, _1, 0));
    pub_right_motor_ =
        nh_.subscribe<std_msgs::Float32>("hw/right_motor/command", 1, boost::bind(&bb_serial::motorCb, this, _1, 127));
}

bb_serial::~bb_serial() {
    int8_t stop_move = 0;
    sp_->write_some(boost::asio::buffer(&stop_move, sizeof(stop_move)));
    sp_->close();
}

void bb_serial::motorCb(const std_msgs::Float32::ConstPtr& msg, int offset) {
    uint8_t cmd_to_send = computeSpeed(msg->data, offset);

    sp_->write_some(boost::asio::buffer(&cmd_to_send, sizeof(cmd_to_send)));
}

uint8_t bb_serial::computeSpeed(float speed, int offset) const {
    if (speed > 0) {
        speed = std::min(speed, max_vel_);
    } else {
        speed = std::max(speed, -max_vel_);
    }
    return speed * 63 / max_vel_ + 64 + offset;
}
