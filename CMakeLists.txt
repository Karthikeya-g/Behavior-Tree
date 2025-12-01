cmake_minimum_required(VERSION 3.14)CMakeLists.txt
project(bt_apple_picker)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- THE "INSTALLATION" STEP ---
# This block tells CMake: "Go get this library from the internet"
include(FetchContent)

message(STATUS "Downloading BehaviorTree.CPP (v3.8)...")
FetchContent_Declare(
  behaviortree_cpp_v3
  GIT_REPOSITORY https://github.com/BehaviorTree/BehaviorTree.CPP.git
  GIT_TAG        v3.8.6  # Assignment asks for V3 compatibility
)
# This command builds and "installs" it into your project memory
FetchContent_MakeAvailable(behaviortree_cpp_v3)

# --- YOUR EXECUTABLE ---
add_executable(bt_main main.cpp)

# Link the library we just downloaded
target_link_libraries(bt_main PRIVATE BT::behaviortree_cpp_v3)
target_include_directories(bt_main PRIVATE ${behaviortree_cpp_v3_SOURCE_DIR}/include)
