#pragma once
#include "../UIBase/UIBase.h"

class UIPanel
    : public UIBase
{
public:
    UIPanel(Object* Owner, const Slot& LayoutSlot, UIBase* Parent);
};
