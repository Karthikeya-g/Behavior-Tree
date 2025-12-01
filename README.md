# Behavior Tree: Apple Picking Task

This repository implements a **Behavior Tree (BT)** in C++ to solve the robotic pick-and-place mission described in the assignment. It uses the `BehaviorTree.CPP` library (v3).

## 🧠 Logic Implementation
The flowchart requirements were mapped to Behavior Tree Control Nodes:

1.  **Sequence Node (`->`):** Used for the main mission flow (Move -> Enter -> Pick -> Exit). All steps must succeed for the mission to complete.
2.  **Fallback Node (`?`):** Used to solve the **"Is Door Closed?"** decision diamonds.
    * *Strategy:* `[IsDoorOpen] ? [OpenDoor]`
    * *Logic:* The robot checks if the door is open. If `FAILURE` (Door is closed), the Fallback node catches the failure and executes the recovery action (`OpenDoor`).

## 🚀 How to Run (Cross-Platform)
I used **CMake FetchContent** to automatically download and build the dependencies. **No manual installation of the library is required.**

### Prerequisites
* C++ Compiler
* CMake (3.14 or higher)

### Build Steps
1.  **Clone the repo:**
    ```bash
    git clone <https://github.com/Karthikeya-g/Behavior-Tree>
    cd Behavior-Tree
    ```
2.  **Configure and Build:**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build . --config Release
    ```
3.  **Run:**
    * *Windows:* `.\Release\bt_main.exe`
    * *Linux/Mac:* `./bt_main`

## 📂 Project Structure
* `main.cpp`: Contains the dummy `ActionNodes` and the XML tree definition.
* `CMakeLists.txt`: Build configuration with automatic dependency management.
