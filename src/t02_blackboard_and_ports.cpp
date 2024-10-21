#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/bt_factory.h"

class SaySomething : public BT::SyncActionNode
{
    public:
      SaySomething(const std::string &name, const BT::NodeConfig &config)
      :BT::SyncActionNode(name, config){
        // to do nothing
      }

      static BT::PortsList providedPorts(){
        return {BT::InputPort<std::string>("message")};
      }

      BT::NodeStatus tick() override {
        BT::Expected<std::string> msg = BT::TreeNode::getInput<std::string>("message");
        if (!msg){
            throw BT::RuntimeError("missing required input [message]: ", msg.error());
        }
        std::cout << "Robot says: " << msg.value() << std::endl;
        return BT::NodeStatus::SUCCESS;
      }
};

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

int main(){
    BT::BehaviorTreeFactory factory;

    factory.registerNodeType<SaySomething>("SaySomething");
    factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

    const std::string xml_dir = "/home/zx/Projects/behaviortree/xml/";
    const std::string xml_name = "t02_blackboard_and_ports_tree.xml";
    const std::string xml_path = xml_dir + xml_name;
    auto tree = factory.createTreeFromFile(xml_path);

    tree.tickWhileRunning();
    return 0;
}