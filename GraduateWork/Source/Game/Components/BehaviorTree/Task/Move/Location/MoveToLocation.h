#pragma once
#include "../../../../../../Core/Component/BehaviorTree/Node/BTNode.h"

class MoveToLocation
    : public BTNode
{
public:
    MoveToLocation(std::shared_ptr<Blackboard> NodeBlackboard);

    bool Run() override;
};
