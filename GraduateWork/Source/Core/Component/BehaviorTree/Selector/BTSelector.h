#pragma once
#include "../Composite/BTCompositeNode.h"

class BTSelector
    : public BTCompositeNode
{
public:
    bool Run() override;
};
