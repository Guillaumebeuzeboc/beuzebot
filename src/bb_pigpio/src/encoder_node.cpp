#include "bb_pigpio/encoder.hpp"
#include "bb_pigpio/shutdown_callback.hpp"
#include <pigpio.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "bb_encoder", ros::init_options::NoSigintHandler);
    ros::NodeHandle nh;
    ros::NodeHandle nh_p("~");

    if (gpioInitialise() < 0)
        return 1;

    float reduction_ratio_left = nh_p.param<float>("reduction_ratio_left", 1633);
    float reduction_ratio_right = nh_p.param<float>("reduction_ratio_right", 1633);

    int        gpio_left_A  = nh_p.param<int>("gpio_left_A", 5);
    int        gpio_left_B  = nh_p.param<int>("gpio_left_B", 6);
    int        gpio_right_A = nh_p.param<int>("gpio_right_A", 13);
    int        gpio_right_B = nh_p.param<int>("gpio_right_B", 19);
    bb_encoder encoder_left(nh, nh_p, gpio_left_A, gpio_left_B, reduction_ratio_left, "left");
    bb_encoder encoder_right(nh, nh_p, gpio_right_A, gpio_right_B, reduction_ratio_right, "right");

    // Override the default ros sigint handler
    signal(SIGINT, mySigIntHandler);

    // Override XMLRPC shutdown
    ros::XMLRPCManager::instance()->unbind("shutdown");
    ros::XMLRPCManager::instance()->unbind("shutdown");

    ros::Rate rate(10);
    while (!g_request_shutdown) {
        ros::spinOnce();
        encoder_left.update();
        encoder_right.update();
        rate.sleep();
    }
    gpioTerminate();

    ros::shutdown();

    return 0;
}
