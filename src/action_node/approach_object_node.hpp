#ifndef APPROACH_OBJECT_NODE_HPP
#define APPROACH_OBJECT_NODE_HPP

#include "behaviortree_cpp/action_node.h"

// Example of custom SyncActionNode (synchronous action)
// without ports.
class ApproachObject : public BT::SyncActionNode {
  public:
    ApproachObject(const std::string &name) : BT::SyncActionNode(name, {}) {}

    // You must override the virtual function tick()
    BT::NodeStatus tick() override
    {
        std::cout << "ApproachObject: " << this->name() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
};
#endif