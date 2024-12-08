#include "action_node/move_base_node.hpp"
#include "action_node/say_something_node.hpp"
#include "action_node/action_command_node.hpp"
#include "behaviortree_cpp/bt_factory.h"

namespace BT {
template <> inline Pose2D convertFromString(StringView pose_str)
{
    std::vector<StringView> data = splitString(pose_str, ';');
    if (data.size() != 3)
    {
        throw RuntimeError("pose string error!");
    }
    else
    {
        Pose2D pose;
        pose.x = convertFromString<double>(data[0]);
        pose.y = convertFromString<double>(data[1]);
        pose.theta = convertFromString<double>(data[2]);
        return pose;
    }
}
}  // namespace BT

int main()
{
    BT::BehaviorTreeFactory factory;

    factory.registerNodeType<MoveBase>("MoveBase");
    factory.registerNodeType<SaySomething<int>>("SaySomething");
    factory.registerNodeType<ActionCommand>("ActionCommand", 10162, 99, 100);

    const std::string source_dir =
        "/home/zx/Projects/BehaviortreeTest/src/examples/";
    const std::string example_name = "t07_set_params_for_init";
    const std::string xml_name = example_name + "_tree.xml";
    const std::string xml_path = source_dir + example_name + "/" + xml_name;

    factory.registerBehaviorTreeFromFile(xml_path);

    auto tree = factory.createTree("MainTree");
    tree.tickWhileRunning();

    // let's visualize some information about the current state of the
    // blackboards.
    std::cout << "\n------ First BB ------" << std::endl;
    tree.subtrees[0]->blackboard->debugMessage();
    std::cout << "\n------ Second BB------" << std::endl;
    tree.subtrees[1]->blackboard->debugMessage();

    return 0;
}