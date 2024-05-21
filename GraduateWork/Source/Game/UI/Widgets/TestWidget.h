#pragma once
#include "../../../Core/UI/Panel/UIPanel.h"

class TestWidget
    : public UIPanel
{
public:
    TestWidget(Object* Owner, const Slot& LayoutSlot, UIBase* Parent);

    void Awake() override;

private:
};
