#pragma once
#include "../../Object/Object.h"
#include "../../Window/Window.h"

struct Padding
{
    Padding() = default;
    explicit Padding(float InPadding)
        : Left(InPadding), Right(InPadding), Top(InPadding), Bottom(InPadding)
    {
    }
    
    float Left;
    float Right;
    float Top;
    float Bottom;
};

struct Slot
{
    Slot() = default;
    Slot(const Padding& InPadding, const Rectangle& InSlotRect)
        : ObjectPadding(InPadding), SlotRect(InSlotRect)
    {}

    Padding ObjectPadding;
    Rectangle SlotRect;
};

class UIButton;

class UIBase
{
public:
    template<typename Type>
    void AddChild(const std::shared_ptr<Type>& Child)
    {
        std::shared_ptr<UIBase> ChildBase = std::dynamic_pointer_cast<UIBase>(Child);
        if (!ChildBase) return;
        
        AddChild(ChildBase);
    }
    
public:
    UIBase(Object* Owner, const Slot& LayoutSlot, UIBase* Parent = nullptr);
    virtual ~UIBase() = default;

    // Called when the object is created.
    virtual void Awake();

    // Update the object and its children.
    virtual void Update(float DeltaTime);

    // Draw the object and its children.
    virtual void Draw();

    // Add a child to this object.
    // The child has parent set to this object.
    // Do not call function Awake() on the child.
    void AddChild(std::shared_ptr<UIBase>& Child);

    // Attach this object to a parent.
    bool AttachToParent(UIBase* Parent);

    // Detach this object from a parent.
    bool DetachFromParent();

    const Rectangle& GetBounds() const;
    
    const Slot& GetLayoutSlot() const { return LayoutSlot; }
    void SetLayoutSlot(const Slot& NewSlot) { LayoutSlot = NewSlot; }

    Object* GetOwner() const;
    UIBase* GetParent() const;

protected:
    Vector2 GetScaleWindow(const Vector2& WindowResolution = Window::GetInstance().GetScreenSize()) const;

private:
    Object* Owner;
    UIBase* Parent;

    Slot LayoutSlot;

    std::vector<std::shared_ptr<UIBase>> Children;
};
