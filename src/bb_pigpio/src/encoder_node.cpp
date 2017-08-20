#include <pigpio.h>
#include "bb_pigpio/encoder.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "bb_encoder");
    ros::NodeHandle nh;
    ros::NodeHandle nh_p("~");

    if (gpioInitialise() < 0) return 1;
    bb_encoder encoder(nh, nh_p, 5, 6);

    ros::Rate rate(10);
    while (ros::ok()) {
        ros::spinOnce();
        encoder.update();
        rate.sleep();
    }
    gpioTerminate();
    return 0;
}
