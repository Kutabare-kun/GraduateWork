#include "BehaviorTree.h"

BehaviorTree::BehaviorTree(Object* Owner)
    : ActorComponent(Owner)
{
}

void BehaviorTree::Update(float DeltaTime)
{
    ActorComponent::Update(DeltaTime);

    if (!Root) return;
    Root->Run();
}
