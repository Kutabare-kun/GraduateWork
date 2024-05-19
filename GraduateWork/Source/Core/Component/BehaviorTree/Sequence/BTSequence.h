#pragma once
#include "../Composite/BTCompositeNode.h"

class BTSequence final
    : public BTCompositeNode
{
public:
    BTSequence(std::shared_ptr<Blackboard> NodeBlackboard);

    bool Run() override;
};
