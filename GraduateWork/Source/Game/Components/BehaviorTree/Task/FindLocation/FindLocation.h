#pragma once
#include "../../../../../Core/Component/BehaviorTree/Node/BTNode.h"

class FindLocation
    : public BTNode
{
public:
    FindLocation(std::shared_ptr<Blackboard> NodeBlackboard);

    bool Run() override;
};
