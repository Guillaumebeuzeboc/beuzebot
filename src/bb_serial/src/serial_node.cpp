#include "bb_serial/serial.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "bb_serial");
    ros::NodeHandle nh;
    ros::NodeHandle nh_p("~");
    
    std::shared_ptr<bb_serial> serial_com;
    try {
        serial_com = std::make_shared<bb_serial>(nh, nh_p);
    } catch (...) {
        return 0;
    }

    ros::spin();

    return 0;
}
