#include "WidgetGameUI.h"

#include "../../../../Core/Directory/Directory.h"
#include "../../../../Core/StaticFunctions/Debug.h"
#include "../../../../Core/UI/Text/Text.h"

WidgetGameUI::WidgetGameUI(Object* Owner, const Rectangle& Bounds, UIObject* Parent,
                           Alignment HorizontalAlignment)
        : Panel(Owner, Bounds, Parent, HorizontalAlignment)
{
    ButtonClose = std::make_shared<Button>(Owner, Rectangle{ 50, 50, 128, 64 }, this, Alignment::Center);
    std::shared_ptr<Button> ThisButton = std::dynamic_pointer_cast<Button>(ButtonClose);
    ThisButton->AttachOnClicked([this]()
    {
        Debug::GetInstance().Log(TextFormat("ButtonClose Clicked!"));
    });

    ThisButton->SetTexture(GetOwner()->GetContext()->TextureAllocator->Add(Directory::GetInstance().GetTexture("Button_Normal.png")), ButtonState::Normal);
    ThisButton->SetTexture(GetOwner()->GetContext()->TextureAllocator->Add(Directory::GetInstance().GetTexture("Button_Clicked.png")), ButtonState::Clicked);

    Font TextFont = LoadFont(Directory::GetInstance().GetFont("Roboto-Regular.ttf").c_str());
    
    TextSettings TextAppearance {
        TextFont, "Close", Vector2{ 64, 32 }, 0.0f, 32.0f, 1.0f, WHITE
    };

    std::shared_ptr<UIObject> ButtonText = std::make_shared<Text>(Owner, Rectangle{ 0, 0, 128, 64 }, ThisButton.get(), Alignment::Center, TextAppearance);
    ThisButton->SetTextUI(ButtonText);
}

void WidgetGameUI::Awake()
{
    AddChild(ButtonClose);
    
    Panel::Awake();
}

void WidgetGameUI::Update(float DeltaTime)
{
    Panel::Update(DeltaTime);
}

void WidgetGameUI::Draw()
{
    Panel::Draw();
}
