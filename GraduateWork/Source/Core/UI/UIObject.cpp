#include "UIObject.h"

#include "../../Game/Actors/Player/Player.h"
#include "../StaticFunctions/Debug.h"
#include "../Window/Window.h"

UIObject::UIObject(Object* Owner, const Rectangle& Bounds, UIObject* Parent,
                   Alignment HorizontalAlignment)
    : Owner(Owner), Bounds(Bounds), bIsAttached(false), bIsVisible(true), ObjectAlignment(HorizontalAlignment), Parent(Parent)
{
    AttachTo(Parent);
}

void UIObject::Awake()
{
    if (Parent && ObjectAlignment == Alignment::None)
        Debug::GetInstance().LogError(TextFormat("Alignment must be set"));
}

void UIObject::Update(float DeltaTime)
{
    if (ObjectAlignment == Alignment::Full)
    {
        if (IsAttached())
        {
            Bounds = GetParentRelativeBounds();
        }
        else
        {
            const Vector2& Resolution = Window::GetInstance().GetScreenSize();
            Bounds = Rectangle{0, 0, Resolution.x, Resolution.y};
        }
    }
}

void UIObject::AddToViewport()
{
    auto ContentHUD = static_cast<Player*>(GetOwner())->GetHUD();
    if (ContentHUD)
    {
        ContentHUD->AddToViewport(this);
    }
}

bool UIObject::AttachTo(UIObject* NewParent)
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

const Rectangle& UIObject::GetRelativeBounds() const
{
    if (!IsAttached()) return GetNativeBounds();
    
    const Rectangle& ParentBounds = GetParentRelativeBounds();
    
    const float X = Bounds.x + ParentBounds.x;
    const float Y = Bounds.y + ParentBounds.y;

    const float Width = Bounds.width + X > ParentBounds.width ? ParentBounds.width - X : Bounds.width;
    const float Height = Bounds.height + Y > ParentBounds.height ? ParentBounds.height - Y : Bounds.height;

    return Rectangle{X, Y, Width, Height};
}

const Vector2& UIObject::GetRelativePosition() const
{
    if (!IsAttached())
    {
        switch (ObjectAlignment)
        {
        case Alignment::None:   return Vector2{Bounds.x, Bounds.y};
        case Alignment::Left:   return Vector2{Bounds.x, Bounds.y};
        case Alignment::Center: return Vector2{Bounds.x + Bounds.width / 2.0f, Bounds.y};
        case Alignment::Right:  return Vector2{Bounds.x + Bounds.width, Bounds.y};
        case Alignment::Full:   return GetParentRelativePosition();
        default:                return Vector2{};
        }
    }
    else
    {
        const Rectangle& ParentBounds = GetParentRelativeBounds();

        const float X = Bounds.x + ParentBounds.x;
        const float Y = Bounds.y + ParentBounds.y;

        const float Width = Bounds.width + X > ParentBounds.width ? ParentBounds.width - X : Bounds.width;
    
        switch (ObjectAlignment)
        {
        case Alignment::None:   return Vector2{X, Y};
        case Alignment::Left:   return Vector2{X, Y};
        case Alignment::Center: return Vector2{X + Width / 2.0f, Y};
        case Alignment::Right:  return Vector2{X + Width, Y};
        case Alignment::Full:   return GetParentRelativePosition();
        default:                return Vector2{};
        }
    }
}

const Vector2& UIObject::GetRelativeSize() const
{
    if (!IsAttached()) return GetNativeSize();
        
    const Rectangle& ParentBounds = GetParentRelativeBounds();
    
    const float X = Bounds.x + ParentBounds.x;
    const float Y = Bounds.y + ParentBounds.y;

    const float Width = Bounds.width + X > ParentBounds.width ? ParentBounds.width - X : Bounds.width;
    const float Height = Bounds.height + Y > ParentBounds.height ? ParentBounds.height - Y : Bounds.height;

    return Vector2{Width, Height};
}
