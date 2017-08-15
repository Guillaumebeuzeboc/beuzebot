#include "bb_serial/serial.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "bb_serial");
    ros::NodeHandle nh;
    ros::NodeHandle nh_p("~");

    bb_serial serial_com(nh, nh_p);

    //    int frequency = 10;
    //    nh_p.param<int>("frequency", frequency, frequency);

    //    ros::Rate rate(frequency);

    //    while (ros::ok()) {
    //        ros::spinOnce();
    //        rate.sleep();
    //    }
    ros::spin();

    return 0;
}
