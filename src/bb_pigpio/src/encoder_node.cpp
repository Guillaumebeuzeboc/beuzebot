#include "bb_pigpio/encoder.hpp"
#include <pigpio.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "bb_encoder");
    ros::NodeHandle nh;
    ros::NodeHandle nh_p("~");

    if (gpioInitialise() < 0)
        return 1;

    float reduction_ratio = nh_p.param<float>("reduction_ratio", 1633);

    int        gpio_left_A  = nh_p.param<int>("gpio_left_A", 5);
    int        gpio_left_B  = nh_p.param<int>("gpio_left_B", 6);
    int        gpio_right_A = nh_p.param<int>("gpio_right_A", 13);
    int        gpio_right_B = nh_p.param<int>("gpio_right_B", 19);
    bb_encoder encoder_left(nh, nh_p, gpio_left_A, gpio_left_B, reduction_ratio, "left");
    bb_encoder encoder_right(nh, nh_p, gpio_right_A, gpio_right_B, reduction_ratio, "right");

    ros::Rate rate(10);
    while (ros::ok()) {
        ros::spinOnce();
        encoder_left.update();
        encoder_right.update();
        rate.sleep();
    }
    gpioTerminate();
    return 0;
}
