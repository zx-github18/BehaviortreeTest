#include "behaviortree_cpp/bt_factory.h"
#include "action_node/say_something_node.hpp"
#include "action_node/think_what_to_say_node.hpp"

int main()
{
    BT::BehaviorTreeFactory factory;

    factory.registerNodeType<SaySomething>("SaySomething");
    factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

    const std::string source_dir =
        "/home/zx/Projects/BehaviortreeTest/src/examples/";
    const std::string example_name = "t02_blackboard_and_ports";
    const std::string xml_name = example_name + "_tree.xml";
    const std::string xml_path = source_dir + example_name + "/" + xml_name;
    auto tree = factory.createTreeFromFile(xml_path);

    tree.tickWhileRunning();
    return 0;
}