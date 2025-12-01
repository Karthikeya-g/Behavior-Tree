#include <iostream>
#include <string>
#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/bt_factory.h"

using namespace BT;

// ======================================================
// 1. DEFINE CUSTOM NODES
// ======================================================

// Action: Move to a specific location
class MoveTo : public SyncActionNode
{
public:
    MoveTo(const std::string& name, const NodeConfig& config)
        : SyncActionNode(name, config) {}

    static PortsList providedPorts() {
        return { InputPort<std::string>("target") };
    }

    NodeStatus tick() override
    {
        std::string target;
        if (!getInput("target", target)) {
            throw RuntimeError("Missing parameter [target]");
        }
        std::cout << "[ ACTION ] Moving towards: " << target << std::endl;
        return NodeStatus::SUCCESS;
    }
};

// Condition: Checks if a door is open
// We simulate that doors are initially CLOSED (Failure) to force the robot to open them.
class IsDoorOpen : public SyncActionNode
{
public:
    IsDoorOpen(const std::string& name, const NodeConfig& config)
        : SyncActionNode(name, config) {}

    static PortsList providedPorts() {
        return { InputPort<std::string>("door_name") };
    }

    NodeStatus tick() override
    {
        std::string door_name;
        getInput("door_name", door_name);
        
        // SIMULATION LOGIC:
        // We return FAILURE to simulate that the door is CLOSED.
        // This forces the Behavior Tree to execute the "OpenDoor" action defined in the Fallback.
        std::cout << "[ CHECK  ] Is " << door_name << " open? -> NO (Closed)" << std::endl;
        return NodeStatus::FAILURE; 
    }
};

// Action: Open a door
class OpenDoor : public SyncActionNode
{
public:
    OpenDoor(const std::string& name, const NodeConfig& config)
        : SyncActionNode(name, config) {}

    static PortsList providedPorts() {
        return { InputPort<std::string>("door_name") };
    }

    NodeStatus tick() override
    {
        std::string door_name;
        getInput("door_name", door_name);
        std::cout << "[ ACTION ] Opening " << door_name << "..." << std::endl;
        return NodeStatus::SUCCESS;
    }
};

// Action: Close a door
class CloseDoor : public SyncActionNode
{
public:
    CloseDoor(const std::string& name, const NodeConfig& config)
        : SyncActionNode(name, config) {}

    static PortsList providedPorts() {
        return { InputPort<std::string>("door_name") };
    }

    NodeStatus tick() override
    {
        std::string door_name;
        getInput("door_name", door_name);
        std::cout << "[ ACTION ] Closing " << door_name << "." << std::endl;
        return NodeStatus::SUCCESS;
    }
};

// Simple Actions without parameters
class EnterRoom : public SyncActionNode
{
public:
    EnterRoom(const std::string& name, const NodeConfig& config) : SyncActionNode(name, config) {}
    static PortsList providedPorts() { return {}; }
    NodeStatus tick() override { 
        std::cout << "[ ACTION ] Entering the room." << std::endl; 
        return NodeStatus::SUCCESS; 
    }
};

class FindApple : public SyncActionNode
{
public:
    FindApple(const std::string& name, const NodeConfig& config) : SyncActionNode(name, config) {}
    static PortsList providedPorts() { return {}; }
    NodeStatus tick() override { 
        std::cout << "[ ACTION ] Apple found!" << std::endl; 
        return NodeStatus::SUCCESS; 
    }
};

class PickApple : public SyncActionNode
{
public:
    PickApple(const std::string& name, const NodeConfig& config) : SyncActionNode(name, config) {}
    static PortsList providedPorts() { return {}; }
    NodeStatus tick() override { 
        std::cout << "[ ACTION ] Picking the apple." << std::endl; 
        return NodeStatus::SUCCESS; 
    }
};

class ExitRoom : public SyncActionNode
{
public:
    ExitRoom(const std::string& name, const NodeConfig& config) : SyncActionNode(name, config) {}
    static PortsList providedPorts() { return {}; }
    NodeStatus tick() override { 
        std::cout << "[ ACTION ] Exiting the room." << std::endl; 
        return NodeStatus::SUCCESS; 
    }
};

// ======================================================
// 2. MAIN FUNCTION & XML TREE
// ======================================================
int main()
{
    BehaviorTreeFactory factory;

    // Register Nodes
    factory.registerNodeType<MoveTo>("MoveTo");
    factory.registerNodeType<IsDoorOpen>("IsDoorOpen");
    factory.registerNodeType<OpenDoor>("OpenDoor");
    factory.registerNodeType<CloseDoor>("CloseDoor");
    factory.registerNodeType<EnterRoom>("EnterRoom");
    factory.registerNodeType<FindApple>("FindApple");
    factory.registerNodeType<PickApple>("PickApple");
    factory.registerNodeType<ExitRoom>("ExitRoom");

    // XML Structure matching the Flow Diagram
    // "Fallback" (or Selector) is used for the door logic. 
    // It tries the first child (IsDoorOpen?). If that fails (Closed), it runs the second child (OpenDoor).
    auto tree = factory.createTreeFromText(R"(
     <root main_tree_to_execute = "MainTree" >
         <BehaviorTree ID="MainTree">
            <Sequence>
                
                <MoveTo target="Room Door"/>
                
                <Fallback>
                    <IsDoorOpen door_name="Room Door"/>
                    <OpenDoor   door_name="Room Door"/>
                </Fallback>
                
                <EnterRoom/>

                <MoveTo target="Fridge"/>
                
                <Fallback>
                    <IsDoorOpen door_name="Fridge Door"/>
                    <OpenDoor   door_name="Fridge Door"/>
                </Fallback>

                <FindApple/>
                <PickApple/>
                <CloseDoor door_name="Fridge Door"/>

                <MoveTo target="Room Door"/>
                <ExitRoom/>

            </Sequence>
         </BehaviorTree>
     </root>
    )");

    std::cout << "\n--- Robot Task Started ---\n" << std::endl;
    tree.tickWhileRunning();
    std::cout << "\n--- Robot Task Finished ---\n" << std::endl;

    return 0;
}
