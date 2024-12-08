
#include "behaviortree_cpp/action_node.h"
#include "common/position2d.h"

class ActionCommand : public BT::SyncActionNode {
  public:
    ActionCommand(const std::string &name,
                  const BT::NodeConfig &config,
                  const int action_id,
                  const int param0,
                  const int param1,
                  const int param2 = 0)
        : SyncActionNode(name, config), action_id_(action_id), param0_(param0),
          param1_(param1), param2_(param2)
    {
        // to do nothing
    }

    static BT::PortsList providedPorts()
    {
        return {BT::OutputPort<int>("action_id"),
                BT::OutputPort<int>("param0"),
                BT::OutputPort<int>("param1"),
                BT::OutputPort<int>("param2")};
    }

    BT::NodeStatus tick() override
    {
        setOutput<int>("action_id", action_id_);
        setOutput<int>("param0", param0_);
        setOutput<int>("param1", param1_);
        setOutput<int>("param2", param2_);

        std::cout << "action cmd id: " << action_id_
                  << "  p0: " << param0_ << "  p1: " << param1_
                  << "  p2: " << param2_ << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

  private:
    int action_id_;
    int param0_;
    int param1_;
    int param2_;
};
