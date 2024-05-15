#pragma once
#include "../Composite/BTCompositeNode.h"

class BTSequence
    : public BTCompositeNode
{
public:
    bool Run() override;
};
