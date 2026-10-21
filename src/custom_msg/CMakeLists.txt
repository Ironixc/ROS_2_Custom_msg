cmake_minimum_required(VERSION 3.8)
project(custom_msg)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)

# Define the message file
set(msg_files
    "msg/Controller.msg"
)

# Generate the messages
rosidl_generate_interfaces(${PROJECT_NAME}
    ${msg_files}
    DEPENDENCIES std_msgs
)

# Package configuration
ament_export_dependencies(rosidl_default_runtime)

# ONLY ONE ament_package() at the very end
ament_package()