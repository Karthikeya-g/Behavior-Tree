
# Robot Behavior Tree Assignment

This repository contains a C++ implementation of a Behavior Tree (BT) that simulates a robot navigating a room, interacting with doors, and fetching an apple. This project relies on the [BehaviorTree.CPP](https://github.com/BehaviorTree/BehaviorTree.CPP) library.

## 📋 Task Overview

The robot performs the following sequence based on the assigned flowchart:
1.  Moves to the room door.
2.  Checks if the door is open (if closed, it opens it).
3.  Enters the room.
4.  Moves to the fridge.
5.  Checks if the fridge is open (if closed, it opens it).
6.  Finds and picks the apple.
7.  Closes the fridge.
8.  Exits the room.

## ⚙️ Dependencies

* **Operating System:** Linux (Ubuntu 22.04 via WSL recommended)
* **Compiler:** GCC / G++ (C++17 standard)
* **Build System:** CMake
* **Library:** `behaviortree_cpp`

## 🚀 How to Build and Run

Follow these steps to compile and execute the behavior tree.

### 1. Prerequisite (If library is not installed)
If the Behavior Tree library is not yet installed on your system, install it via `apt` (or `vcpkg`):
```bash
sudo apt-get update
sudo apt-get install libbehaviortree-cpp-dev
````

### 2\. Build the Project

Navigate to the project root directory and run:

```bash
mkdir build
cd build
cmake ..
make
```

### 3\. Run the Executable

After a successful build, execute the robot simulation:

```bash
./robot_main
```

*(Note: If you encounter a shared library error, run `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib` before running the executable).*

## 📊 Expected Output

When running the code, you will see the following trace, confirming the robot handles the "Closed Door" scenarios correctly using Fallback nodes:

```text
--- Robot Task Started ---

[ ACTION ] Moving towards: Room Door
[ CHECK  ] Is Room Door open? -> NO (Closed)
[ ACTION ] Opening Room Door...
[ ACTION ] Entering the room.
[ ACTION ] Moving towards: Fridge
[ CHECK  ] Is Fridge Door open? -> NO (Closed)
[ ACTION ] Opening Fridge Door...
[ ACTION ] Apple found!
[ ACTION ] Picking the apple.
[ ACTION ] Closing Fridge Door.
[ ACTION ] Moving towards: Room Door
[ ACTION ] Exiting the room.

--- Robot Task Finished ---
```

## 🧠 Code Logic & Design

The Behavior Tree is constructed using two primary control flow nodes:

### 1\. The `Sequence` Node

The root of the tree is a **Sequence**. It ensures the robot performs the tasks in a strict linear order (Enter Room -\> Get Apple -\> Leave). If any step fails, the whole sequence stops (though in this simulation, actions always succeed).

### 2\. The `Fallback` (Selector) Node

The decision-making logic for the doors ("Is the door closed?") is handled using a **Fallback** node.

  * **Logic:** `Fallback( CheckCondition, TakeAction )`
  * **Execution:**
    1.  The robot first ticks `IsDoorOpen`.
    2.  If the door is **Closed**, this node returns `FAILURE`.
    3.  The Fallback node catches the failure and runs the next child: `OpenDoor`.
    4.  If the door was already **Open**, the first node would return `SUCCESS`, and `OpenDoor` would be skipped entirely.

### 3\. Modular Actions (Ports)

Instead of hardcoding separate classes for every location (e.g., `MoveToFridge`, `MoveToDoor`), I implemented a generic `MoveTo` class that accepts an **Input Port** (`target`). This makes the code cleaner and reusable for any future locations.
