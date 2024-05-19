#pragma once
#include "../Composite/BTCompositeNode.h"

class BTSelector final
    : public BTCompositeNode
{
public:
    BTSelector(std::shared_ptr<Blackboard> NodeBlackboard);

    bool Run() override;
};
