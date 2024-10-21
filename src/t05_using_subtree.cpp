#include "behaviortree_cpp/bt_factory.h"


class CrossDoor
{
public:
    void registerNodes(BT::BehaviorTreeFactory& factory);

    // SUCCESS if _door_open != true
    BT::NodeStatus isDoorClosed(){
        if (_door_open){
            std::cout << "door is opened" << std::endl;
            return BT::NodeStatus::FAILURE;
        } else {
            _door_open = false;
            std::cout << "door is close" << std::endl;
            return BT::NodeStatus::SUCCESS;
        }
    }

    // SUCCESS if _door_open == true
    BT::NodeStatus passThroughDoor(){
        if (_door_open) {
            std::cout << "pass through the door" << std::endl;
            return BT::NodeStatus::SUCCESS;
        } else {
            std::cout << "door closed! pass failure." << std::endl;
            return BT::NodeStatus::FAILURE;
        }
    }

    // After 3 attempts, will open a locked door
    BT::NodeStatus pickLock() {
        ++_pick_attempts;
        std::cout << "attempt open door " << _pick_attempts << " times...";
        if(_pick_attempts >= 3){
            std::cout << "[OK]" << std::endl;
            _door_open = true;
            return BT::NodeStatus::SUCCESS;
        } else {
            std::cout << "[Fail]" << std::endl;
            return BT::NodeStatus::FAILURE;
        }
    }

    // FAILURE if door locked
    BT::NodeStatus openDoor(){
        if (_door_locked){
            std::cout << "the door is locked!" << std::endl;
            return BT::NodeStatus::FAILURE;
        } else {
            _door_open = true;
            std::cout << "open the door" << std::endl;
            return BT::NodeStatus::SUCCESS;
        }
    }

    // WILL always open a door
    BT::NodeStatus smashDoor(){
        _door_open = true;
        std::cout << "open the door" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

private:
    bool _door_open   = false;
    bool _door_locked = true;
    int _pick_attempts = 0;
};

// Helper method to make registering less painful for the user
void CrossDoor::registerNodes(BT::BehaviorTreeFactory &factory)
{
  factory.registerSimpleCondition(
      "IsDoorClosed", std::bind(&CrossDoor::isDoorClosed, this));

  factory.registerSimpleAction(
      "PassThroughDoor", std::bind(&CrossDoor::passThroughDoor, this));

  factory.registerSimpleAction(
      "OpenDoor", std::bind(&CrossDoor::openDoor, this));

  factory.registerSimpleAction(
      "PickLock", std::bind(&CrossDoor::pickLock, this));

  factory.registerSimpleCondition(
      "SmashDoor", std::bind(&CrossDoor::smashDoor, this));
}

int main()
{
  BT::BehaviorTreeFactory factory;

  CrossDoor cross_door;
  cross_door.registerNodes(factory);

  // In this example a single XML contains multiple <BehaviorTree>
  // To determine which one is the "main one", we should first register
  // the XML and then allocate a specific tree, using its ID
  const std::string xml_dir = "/home/zx/Projects/behaviortree/xml/";
  const std::string xml_name = "t05_using_subtree_tree.xml";
  const std::string xml_path = xml_dir + xml_name;
  factory.registerBehaviorTreeFromFile(xml_path);
  auto tree = factory.createTree("MainTree");

  // helper function to print the tree
  printTreeRecursively(tree.rootNode());

  tree.tickWhileRunning();

  return 0;
}
