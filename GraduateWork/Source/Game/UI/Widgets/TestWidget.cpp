#include "TestWidget.h"

#include <iostream>

#include "../../../Core/UI/Button/UIButton.h"

TestWidget::TestWidget(Object* Owner, const Slot& LayoutSlot, UIBase* Parent)
    : UIPanel(Owner, LayoutSlot, Parent)
{
}

void TestWidget::Awake()
{
    std::shared_ptr<UIButton> ActionButton = std::make_shared<UIButton>(GetOwner(), Slot{Padding{0.0f}, Rectangle{0.0f, 0.0f, 200.0f, 80.0f}}, this);
    AddChild(ActionButton);
    
    ActionButton->SetAction([]() { std::cout << "Button pressed" << std::endl; });
    
    UIPanel::Awake();
}

void TestWidget::Update(float DeltaTime)
{
    UIPanel::Update(DeltaTime);
}

void TestWidget::Draw()
{
    UIPanel::Draw();
}
