#include "GameUI.h"

#include "../../../../Core/UI/Bar/UIBar.h"

GameUI::GameUI(Object* Owner, const Slot& LayoutSlot, UIBase* Parent)
    : UIPanel(Owner, LayoutSlot, Parent)
{
}

void GameUI::Awake()
{
    const Vector2 WindowResolution = Window::GetInstance().GetScreenSize();

    // Create a health bar
    HealthBar = std::make_shared<UIBar>(
        GetOwner(),
        Slot{
            Padding{0.0f},
            Crop{0.0f},
            Rectangle{20.0f, WindowResolution.y - 45.0f, 210.0f, 25.0f}
        }, this, "HealthBarEmpty.png", "HealthBarFill.png");
    AddChild(HealthBar);
    // ~Create a health bar

    UIPanel::Awake();
}
