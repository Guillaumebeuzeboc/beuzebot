cmake_minimum_required(VERSION 2.8.3)
project(bb_cartographer)

find_package(catkin REQUIRED COMPONENTS
  cartographer_ros
  depthimage_to_laserscan
  message_runtime
  openni2_launch
  roscpp
  roslib
  sensor_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES bb_cartographer
#  CATKIN_DEPENDS cartographer_ros depthimage_to_laserscan message_runtime openni2_launch roscpp roslib sensor_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

#############
## Install ##
#############

 install(DIRECTORY launch/
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
 )

 install(DIRECTORY config/
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/config
 )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_bb_cartographer.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
