#include <ros/ros.h>
#include <std_msgs/Empty.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "bb_encoder_killer", ros::init_options::NoSigintHandler);
    ros::NodeHandle nh;
    ros::NodeHandle nh_p("~");

    ros::Publisher pub_alive = nh.advertise<std_msgs::Empty>("/hw/bb_pigpio/stay_alive", 1);

    ros::Rate rate(10);
    std_msgs::Empty msg;
    while (ros::ok()) {
        ros::spinOnce();
        pub_alive.publish(msg);
        rate.sleep();
    }
    ROS_INFO("bb_encoder killer killed");

    return 0;
}
