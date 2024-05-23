#include "PauseWidget.h"

#include "../../../../Core/Directory/Directory.h"
#include "../../../../Core/SceneManager/SceneStateMachine.h"
#include "../../../../Core/UI/Button/UIButton.h"
#include "../../../Scene/MainScene/MainScene.h"
#include "../../HUD/PlayerHUD.h"
#include "../GameUI/GameUI.h"

PauseWidget::PauseWidget(Object* Owner, const Slot& LayoutSlot, UIBase* Parent)
    : UIBase(Owner, LayoutSlot, Parent)
{
}

void PauseWidget::Awake()
{
    UIBase::Awake();

    const Vector2 WindowResolution = Window::GetInstance().GetScreenSize();

    ButtonStateTexture ButtonTextures
    {
        "Button_Normal.png",
        "Button_Clicked.png",
        "Button_Clicked.png",
        "Button_Clicked.png"
    };

    std::shared_ptr<UIButton> PlayButton = std::make_shared<UIButton>(
        GetOwner(),
        Slot{
            Padding{0.0f},
            Crop{0.0f},
            Rectangle{WindowResolution.x / 2.0f - 150.0f, WindowResolution.y / 2.0f - 84.0f, 300.0f, 64.0f}
        }, this, ButtonTextures);
    AddChild(PlayButton);

    PlayButton->SetAction([&]()
    {
        QueueForRemoval();

        const std::shared_ptr<PlayerHUD> HUD = GetOwner()->GetComponent<PlayerHUD>();
        const std::shared_ptr<GameUI> ThisGameUI = HUD->GetGameUIWidget();
        ThisGameUI->SetVisible(true);
    });

    ResourceAllocator<FontResource>* FontAllocator = GetOwner()->GetContext()->FontAllocator;
    const int RobotoRegularID = FontAllocator->Add(Directory::GetInstance().GetFont("Roboto-Regular.ttf"));

    TextSettings PlayTextSetting
    {
        GetOwner()->GetContext()->FontAllocator->Get(RobotoRegularID)->Get_Impl(),
        "RESUME",
        Vector2{0.0f, 0.0f},
        0.0f,
        32.0f,
        1.0f,
        WHITE
    };

    const Slot& PlayButtonLayout = PlayButton->GetLayoutSlot();

    std::shared_ptr<UIText> PlayText = std::make_shared<UIText>(
        GetOwner(),
        Slot{
            Padding{0.0f},
            Crop{0.0f},
            PlayButtonLayout.SlotRect
        }, PlayButton.get(), PlayTextSetting);
    PlayButton->AddChild(PlayText);

    std::shared_ptr<UIButton> ExitButton = std::make_shared<UIButton>(
        GetOwner(),
        Slot{
            Padding{0.0f},
            Crop{0.0f},
            Rectangle{WindowResolution.x / 2.0f - 150.0f, WindowResolution.y / 2.0f, 300.0f, 64.0f}
        }, this, ButtonTextures);
    AddChild(ExitButton);

    ExitButton->SetAction([&]()
    {
        QueueForRemoval();

        const int MainSceneID = SceneStateMachine::GetInstance().GetScene<MainScene>();
        if (MainSceneID == -1) return;

        SceneStateMachine::GetInstance().SwitchTo(MainSceneID);
    });

    TextSettings ExitTextSetting
    {
        GetOwner()->GetContext()->FontAllocator->Get(RobotoRegularID)->Get_Impl(),
        "EXIT",
        Vector2{0.0f, 0.0f},
        0.0f,
        32.0f,
        1.0f,
        WHITE
    };

    const Slot& ExitButtonLayout = ExitButton->GetLayoutSlot();

    std::shared_ptr<UIText> ExitText = std::make_shared<UIText>(
        GetOwner(),
        Slot{
            Padding{0.0f},
            Crop{0.0f},
            ExitButtonLayout.SlotRect
        }, ExitButton.get(), ExitTextSetting);
    ExitButton->AddChild(ExitText);
}
