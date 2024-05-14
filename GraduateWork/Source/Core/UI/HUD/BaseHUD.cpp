#include "BaseHUD.h"

BaseHUD::BaseHUD(Object* Owner)
    : ActorComponent(Owner)
{
    
}

void BaseHUD::Awake()
{
    ActorComponent::Awake();

    for (auto& Element : UIElements)
    {
        Element->Awake();
    }
}

void BaseHUD::LateUpdate(float DeltaTime)
{
    ActorComponent::LateUpdate(DeltaTime);

    for (auto& Element : UIElements)
    {
        Element->Update(DeltaTime);
    }
}

void BaseHUD::Draw()
{
    for (auto& Element : UIElements)
    {
        Element->Draw();
    }
}

bool BaseHUD::ContinueToDraw() const
{
    return !GetOwner()->IsQueuedForRemoval();
}
