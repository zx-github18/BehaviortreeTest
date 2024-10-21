#include "behaviortree_cpp/action_node.h"

class ThinkWhatToSay : public BT::SyncActionNode{
    public:
        ThinkWhatToSay(const std::string &name, const BT::NodeConfig &config)
        : BT::SyncActionNode(name, config) {
            // to do nothing
        }

        static BT::PortsList providedPorts(){
            return {BT::OutputPort<std::string>("message")};
        }

        BT::NodeStatus tick() override {
            const char str[] = "anwser is 42";
            BT::TreeNode::setOutput("message", str);
            return BT::NodeStatus::SUCCESS;
        }
};