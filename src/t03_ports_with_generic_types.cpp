#include "behaviortree_cpp/bt_factory.h"
#include "action_node/calculate_goal_node.hpp"
#include "action_node/print_target_node.hpp"

namespace BT {
template <> inline Position2D convertFromString(StringView str)
{
    auto parts = splitString(str, ';');
    if (parts.size() != 2)
    {
        throw RuntimeError("invalid input)");
    }
    else
    {
        Position2D output;
        output.x = convertFromString<double>(parts[0]);
        output.y = convertFromString<double>(parts[1]);
        return output;
    }
}
}  // namespace BT

int main()
{
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<CalculateGoal>("CalculateGoal");
    factory.registerNodeType<PrintTarget>("PrintTarget");

    std::string xml_path_dir = "/home/zx/Projects/behaviortree/xml/";
    std::string xml_name = "t03_ports_with_generic_types_tree.xml";
    std::string xml_path = xml_path_dir + xml_name;
    BT::Tree tree = factory.createTreeFromFile(xml_path);
    tree.tickWhileRunning();
    return 0;
}