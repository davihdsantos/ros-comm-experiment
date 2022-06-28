cmake_minimum_required(VERSION 2.8.3)
project(mav_teleop)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  geometry_msgs
  tf2_geometry_msgs
  std_msgs
  visualization_msgs
  mavros_msgs)
include_directories(include ${catkin_INCLUDE_DIRS})

catkin_package(
    INCLUDE_DIRS
    LIBRARIES
    CATKIN_DEPENDS roscpp sensor_msgs geometry_msgs mavros_msgs
    DEPENDS
)

add_executable(mav_teleop src/mav_teleop.cpp)
target_link_libraries(mav_teleop ${catkin_LIBRARIES})
add_dependencies(mav_teleop std_msgs ${catkin_EXPORTED_TARGETS})

add_executable(teleop_remap src/teleop_remap.cpp)
target_link_libraries(teleop_remap ${catkin_LIBRARIES})
add_dependencies(teleop_remap std_msgs ${catkin_EXPORTED_TARGETS})

install(TARGETS mav_teleop teleop_remap
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch
  DESTINATION  ${CATKIN_PACKAGE_SHARE_DESTINATION}
)