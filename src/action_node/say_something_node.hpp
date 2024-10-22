#ifndef SAY_SOMETHING_NODE_HPP
#define SAY_SOMETHING_NODE_HPP

#include "behaviortree_cpp/action_node.h"

class SaySomething : public BT::SyncActionNode {
  public:
    SaySomething(const std::string &name, const BT::NodeConfig &config)
        : BT::SyncActionNode(name, config)
    {
        // to do nothing
    }

    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<std::string>("message")};
    }

    BT::NodeStatus tick() override
    {
        BT::Expected<std::string> msg =
            BT::TreeNode::getInput<std::string>("message");
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