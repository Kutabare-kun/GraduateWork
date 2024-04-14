#pragma once
#include "../Object/Object.h"

#include "raylib.h"

enum class Alignment
{
    None,
    Left,
    Center,
    Right
};

class UIObject
{
public:
    UIObject(Object* Owner, const Rectangle& Bounds, std::shared_ptr<UIObject>&& Parent = nullptr, Alignment HorizontalAlignment = Alignment::None);
    virtual ~UIObject() = default;

    virtual void Awake();
    
    virtual void Draw() = 0;
    virtual void Update(float DeltaTime) = 0;

    void AddToViewport();

    bool AttachTo(std::shared_ptr<UIObject>& NewParent);
    bool Detach();

    bool IsAttached() const { return bIsAttached; }
    bool IsVisible() const { return bIsVisible; }

    void SetVisible(bool bNewVisible) { bIsVisible = bNewVisible; }

    const Rectangle& GetBounds() const { return Parent ? Parent->GetBounds() : Bounds; }
    const Rectangle& GetParentRelativeBounds() const { return Parent.get() ? Parent->GetRelativeBounds() : Rectangle{}; }
    const Rectangle& GetRelativeBounds() const { return Bounds; }

    void SetBounds(const Rectangle& NewBounds) { Bounds = NewBounds; }
    
    const Vector2& GetPosition() const { return Parent.get() ? Parent->GetPosition() : Vector2{ Bounds.x, Bounds.y }; }
    const Vector2& GetParentRelativePosition() const { return Parent.get() ? Parent->GetRelativePosition() : Vector2{}; }
    const Vector2& GetRelativePosition() const;

    void SetPosition(const Vector2& NewPosition) { Bounds.x = NewPosition.x; Bounds.y = NewPosition.y; }
    
    const Vector2& GetSize() const { return Parent.get() ? Parent->GetSize() : Vector2{ Bounds.width, Bounds.height }; }
    const Vector2& GetParentRelativeSize() const { return Parent.get() ? Parent->GetRelativeSize() : Vector2{}; }
    const Vector2& GetRelativeSize() const { return Vector2{ Bounds.width, Bounds.height }; }

    void SetSize(const Vector2& NewSize) { Bounds.width = NewSize.x; Bounds.height = NewSize.y; }

    const Alignment& GetHorizontalAlignment() const { return HorizontalAlignment; }
    void SetHorizontalAlignment(Alignment NewHorizontalAlignment) { HorizontalAlignment = NewHorizontalAlignment; }
    
    Object* GetOwner() const { return Owner; }
    std::shared_ptr<UIObject> GetParent() const { return Parent; }

private:
    Rectangle Bounds;
    bool bIsAttached;
    bool bIsVisible;
    Object* Owner;

    Alignment HorizontalAlignment;

    std::shared_ptr<UIObject> Parent;
};
