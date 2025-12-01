cmake_minimum_required(VERSION 3.5)
project(bt_assignment)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
.
# Find the installed BehaviorTree library
find_package(behaviortree_cpp REQUIRED)

# Create the executable
add_executable(robot_main main.cpp)

# Link the library
target_link_libraries(robot_main PRIVATE behaviortree_cpp)
