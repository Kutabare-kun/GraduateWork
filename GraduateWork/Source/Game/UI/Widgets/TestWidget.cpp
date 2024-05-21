#include "TestWidget.h"

#include <iostream>

#include "../../../Core/Directory/Directory.h"
#include "../../../Core/UI/Button/UIButton.h"
#include "../../../Core/UI/Text/UIText.h"

TestWidget::TestWidget(Object* Owner, const Slot& LayoutSlot, UIBase* Parent)
    : UIPanel(Owner, LayoutSlot, Parent)
{
}

void TestWidget::Awake()
{
    ButtonStateTexture ButtonTextures
    {
        "Button_Normal.png",
        "Button_Clicked.png",
        "Button_Clicked.png",
        "Button_Clicked.png"
    };

    std::shared_ptr<UIButton> ActionButton = std::make_shared<UIButton>(
        GetOwner(), Slot{Padding{0.0f}, Rectangle{0.0f, 0.0f, 200.0f, 80.0f}}, this, ButtonTextures);
    AddChild(ActionButton);
    ActionButton->SetAction([]() { std::cout << "Button pressed" << std::endl; });

    ResourceAllocator<FontResource>* FontAllocator = GetOwner()->GetContext()->FontAllocator;
    const int RobotoRegularID = FontAllocator->Add(Directory::GetInstance().GetFont("Roboto-Regular.ttf"));

    TextSettings ButtonTextSettings
    {
        FontAllocator->Get(RobotoRegularID)->Get_Impl(),
        "Button",
        Vector2{0.0f, 0.0f},
        0.0f,
        32.0f,
        1.0f,
        WHITE
    };

    std::shared_ptr<UIText> ButtonText = std::make_shared<UIText>(
        GetOwner(), Slot{Padding{0.0f}, Rectangle{0.0f, 0.0f, 200.0f, 80.0f}},
        ActionButton.get(), ButtonTextSettings);

    ActionButton->AddChild(ButtonText);

    UIPanel::Awake();
}
