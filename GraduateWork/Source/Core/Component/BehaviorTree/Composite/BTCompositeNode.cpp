#include "BTCompositeNode.h"

BTCompositeNode::BTCompositeNode(std::shared_ptr<Blackboard> NodeBlackboard)
    : BTNode(NodeBlackboard)
{
}

void BTCompositeNode::RemoveChild(std::shared_ptr<BTNode>& Child)
{
    Children.erase(std::remove(Children.begin(), Children.end(), Child), Children.end());
}
