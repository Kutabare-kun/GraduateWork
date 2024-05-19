#include "BehaviorTree.h"

#include "Sequence/BTSequence.h"

BehaviorTree::BehaviorTree(Object* Owner)
    : ActorComponent(Owner)
{
}

void BehaviorTree::Awake()
{
    Root = std::make_shared<BTSequence>(GetBlackboard());

    ActorComponent::Awake();
}

void BehaviorTree::Update(float DeltaTime)
{
    ActorComponent::Update(DeltaTime);

    if (!Blackboard) return;
    Blackboard->UpdateDeltaTime(DeltaTime);

    if (!Root) return;
    Root->Run();
}
