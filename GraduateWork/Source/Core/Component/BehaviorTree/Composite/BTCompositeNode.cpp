#include "BTCompositeNode.h"

void BTCompositeNode::RemoveChild(std::unique_ptr<BTNode>& Child)
{
    Children.erase(std::remove(Children.begin(), Children.end(), Child), Children.end());
}
