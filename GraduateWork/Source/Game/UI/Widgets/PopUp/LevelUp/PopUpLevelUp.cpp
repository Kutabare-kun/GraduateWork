#include "PopUpLevelUp.h"

#include "../../../../../Core/Timer/Manager/TimerManager.h"
#include "../../../../../Core/UI/Image/UIImage.h"

PopUpLevelUp::PopUpLevelUp(Object* Owner, const Slot& LayoutSlot, UIBase* Parent)
    : UIBase(Owner, LayoutSlot, Parent)
{
    SetName(TextFormat("PopUpLevelUp"));
}

void PopUpLevelUp::Awake()
{
    std::shared_ptr<UIImage> LevelUpImage = std::make_shared<UIImage>(
        GetOwner(), Slot{Padding{0.0f}, Crop{0.0f}, GetLayoutSlot().SlotRect},
        nullptr, "LevelUpPopUp.png");
    AddChild(LevelUpImage);

    UIBase::Awake();

    GetOwner()->GetContext()->TimerManagerSys->AddTimer([&]()
    {
        QueueForRemoval();
    }, 1.5f);
}
