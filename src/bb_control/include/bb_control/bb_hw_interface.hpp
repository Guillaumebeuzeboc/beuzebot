#ifndef BB_CONTROL__BB_HW_INTERFACE_HPP
#define BB_CONTROL__BB_HW_INTERFACE_HPP

#include <ros_control_boilerplate/generic_hw_interface.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>

/// \brief Hardware interface for a robot
class BBHWInterface : public ros_control_boilerplate::GenericHWInterface
{
public:
  /**
   * \brief Constructor
   * \param nh - Node handle for topics.
   */
  BBHWInterface(ros::NodeHandle& nh, urdf::Model* urdf_model = NULL);

  /** \brief Read the state from the robot hardware. */
  virtual void init();

  /** \brief Read the state from the robot hardware. */
  virtual void read(ros::Duration &elapsed_time);

  /** \brief Write the command to the robot hardware. */
  virtual void write(ros::Duration &elapsed_time);

  /** \breif Enforce limits for all values before writing */
  virtual void enforceLimits(ros::Duration &period);

private:

  void readVelocityCB(const std_msgs::Float32::ConstPtr& msg, int joint_nbr);

  ros::Subscriber sub_velocity_[2];
  ros::Publisher pub_velocity_[2];

  float measured_velocity[2];
  float measured_position[2];
  float previous_measured_position[2];

  ros::Publisher pub_ready_;

};  // class

#endif

