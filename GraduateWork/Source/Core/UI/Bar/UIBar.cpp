#include "UIBar.h"

#include <algorithm>

#include "../Image/UIImage.h"

UIBar::UIBar(Object* Owner, const Slot& LayoutSlot, UIBase* Parent, const std::string& BackgroundImageName,
                const std::string& ForegroundImageName)
    : UIBase(Owner, LayoutSlot, Parent)
{
    BackgroundImage = std::make_shared<UIImage>(GetOwner(), LayoutSlot, this, BackgroundImageName);
    ForegroundImage = std::make_shared<UIImage>(GetOwner(), LayoutSlot, this, ForegroundImageName);
}

void UIBar::Awake()
{
    UIBase::Awake();

    AddChild(BackgroundImage);
    AddChild(ForegroundImage);
}

void UIBar::Update(float DeltaTime)
{
    UIBase::Update(DeltaTime);

    if (IsKeyDown(KEY_KP_SUBTRACT)) UpdatePercentage(Percentage - 0.01f);
    if (IsKeyDown(KEY_KP_ADD)) UpdatePercentage(Percentage + 0.01f);
}

void UIBar::Draw()
{
    UIBase::Draw();
}

void UIBar::UpdatePercentage(float NewPercentage)
{
    Percentage = std::clamp<float>(NewPercentage, 0.0f, 1.0f);
    const Rectangle HealthBar = ForegroundImage->GetTextureBounds();

    const float NewWidth = HealthBar.width * Percentage;
    const float DeltaWidth = HealthBar.width - NewWidth;

    const Slot& ForegroundSlot = ForegroundImage->GetLayoutSlot();
    const Slot& BackgroundSlot = BackgroundImage->GetLayoutSlot();

    const float DeltaX = BackgroundSlot.SlotRect.width - BackgroundSlot.SlotRect.width * Percentage;

    ForegroundImage->SetLayoutSlot(
        Slot{
            Padding{
                0.0f, 0.0f, 0.0f, 0.0f
            },
            Crop{
                0.0f, 0.0f, DeltaWidth, 0.0f
            },
            Rectangle{
                BackgroundSlot.SlotRect.x, BackgroundSlot.SlotRect.y,
                BackgroundSlot.SlotRect.width - DeltaX, BackgroundSlot.SlotRect.height
            }
        }
    );
}
