#include "BTSequence.h"

BTSequence::BTSequence(std::shared_ptr<Blackboard> NodeBlackboard)
    : BTCompositeNode(NodeBlackboard)
{
}

bool BTSequence::Run()
{
    for (const auto& Child : GetChildren())
    {
        if (Child->Run()) continue;
        return false;
    }

    return true;
}
