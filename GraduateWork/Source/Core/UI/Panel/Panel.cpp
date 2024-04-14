#include "Panel.h"

Panel::Panel(Object* Owner, const Rectangle& Bounds, std::shared_ptr<UIObject>&& Parent, Alignment HorizontalAlignment)
    : UIObject(Owner, Bounds, std::move(Parent), HorizontalAlignment)
{
}

void Panel::Awake()
{
    UIObject::Awake();

    for (auto& Element : Children)
    {
        Element->Awake();
    }
}

void Panel::Update(float DeltaTime)
{
    for (auto& Element : Children)
    {
        Element->Update(DeltaTime);
    }
}

void Panel::Draw()
{
    for (auto& Element : Children)
    {
        Element->Draw();
    }
}

void Panel::AddChild(std::shared_ptr<UIObject>& Child)
{
    Children.push_back(Child);
}

void Panel::RemoveChild(std::shared_ptr<UIObject>& Child)
{
    Children.erase(std::remove(Children.begin(), Children.end(), Child), Children.end());
}
