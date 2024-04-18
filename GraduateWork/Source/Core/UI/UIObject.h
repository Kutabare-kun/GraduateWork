#pragma once
#include "../Object/Object.h"

#include "raylib.h"

enum class Alignment
{
    None,
    Left,
    Center,
    Right,
    Full,
};

struct Padding
{
    float Left;
    float Right;
    float Top;
    float Bottom;
};

class UIObject
{
public:
    UIObject(Object* Owner, const Rectangle& Bounds, UIObject* Parent = nullptr, Alignment HorizontalAlignment = Alignment::None);
    virtual ~UIObject() = default;

    virtual void Awake();
    
    virtual void Draw() = 0;
    virtual void Update(float DeltaTime);

    void AddToViewport();

    bool AttachTo(UIObject* NewParent);
    bool Detach();

    bool IsAttached() const { return bIsAttached; }
    bool IsVisible() const { return bIsVisible; }

    void SetVisible(bool bNewVisible) { bIsVisible = bNewVisible; }

    const Rectangle& GetBounds() const { return Parent ? Parent->GetBounds() : Bounds; }
    const Rectangle& GetParentRelativeBounds() const { return Parent ? Parent->GetRelativeBounds() : Rectangle{}; }
    const Rectangle& GetRelativeBounds() const;
    const Rectangle& GetNativeBounds() const { return Bounds; }

    void SetBounds(const Rectangle& NewBounds) { Bounds = NewBounds; }
    
    const Vector2& GetPosition() const { return Parent ? Parent->GetPosition() : Vector2{ Bounds.x, Bounds.y }; }
    const Vector2& GetParentRelativePosition() const { return Parent ? Parent->GetRelativePosition() : Vector2{}; }
    const Vector2& GetRelativePosition() const;
    const Vector2& GetNativePosition() const { return Vector2{ Bounds.x, Bounds.y }; }

    void SetPosition(const Vector2& NewPosition) { Bounds.x = NewPosition.x; Bounds.y = NewPosition.y; }
    
    const Vector2& GetSize() const { return Parent ? Parent->GetSize() : Vector2{ Bounds.width, Bounds.height }; }
    const Vector2& GetParentRelativeSize() const { return Parent ? Parent->GetRelativeSize() : Vector2{}; }
    const Vector2& GetRelativeSize() const;
    const Vector2& GetNativeSize() const { return Vector2{ Bounds.width, Bounds.height }; }

    void SetSize(const Vector2& NewSize) { Bounds.width = NewSize.x; Bounds.height = NewSize.y; }

    const Alignment& GetObjectAlignment() const { return ObjectAlignment; }
    void SetHorizontalAlignment(Alignment NewHorizontalAlignment) { ObjectAlignment = NewHorizontalAlignment; }
    
    Object* GetOwner() const { return Owner; }
    UIObject* GetParent() const { return Parent; }

private:
    Object* Owner;
    Rectangle Bounds;
    bool bIsAttached;
    bool bIsVisible;

    Alignment ObjectAlignment;

    UIObject* Parent;
};
