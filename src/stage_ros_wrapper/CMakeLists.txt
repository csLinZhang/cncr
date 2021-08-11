cmake_minimum_required(VERSION 2.8.3)
project(stage_ros_wrapper)

find_package(catkin REQUIRED
  COMPONENTS
    geometry_msgs
    nav_msgs
    roscpp
    sensor_msgs
    std_msgs
    std_srvs
    tf
    cv_bridge
)

find_package(Boost REQUIRED COMPONENTS system thread)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

catkin_package()

add_executable(stage_ros_wrapper src/main.cpp src/stage_ros_wrapper.cpp)
target_link_libraries(stage_ros_wrapper
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
  # ${STAGE_LIBRARIES}
  stage
  fltk
)

install(TARGETS stage_ros_wrapper
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
