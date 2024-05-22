#include "BaseHUD.h"

BaseHUD::BaseHUD(Object* Owner)
    : ActorComponent(Owner)
{
    SetDrawLayer(DrawLayer::UI);
}

void BaseHUD::Awake()
{
    ActorComponent::Awake();
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

void BaseHUD::ProcessNewElements()
{
    if (NewUIElements.empty()) return;

    for (const auto& Element : NewUIElements)
    {
        Element->Awake();
        UIElements.push_back(Element);
    }

    NewUIElements.clear();
}

void BaseHUD::ProcessRemovals()
{
    auto Iter = UIElements.begin();
    while (Iter != UIElements.end())
    {
        if (auto UIObject = *Iter->get(); UIObject.IsQueuedForRemoval())
        {
            Iter = UIElements.erase(Iter);
        }
        else
        {
            ++Iter;
        }
    }
}

void BaseHUD::Add(std::shared_ptr<UIBase> Element)
{
    NewUIElements.push_back(Element);
}
