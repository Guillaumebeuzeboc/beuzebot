#include <pigpio.h>
#include <iostream>

#include <std_msgs/Float32.h>

#include "bb_pigpio/encoder.hpp"

void bb_encoder::_pulse(int gpio, int level, uint32_t tick) {
    if (gpio == gpioA_)
        levA_ = level;
    else
        levB_ = level;

    if (gpio != lastGpio_) /* debounce */
    {
        lastGpio_ = gpio;

        if ((gpio == gpioA_) && (level == 1)) {
            if (levB_)
                callback(1);
        } else if ((gpio == gpioB_) && (level == 1)) {
            if (levA_)
                callback(-1);
        }
    }
}

bb_encoder::bb_encoder(ros::NodeHandle&   nh,
                       ros::NodeHandle    nh_p,
                       int                gpioA,
                       int                gpioB,
                       const float&       reduction_ratio,
                       const std::string& side)
  : nh_(nh)
  , nh_p_(nh_p)
  , pos_(0)
  , gpioA_(gpioA)
  , gpioB_(gpioB)
  , levA_(0)
  , levB_(0)
  , lastGpio_(-1)
  , reduction_ratio_(reduction_ratio) {
    gpioSetMode(gpioA_, PI_INPUT);
    gpioSetMode(gpioB_, PI_INPUT);

    /* pull up is needed as encoder common is grounded */

    gpioSetPullUpDown(gpioA_, PI_PUD_UP);
    gpioSetPullUpDown(gpioB_, PI_PUD_UP);

    /* monitor encoder level changes */

    gpioSetAlertFuncEx(gpioA_, _pulseEx, this);
    gpioSetAlertFuncEx(gpioB_, _pulseEx, this);

    pub_pos_ = nh.advertise<std_msgs::Float32>("pos_" + side + "_encoder", 1);
}

bb_encoder::~bb_encoder() {
    gpioSetAlertFuncEx(gpioA_, 0, this);
    gpioSetAlertFuncEx(gpioB_, 0, this);
}

void bb_encoder::update() const {
    std_msgs::Float32 msg;
    msg.data = pos_ / reduction_ratio_;
    pub_pos_.publish(msg);
}

void bb_encoder::_pulseEx(int gpio, int level, uint32_t tick, void* user) {
    /*
       Need a static callback to link with C.
    */

    bb_encoder* mySelf = (bb_encoder*)user;

    mySelf->_pulse(gpio, level, tick); /* Call the instance callback. */
}

void bb_encoder::callback(int way) {
    pos_ += way;
}
