#ifndef ENCODER_HPP
#define ENCODER_HPP
#include <stdint.h>

#include <ros/ros.h>

class bb_encoder {
  public:
    /**
       * @brief encoder, class for reading an encoder
       * @param gpioA
       * @param gpioB
       */
    bb_encoder(ros::NodeHandle& nh, ros::NodeHandle nh_p, int gpioA, int gpioB);

    ~bb_encoder();

    void update() const;

  private:
    void _pulse(int gpio, int level, uint32_t tick);

    void callback(int way);

    /* Need a static callback to link with C. */
    static void _pulseEx(int gpio, int level, uint32_t tick, void* user);

    ros::NodeHandle nh_;
    ros::NodeHandle nh_p_;
    ros::Publisher  pub_pos_left_;
    int             gpioA_;
    int             gpioB_;
    int             levA_;
    int             levB_;
    int             lastGpio_;
    int             pos_;
};

#endif  // ENCODER_HPP
