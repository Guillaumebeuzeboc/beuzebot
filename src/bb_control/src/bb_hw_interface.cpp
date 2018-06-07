#include <bb_control/bb_hw_interface.hpp>
#include <exception>
#include <angles/angles.h>
#include <std_msgs/Bool.h>

BBHWInterface::BBHWInterface(ros::NodeHandle &nh, urdf::Model *urdf_model)
  : ros_control_boilerplate::GenericHWInterface(nh, urdf_model)
{
  sub_velocity_[0] = nh_.subscribe<std_msgs::Float32> ("/hw/left_encoder/position", 2, boost::bind(&BBHWInterface::readVelocityCB, this, _1, 0));
  sub_velocity_[1] = nh_.subscribe<std_msgs::Float32> ("/hw/right_encoder/position", 2, boost::bind(&BBHWInterface::readVelocityCB, this, _1, 1));
  pub_velocity_[0] = nh_.advertise<std_msgs::Float32> ("hw/left_motor/command", 1);
  pub_velocity_[1] = nh_.advertise<std_msgs::Float32> ("hw/right_motor/command", 1);

  pub_ready_ = nh_.advertise<std_msgs::Bool> ("/controller/ready", 1, true);
}

void BBHWInterface::init()
{
  GenericHWInterface::init();

  ROS_INFO_NAMED("bb_hw_interface", "BBHWInterface Ready.");
  if(num_joints_!=2){
    ROS_ERROR("Beuzebot is supposed to have only two joints and not %d !", static_cast<int>(num_joints_));
    throw std::exception();
    return;
  }

  for (std::size_t joint_id = 0; joint_id < num_joints_; ++joint_id){
    measured_velocity[joint_id]= 0.0;
    measured_position[joint_id]= 0.0;
    previous_measured_position[joint_id]= 0.0;
  }

  std_msgs::Bool msg;
  msg.data = true;
  pub_ready_.publish(msg);
}

void BBHWInterface::read(ros::Duration &elapsed_time)
{
  for (std::size_t joint_id = 0; joint_id < num_joints_; ++joint_id){
    previous_measured_position[joint_id] = joint_position_[joint_id];
    const double normalized_angle = angles::normalize_angle(measured_position[joint_id]);
    joint_position_[joint_id] = normalized_angle;
    joint_velocity_[joint_id] = angles::normalize_angle(normalized_angle - previous_measured_position[joint_id]) / elapsed_time.toSec();

  }

}

void BBHWInterface::write(ros::Duration &elapsed_time)
{
  // Safety
  enforceLimits(elapsed_time);
  for (std::size_t joint_id = 0; joint_id < num_joints_; ++joint_id){
    std_msgs::Float32 data;
    data.data = joint_velocity_command_[joint_id];
    pub_velocity_[joint_id].publish(data);
  }

}

void BBHWInterface::enforceLimits(ros::Duration &period)
{
  // Enforces velocity and acceleration limits
  vel_jnt_sat_interface_.enforceLimits(period);
}

void BBHWInterface::readVelocityCB(const std_msgs::Float32::ConstPtr& msg, int joint_nbr)
{
  measured_position[joint_nbr] = msg->data;
}
