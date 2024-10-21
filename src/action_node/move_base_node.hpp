#pragma once
#include "behaviortree_cpp/action_node.h"
#include "common/Pose2D.h"

namespace chr = std::chrono;

class MoveBase : public BT::StatefulActionNode {
  public:
    MoveBase(const std::string &name, const BT::NodeConfig &config)
        : BT::StatefulActionNode(name, config)
    {
        // to do nothing
    }

    static BT::PortsList providedPorts()
    {
        return {BT::InputPort<Pose2D>("goal")};
    }

    /// Method called once, when transitioning from the state IDLE.
    /// If it returns RUNNING, this becomes an asynchronous node.
    virtual BT::NodeStatus onStart() override;

    /// method invoked when the action is already in the RUNNING state.
    virtual BT::NodeStatus onRunning() override;

    /// when the method halt() is called and the action is RUNNING, this method
    /// is invoked. This is a convenient place todo a cleanup, if needed.
    virtual void onHalted() override;

  private:
    Pose2D                                _goal;
    std::chrono::system_clock::time_point _complete_time_;
};

BT::NodeStatus MoveBase::onStart()
{
    if (!BT::TreeNode::getInput<Pose2D>("goal", _goal))
    {
        throw BT::RuntimeError("missing goal");
    }
    else
    {
        std::cout << "[ MoveBase: SEND REQUEST ]. goal: x=" << _goal.x
                  << " y=" << _goal.y << " theta=" << _goal.theta << std::endl;
        _complete_time_ =
            std::chrono::system_clock::now() + std::chrono::milliseconds(220);
        return BT::NodeStatus::RUNNING;
    }
}

BT::NodeStatus MoveBase::onRunning()
{

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    if (std::chrono::system_clock::now() > _complete_time_)
    {
        std::cout << "move base complete!" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
    return BT::NodeStatus::RUNNING;
}

void MoveBase::onHalted() { std::cout << "MoveBase abort!" << std::endl; }
