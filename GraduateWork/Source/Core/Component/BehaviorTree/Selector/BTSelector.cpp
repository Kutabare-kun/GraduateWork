#include "BTSelector.h"

BTSelector::BTSelector(std::shared_ptr<Blackboard> NodeBlackboard)
    : BTCompositeNode(NodeBlackboard)
{
}

bool BTSelector::Run()
{
    for (const auto& Child : GetChildren())
    {
        if (!Child->Run()) continue;
        return true;
    }

    return false;
}
