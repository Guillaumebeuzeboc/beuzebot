cmake_minimum_required(VERSION 2.8.3)
project(bb_control)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  ros_control_boilerplate
  angles
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES bb_control
  CATKIN_DEPENDS ros_control_boilerplate angles

)
###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(bb_hw_interface
  src/bb_hw_interface.cpp
)
target_link_libraries(bb_hw_interface
  ${catkin_LIBRARIES}
)

add_executable(bb_hw_main src/bb_hw_main.cpp)
target_link_libraries(bb_hw_main
  bb_hw_interface
  ${catkin_LIBRARIES}
)


#############
## Install ##
#############

 # install librairies
 install(TARGETS bb_hw_interface
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
 )

 # install executables
 install(TARGETS bb_hw_main
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )

 install(DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*.hpp"
 )

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
# catkin_add_gtest(${PROJECT_NAME}-test test/test_bb_control.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
