cmake_minimum_required(VERSION 2.8.3)
project(stage_simulator)

find_package(catkin REQUIRED COMPONENTS roscpp)

catkin_package()

install(DIRECTORY
  launch world
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
