#include "UIBase.h"

#include <raymath.h>

UIBase::UIBase(Object* Owner, const Slot& LayoutSlot, UIBase* Parent)
    : Owner(Owner), Parent(Parent), LayoutSlot(LayoutSlot), BaseResolution(Window::GetInstance().GetScreenSize())
{
}

void UIBase::Awake()
{
    for (auto& Child : Children)
    {
        Child->Awake();
    }
}

void UIBase::Update(float DeltaTime)
{
    for (auto& Child : Children)
    {
        Child->Update(DeltaTime);
    }
}

void UIBase::Draw()
{
    if (IsVisible())
    {
        for (auto& Child : Children)
        {
            Child->Draw();
        }
    }
}

void UIBase::AddChild(std::shared_ptr<UIBase>& Child)
{
    Children.push_back(Child);
    Child->AttachToParent(this);
}

bool UIBase::AttachToParent(UIBase* Parent)
{
    if (Parent) return false;

    this->Parent = Parent;
    return true;
}

bool UIBase::DetachFromParent()
{
    if (!Parent) return false;

    this->Parent = nullptr;
    return true;
}

Rectangle UIBase::GetBounds() const
{
    const Vector2& Scale = GetScaleWindow();

    return {
        LayoutSlot.SlotRect.x * Scale.x, LayoutSlot.SlotRect.y * Scale.y,
        LayoutSlot.SlotRect.width * Scale.x, LayoutSlot.SlotRect.height * Scale.y
    };
}

Object* UIBase::GetOwner() const
{
    return Owner;
}

UIBase* UIBase::GetParent() const
{
    return Parent;
}

Vector2 UIBase::GetScaleWindow(const Vector2& WindowResolution) const
{
    return Vector2Divide(WindowResolution, BaseResolution);
}
