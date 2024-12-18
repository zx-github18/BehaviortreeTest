#include "behaviortree_cpp/bt_factory.h"
#include "common/pose2d.h"
#include "action_node/move_base_node.hpp"
#include "action_node/say_something_node.hpp"

namespace chr = std::chrono;

BT::NodeStatus CheckBattery()
{
    std::cout << "[ Battery OK ]" << std::endl;
    return BT::NodeStatus::SUCCESS;
}

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

    factory.registerNodeType<SaySomething<std::string>>("SaySomething");
    factory.registerNodeType<MoveBase>("MoveBase");
    factory.registerSimpleCondition("BatteryOK", std::bind(CheckBattery));

    const std::string source_dir =
        "/home/zx/Projects/BehaviortreeTest/src/examples/";
    const std::string example_name = "t04_reactive_and_asynchronous_behaviors";
    const std::string xml_name = example_name + "_tree.xml";
    const std::string xml_path = source_dir + example_name + "/" + xml_name;
    BT::Tree tree = factory.createTreeFromFile(xml_path);

    std::cout << "--- ticking" << std::endl;
    BT::NodeStatus status = tree.tickOnce();
    std::cout << "--- status:" << BT::toStr(status) << std::endl << std::endl;

    while (BT::NodeStatus::RUNNING == status)
    {
        std::this_thread::sleep_for(chr::milliseconds(100));

        std::cout << "--- ticking" << std::endl;
        status = tree.tickOnce();
        std::cout << "--- status:" << BT::toStr(status) << std::endl
                  << std::endl;
    }

    return 0;
}