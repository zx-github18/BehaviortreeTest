#ifndef SAY_SOMETHING_NODE_HPP
#define SAY_SOMETHING_NODE_HPP

#include "behaviortree_cpp/action_node.h"
template<class T>
class SaySomething : public BT::SyncActionNode {
  public:
    SaySomething(const std::string &name, const BT::NodeConfig &config)
        : BT::SyncActionNode(name, config)
    {
        // to do nothing
    }

    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<T>("message")};
    }

    BT::NodeStatus tick() override
    {
        BT::Expected<T> msg =
            BT::TreeNode::getInput<T>("message");
        if (!msg)
        {
            throw BT::RuntimeError("missing required input [message]: ",
                                   msg.error());
        }
        std::cout << "Robot says: " << msg.value() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
};

#endif  // SAY_SOMETHING_NODE_HPP