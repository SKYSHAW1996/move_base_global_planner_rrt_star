cmake_minimum_required(VERSION 2.8.3)
project(youibot_rrt)
add_definitions(-std=c++11 -Wall -Werror)

find_package(catkin REQUIRED 
  COMPONENTS
    roscpp
    roslint
    tf
    nav_core
    costmap_2d
    base_local_planner
    pluginlib
    visualization_msgs
)

#find_package(Eigen3 REQUIRED)

include_directories(include ${catkin_INCLUDE_DIRS})

#add_definitions(${EIGEN3_DEFINITIONS})

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS
    roscpp
    pluginlib
    costmap_2d
    base_local_planner
    nav_core
    visualization_msgs
)

add_library(${PROJECT_NAME} 
  src/youibot_rrt.cpp
  src/vertex.cpp
)

add_dependencies(youibot_rrt ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})




install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/ DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})
install(FILES rrt_planner_plugin.xml DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})  
