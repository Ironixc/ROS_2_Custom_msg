cmake_minimum_required(VERSION 3.8)
project(simple_demo_cpp)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
# Fixed name: must match the exact package name of your messages
find_package(custom_msg REQUIRED) 

# Include dirs (opsional kalau ada header tambahan)
include_directories(
    include
)

add_executable(talker src/talker.cpp)
ament_target_dependencies(talker
    rclcpp
    std_msgs
    custom_msg
)

add_executable(listener src/listener.cpp)
ament_target_dependencies(listener
    rclcpp
    std_msgs
    custom_msg
)

install(TARGETS
    talker
    listener
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()