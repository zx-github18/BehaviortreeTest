#include "behaviortree_cpp/bt_factory.h"
#include "action_node/say_something_node.hpp"
#include "action_node/think_what_to_say_node.hpp"

int main()
{
    BT::BehaviorTreeFactory factory;

    factory.registerNodeType<SaySomething>("SaySomething");
    factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

    const std::string xml_dir  = "/home/zx/Projects/behaviortree/xml/";
    const std::string xml_name = "t02_blackboard_and_ports_tree.xml";
    const std::string xml_path = xml_dir + xml_name;
    auto              tree     = factory.createTreeFromFile(xml_path);

    tree.tickWhileRunning();
    return 0;
}