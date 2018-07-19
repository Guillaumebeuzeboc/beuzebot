cmake_minimum_required(VERSION 2.8.3)
project(bb_description)

find_package(catkin REQUIRED)

catkin_package()

#############
## Install ##
#############

 install(DIRECTORY launch/
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
 )

 install(DIRECTORY rviz/
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/rviz
 )

 install(DIRECTORY urdf/
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/urdf
 )


#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_bb_description.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
