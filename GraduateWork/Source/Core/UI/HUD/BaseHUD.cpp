#include "BaseHUD.h"

BaseHUD::BaseHUD(Object* Owner)
    : ActorComponent(Owner)
{
    SetDrawLayer(DrawLayer::UI);
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

void BaseHUD::Draw(const Camera2D& OwnerCamera)
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

void BaseHUD::AddUIElement(std::shared_ptr<UIBase> Element)
{
    UIElements.push_back(Element);
}
