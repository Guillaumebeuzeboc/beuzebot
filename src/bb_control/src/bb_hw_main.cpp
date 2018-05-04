#include <ros_control_boilerplate/generic_hw_control_loop.h>
#include <bb_control/bb_hw_interface.hpp>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "bb_hw_interface");
  ros::NodeHandle nh;

  // NOTE: We run the ROS loop in a separate thread as external calls such
  // as service callbacks to load controllers can block the (main) control loop
  ros::AsyncSpinner spinner(2);
  spinner.start();

  // Create the hardware interface specific to your robot
  boost::shared_ptr<BBHWInterface> bb_hw_interface
    (new BBHWInterface(nh));
  bb_hw_interface->init();

  // Start the control loop
  ros_control_boilerplate::GenericHWControlLoop control_loop(nh, bb_hw_interface);
  
  ros::waitForShutdown(); 

  return 0;
}
