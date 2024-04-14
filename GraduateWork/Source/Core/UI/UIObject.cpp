#include "UIObject.h"

#include "../../Game/Actors/Player/Player.h"
#include "../StaticFunctions/Debug.h"

UIObject::UIObject(Object* Owner, const Rectangle& Bounds, std::shared_ptr<UIObject>&& Parent,
                   Alignment HorizontalAlignment)
    : Owner(Owner), Bounds(Bounds), bIsVisible(true), HorizontalAlignment(HorizontalAlignment)
{
    AttachTo(Parent);
}

void UIObject::Awake()
{
    if (Parent && HorizontalAlignment == Alignment::None)
        Debug::GetInstance().LogError(TextFormat("Alignment must be set"));
}

void UIObject::AddToViewport()
{
    auto ContentHUD = static_cast<Player*>(GetOwner())->GetHUD();
    if (ContentHUD)
    {
        ContentHUD->AddToViewport(this);
    }
}

bool UIObject::AttachTo(std::shared_ptr<UIObject>& NewParent)
{
    if (!NewParent) return false;
    if (bIsAttached) return false;

    Parent = NewParent;
    return bIsAttached = true;
}

bool UIObject::Detach()
{
    if (!bIsAttached) return false;

    Parent = nullptr;
    bIsAttached = false;

    return true;
}

const Vector2& UIObject::GetRelativePosition() const
{
    switch (HorizontalAlignment)
    {
    case Alignment::None:   return Vector2{Bounds.x, Bounds.y};
    case Alignment::Left:   return Vector2{Bounds.x, Bounds.y};
    case Alignment::Center: return Vector2{Bounds.x + Bounds.width / 2.0f, Bounds.y};
    case Alignment::Right:  return Vector2{Bounds.x + Bounds.width, Bounds.y};
    default:                return Vector2{};
    }
}
