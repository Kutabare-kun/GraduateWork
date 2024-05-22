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

    Padding(float InLeft, float InRight, float InTop, float InBottom)
        : Left(InLeft), Right(InRight), Top(InTop), Bottom(InBottom)
    {
    }

    float Left;
    float Right;
    float Top;
    float Bottom;
};

struct Crop
{
    Crop() = default;

    explicit Crop(float InCrop)
        : CropRect({InCrop, InCrop, InCrop, InCrop})
    {
    }

    explicit Crop(const Rectangle& InCropRect)
        : CropRect(InCropRect)
    {
    }

    Crop(float InX, float InY, float InWidth, float InHeight)
        : CropRect({InX, InY, InWidth, InHeight})
    {
    }

    Rectangle CropRect;
};

struct Slot
{
    Slot() = default;

    Slot(const Padding& InPadding, const Crop& InCrop, const Rectangle& InSlotRect)
        : ObjectPadding(InPadding), ObjectCrop(InCrop), SlotRect(InSlotRect)
    {
    }

    Padding ObjectPadding;
    Crop ObjectCrop;
    Rectangle SlotRect;
};

class UIButton;
class UIText;

class UIBase
{
public:
    template <typename Type>
    void AddChild(const std::shared_ptr<Type>& Child)
    {
        std::shared_ptr<UIBase> ChildBase = std::dynamic_pointer_cast<UIBase>(Child);
        if (!ChildBase) return;

        AddChild(ChildBase);
    }

    template <typename Type>
    std::shared_ptr<Type> GetChild()
    {
        for (auto ChildUI : Children)
        {
            auto ExistingUI = std::dynamic_pointer_cast<Type>(ChildUI);
            if (ExistingUI) return ExistingUI;
        }

        return nullptr;
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

    Rectangle GetBounds() const;

    const Slot& GetLayoutSlot() const { return LayoutSlot; }
    void SetLayoutSlot(const Slot& NewSlot) { LayoutSlot = NewSlot; }

    void SetVisible(bool bVisible) { bIsVisible = bVisible; }
    bool IsVisible() const { return bIsVisible; }

    bool IsQueuedForRemoval() const { return bQueuedForRemoval; }
    void QueueForRemoval() { bQueuedForRemoval = true; }

    Object* GetOwner() const;
    UIBase* GetParent() const;

    std::string GetName() const { return Name; }

protected:
    void SetName(const std::string& InName) { Name = InName; }

    Vector2 GetScaleWindow(const Vector2& WindowResolution = Window::GetInstance().GetScreenSize()) const;

private:
    bool bIsVisible = true;

    Object* Owner;
    UIBase* Parent;

    Slot LayoutSlot;

    bool bQueuedForRemoval = false;

    std::vector<std::shared_ptr<UIBase>> Children;

    const Vector2 BaseResolution;

    std::string Name;
};
