#pragma once
#include "behaviortree_cpp/action_node.h"
#include "common/Position2D.h"

class CalculateGoal : public BT::SyncActionNode{
    public:
        CalculateGoal(const std::string &name, const BT::NodeConfig &config)
        : SyncActionNode(name,config){
            //to do nothing
        }

        static BT::PortsList providedPorts(){
            return {BT::OutputPort<Position2D>("goal")};
        }

        BT::NodeStatus tick() override{
            Position2D mygoal={1.1,2.3};
            setOutput<Position2D>("goal", mygoal);
            return BT::NodeStatus::SUCCESS;
        }
};