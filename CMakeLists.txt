cmake_minimum_required(VERSION 2.8.3)
project(rosbag_health_check)

find_package(catkin REQUIRED COMPONENTS roscpp
  rosbag
  xmlrpcpp
)

catkin_package(
  INCLUDE_DIRS include/
  CATKIN_DEPENDS roscpp
  xmlrpcpp
)

include_directories(
  ${catkin_INCLUDE_DIRS},
  include/${PROJECT_NAME}
)

add_executable(${PROJECT_NAME}_node src/rosbag_health_check.cpp)
add_dependencies(
  ${PROJECT_NAME}
  ${catkin_EXPORTED_LIBRARIES}
  ${catkin_LIBRARIES}
)

install(DIRECTORY launch
		DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

install(DIRECTORY config
		DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

install(DIRECTORY include/${PROJECT_NAME}/
		DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})
