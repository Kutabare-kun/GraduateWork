#include "WidgetGameUI.h"

#include "../../../../Core/Directory/Directory.h"
#include "../../../../Core/StaticFunctions/Debug.h"

WidgetGameUI::WidgetGameUI(Object* Owner, const Rectangle& Bounds, UIObject* Parent,
                           Alignment HorizontalAlignment)
        : Panel(Owner, Bounds, Parent, HorizontalAlignment)
{
    ButtonClose = std::make_shared<Button>(Owner, Rectangle{ 50, 50, 100, 50 }, this, Alignment::Left);
    std::dynamic_pointer_cast<Button>(ButtonClose)->AttachOnClicked([this]()
    {
        Debug::GetInstance().Log(TextFormat("ButtonClose Clicked!"));
    });

    std::dynamic_pointer_cast<Button>(ButtonClose)->SetTexture(GetOwner()->GetContext()->TextureAllocator->Add(Directory::GetInstance().GetTexture("Button.png")));
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
