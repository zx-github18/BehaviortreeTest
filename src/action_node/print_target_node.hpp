#pragma once
#include "behaviortree_cpp/action_node.h"
#include "common/Position2D.h"

class PrintTarget : public BT::SyncActionNode{
    public:
        PrintTarget(const std::string &name, const BT::NodeConfig &config)
        : SyncActionNode(name,config){
            //to do nothing
        }

        static BT::PortsList providedPorts(){
            const char*  description = "Simply print the goal on console...";
            return {BT::InputPort<Position2D>("target",description)};
        }

        BT::NodeStatus tick() override{
            BT::Expected<Position2D> res = getInput<Position2D>("target");
            if(!res){
                throw BT::RuntimeError("missing required input [target]: ", 
                              res.error() );
            }
            Position2D target = res.value();
            std::cout << "target: "<< target.x << " " << target.y<< std::endl;
            return BT::NodeStatus::SUCCESS;
        }
};