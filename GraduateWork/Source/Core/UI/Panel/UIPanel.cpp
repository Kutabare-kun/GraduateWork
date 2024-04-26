#include "UIPanel.h"

UIPanel::UIPanel(Object* Owner, const Slot& LayoutSlot, UIBase* Parent)
    : UIBase(Owner, LayoutSlot, Parent)
{
}

void UIPanel::Awake()
{
    UIBase::Awake();

    
}

void UIPanel::Update(float DeltaTime)
{
    UIBase::Update(DeltaTime);
}

void UIPanel::Draw()
{
    UIBase::Draw();
}
