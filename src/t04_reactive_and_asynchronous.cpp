#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/behavior_tree.h"
#include <thread>

struct Pose2D{
    double x;
    double y;
    double theta;
};

namespace chr = std::chrono;

BT::NodeStatus CheckBattery(){
    std::cout << "[ Battery OK ]" << std::endl;
    return BT::NodeStatus::SUCCESS;
}

class SaySomething : public BT::SyncActionNode{
public:
    SaySomething(const std::string &name, const BT::NodeConfig &config)
        : BT::SyncActionNode(name, config){
            // to do nothing
        }

    static BT::PortsList providedPorts(){
        return {BT::InputPort<std::string>("message")};
    }

    BT::NodeStatus tick() override {
        BT::Expected<std::string> msg = BT::TreeNode::getInput<std::string>("message");
        if(!msg){
            throw BT::RuntimeError("missing required input [message]", msg.error());
        }
        std::cout << "Robot says: " << msg.value() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
};

class MoveBase : public BT::StatefulActionNode{
public:
    MoveBase(const std::string &name, const BT::NodeConfig &config) : BT::StatefulActionNode(name, config)
    {
        // to do nothing
    }

    static BT::PortsList providedPorts(){
        return { BT::InputPort<Pose2D>("goal") };
    }

    /// Method called once, when transitioning from the state IDLE.
    /// If it returns RUNNING, this becomes an asynchronous node.
    virtual BT::NodeStatus onStart() override;

    /// method invoked when the action is already in the RUNNING state.
    virtual BT::NodeStatus onRunning() override;

    /// when the method halt() is called and the action is RUNNING, this method is invoked.
    /// This is a convenient place todo a cleanup, if needed.
    virtual void onHalted() override;

private:
    Pose2D _goal;
    std::chrono::system_clock::time_point _complete_time_;
};

namespace BT{
template <> inline Pose2D convertFromString(StringView pose_str){
 
    std::vector<StringView> data = splitString(pose_str, ';');

    if (data.size()!= 3){
        throw RuntimeError("pose string error!");
    }else{
        Pose2D pose;
        pose.x = convertFromString<double>(data[0]);
        pose.y = convertFromString<double>(data[1]);
        pose.theta = convertFromString<double>(data[2]);
        return pose;
    }
}
}

BT::NodeStatus MoveBase::onStart(){
    if(!BT::TreeNode::getInput<Pose2D>("goal", _goal)){
        throw BT::RuntimeError("missing goal");
    } else {
        std::cout << "[ MoveBase: SEND REQUEST ]. goal: x=" << _goal.x << " y=" << _goal.y << " theta=" << _goal.theta << std::endl;
        _complete_time_ = chr::system_clock::now()+ chr::milliseconds(220);
        return BT::NodeStatus::RUNNING;
    }
}

BT::NodeStatus MoveBase::onRunning(){

    std::this_thread::sleep_for(chr::milliseconds(10));

    if (chr::system_clock::now() > _complete_time_){
        std::cout << "move base complete!" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
    return BT::NodeStatus::RUNNING;
}

void MoveBase::onHalted(){
    std::cout << "MoveBase abort!" << std::endl;
}

int main()
{
    BT::BehaviorTreeFactory factory;

    factory.registerNodeType<SaySomething>("SaySomething");
    factory.registerNodeType<MoveBase>("MoveBase");
    factory.registerSimpleCondition("BatteryOK", std::bind(CheckBattery));

    const std::string xml_dir = "/home/zx/Projects/behaviortree/xml/";
    const std::string xml_name = "t04_reactive_and_asynchronous_tree.xml";
    const std::string xml_path = xml_dir + xml_name;
    // std::cout << xml_path << std::endl;
    BT::Tree tree = factory.createTreeFromFile(xml_path);

    std::cout << "--- ticking" << std::endl;
    BT::NodeStatus status = tree.tickOnce();
    std::cout << "--- status:" << BT::toStr(status) << std::endl
              << std::endl;

    while (BT::NodeStatus::RUNNING == status )
    {
        std::this_thread::sleep_for(chr::milliseconds(100));

        std::cout << "--- ticking" << std::endl;
        status = tree.tickOnce();
        std::cout << "--- status:" << BT::toStr(status) << std::endl
              << std::endl;
    }
    
    return 0;
}