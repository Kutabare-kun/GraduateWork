#include "GameUI.h"

#include "../../../../Core/StaticFunctions/Debug.h"
#include "../../../../Core/UI/Bar/UIBar.h"
#include "../../../../Core/UI/Button/UIButton.h"
#include "../../HUD/PlayerHUD.h"
#include "../LevelBorder/LevelBorder.h"
#include "../PauseWidget/PauseWidget.h"

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

    LevelBorderWidget = std::make_shared<LevelBorder>(
        GetOwner(),
        Slot{
            Padding{0.0f},
            Crop{0.0f},
            Rectangle{20.0f, WindowResolution.y - 80.0f, 32.0f, 32.0f}
        }, this);
    AddChild(LevelBorderWidget);

    ButtonStateTexture ButtonTextures
    {
        "Pause_Button_Normal.png",
        "Pause_Button_Clicked.png",
        "Pause_Button_Clicked.png",
        "Pause_Button_Clicked.png"
    };

    std::shared_ptr<UIButton> ActionButton = std::make_shared<UIButton>(
        GetOwner(),
        Slot{
            Padding{0.0f},
            Crop{0.0f},
            Rectangle{WindowResolution.x - 68.0f, 20.0f, 48.0f, 48.0f}
        }, this, ButtonTextures);
    AddChild(ActionButton);

    ActionButton->SetAction([&]()
    {
        SetVisible(false);

        std::shared_ptr<PlayerHUD> HUD = GetOwner()->GetComponent<PlayerHUD>();
        std::shared_ptr<PauseWidget> ThisPauseWidget = std::make_shared<PauseWidget>(
            GetOwner(),
            Slot{
                Padding{0.0f},
                Crop{0.0f},
                Rectangle{0.0f, 0.0f, WindowResolution.x, WindowResolution.y}
            },
            nullptr);

        HUD->Add(ThisPauseWidget);
    });

    UIPanel::Awake();
}
