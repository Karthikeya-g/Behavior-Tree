#include <behaviortree_cpp_v3/bt_factory.h>
#include <behaviortree_cpp_v3/action_node.h>
#include <iostream>

using namespace BT;

// =========================================================
// 1. DUMMY ACTIONS (Rectangles in Flowchart)
// =========================================================

class MoveToRoomDoor : public SyncActionNode {
public:
    MoveToRoomDoor(const std::string& name, const NodeConfiguration& config) : SyncActionNode(name, config) {}
    NodeStatus tick() override {
        std::cout << "[ ACTION ] Moving towards the room door..." << std::endl;
        return NodeStatus::SUCCESS;
    }
};

class EnterRoom : public SyncActionNode {
public:
    EnterRoom(const std::string& name, const NodeConfiguration& config) : SyncActionNode(name, config) {}
    NodeStatus tick() override {
        std::cout << "[ ACTION ] Entering the room." << std::endl;
        return NodeStatus::SUCCESS;
    }
};

class MoveToFridge : public SyncActionNode {
public:
    MoveToFridge(const std::string& name, const NodeConfiguration& config) : SyncActionNode(name, config) {}
    NodeStatus tick() override {
        std::cout << "[ ACTION ] Moving towards the fridge." << std::endl;
        return NodeStatus::SUCCESS;
    }
};

class OpenDoor : public SyncActionNode {
public:
    OpenDoor(const std::string& name, const NodeConfiguration& config) : SyncActionNode(name, config) {}
    NodeStatus tick() override {
        std::cout << "[ ACTION ] Opening the door." << std::endl;
        return NodeStatus::SUCCESS;
    }
};

class FindApple : public SyncActionNode {
public:
    FindApple(const std::string& name, const NodeConfiguration& config) : SyncActionNode(name, config) {}
    NodeStatus tick() override {
        std::cout << "[ ACTION ] Finding the apple inside." << std::endl;
        return NodeStatus::SUCCESS;
    }
};

class PickApple : public SyncActionNode {
public:
    PickApple(const std::string& name, const NodeConfiguration& config) : SyncActionNode(name, config) {}
    NodeStatus tick() override {
        std::cout << "[ ACTION ] Picking the apple." << std::endl;
        return NodeStatus::SUCCESS;
    }
};

class CloseFridge : public SyncActionNode {
public:
    CloseFridge(const std::string& name, const NodeConfiguration& config) : SyncActionNode(name, config) {}
    NodeStatus tick() override {
        std::cout << "[ ACTION ] Closing the fridge door." << std::endl;
        return NodeStatus::SUCCESS;
    }
};

class MoveToExit : public SyncActionNode {
public:
    MoveToExit(const std::string& name, const NodeConfiguration& config) : SyncActionNode(name, config) {}
    NodeStatus tick() override {
        std::cout << "[ ACTION ] Moving to room exit." << std::endl;
        return NodeStatus::SUCCESS;
    }
};

class ExitRoom : public SyncActionNode {
public:
    ExitRoom(const std::string& name, const NodeConfiguration& config) : SyncActionNode(name, config) {}
    NodeStatus tick() override {
        std::cout << "[ ACTION ] Exiting the room. Task Complete." << std::endl;
        return NodeStatus::SUCCESS;
    }
};

// =========================================================
// 2. DUMMY CONDITIONS (Diamonds in Flowchart)
// =========================================================

class IsDoorOpen : public SyncActionNode {
public:
    IsDoorOpen(const std::string& name, const NodeConfiguration& config) : SyncActionNode(name, config) {}
    NodeStatus tick() override {
        // FLOWCHART LOGIC: "Is Door Closed? -> Yes -> Open Door"
        // BT LOGIC: "Is Door Open? -> No (Failure) -> Fallback triggers Open Door"
        std::cout << "[ CHECK  ] Is door open? -> NO (Door is closed)." << std::endl;
        return NodeStatus::FAILURE; 
    }
};

// =========================================================
// 3. MAIN EXECUTION
// =========================================================

int main() {
    BehaviorTreeFactory factory;

    // Register all nodes
    factory.registerNodeType<MoveToRoomDoor>("MoveToRoomDoor");
    factory.registerNodeType<IsDoorOpen>("IsDoorOpen");
    factory.registerNodeType<OpenDoor>("OpenDoor");
    factory.registerNodeType<EnterRoom>("EnterRoom");
    factory.registerNodeType<MoveToFridge>("MoveToFridge");
    factory.registerNodeType<FindApple>("FindApple");
    factory.registerNodeType<PickApple>("PickApple");
    factory.registerNodeType<CloseFridge>("CloseFridge");
    factory.registerNodeType<MoveToExit>("MoveToExit");
    factory.registerNodeType<ExitRoom>("ExitRoom");

    // XML Structure matching the flowchart
    auto tree_xml = R"(
     <root main_tree_to_execute = "MainTree">
         <BehaviorTree ID="MainTree">
            <Sequence name="Mission">
               
               <MoveToRoomDoor/>
               <Fallback name="EnsureRoomDoorOpen">
                   <IsDoorOpen/>
                   <OpenDoor/>
               </Fallback>
               <EnterRoom/>

               <MoveToFridge/>
               <Fallback name="EnsureFridgeOpen">
                   <IsDoorOpen/>
                   <OpenDoor/>
               </Fallback>
               <FindApple/>
               <PickApple/>
               <CloseFridge/>

               <MoveToExit/>
               <ExitRoom/>

            </Sequence>
         </BehaviorTree>
     </root>
    )";

    auto tree = factory.createTreeFromText(tree_xml);

    std::cout << "--- STARTING BEHAVIOR TREE ---" << std::endl;
    tree.tickRoot();
    std::cout << "--- FINISHED ---" << std::endl;

    return 0;
}
