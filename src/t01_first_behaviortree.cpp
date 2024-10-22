#include "behaviortree_cpp/bt_factory.h"
#include "action_node/approach_object_node.hpp"

using namespace BT;

// Simple function that return a NodeStatus
BT::NodeStatus CheckBattery()
{
    std::cout << "[ Battery: OK ]" << std::endl;
    return BT::NodeStatus::SUCCESS;
}

// We want to wrap into an ActionNode the methods open() and close()
class GripperInterface {
  public:
    GripperInterface() : _open(true) {}

    NodeStatus open()
    {
        _open = true;
        std::cout << "GripperInterface::open" << std::endl;
        return NodeStatus::SUCCESS;
    }

    NodeStatus close()
    {
        std::cout << "GripperInterface::close" << std::endl;
        _open = false;
        return NodeStatus::SUCCESS;
    }

  private:
    bool _open;  // shared information
};

int main()
{
    // We use the BehaviorTreeFactory to register our custom nodes
    BehaviorTreeFactory factory;

    // The recommended way to create a Node is through inheritance.
    factory.registerNodeType<ApproachObject>("ApproachObject");

    // Registering a SimpleActionNode using a function pointer.
    // You can use C++11 lambdas or std::bind
    factory.registerSimpleCondition("CheckBattery",
                                    [&](TreeNode &) { return CheckBattery(); });

    // You can also create SimpleActionNodes using methods of a class
    GripperInterface gripper;
    factory.registerSimpleAction("OpenGripper",
                                 [&](TreeNode &) { return gripper.open(); });
    factory.registerSimpleAction("CloseGripper",
                                 [&](TreeNode &) { return gripper.close(); });

    // Trees are created at deployment-time (i.e. at run-time, but only
    // once at the beginning).

    // IMPORTANT: when the object "tree" goes out of scope, all the
    // TreeNodes are destroyed
    const std::string xml_dir = "/home/zx/Projects/behaviortree/xml/";
    const std::string xml_name = "t01_first_behaviortree_tree.xml";
    const std::string xml_path = xml_dir + xml_name;
    auto tree = factory.createTreeFromFile(xml_path);

    // To "execute" a Tree you need to "tick" it.
    // The tick is propagated to the children based on the logic of the tree.
    // In this case, the entire sequence is executed, because all the children
    // of the Sequence return SUCCESS.
    tree.tickWhileRunning();

    return 0;
}

/* Expected output:
*
  [ Battery: OK ]
  GripperInterface::open
  ApproachObject: approach_object
  GripperInterface::close
*/
