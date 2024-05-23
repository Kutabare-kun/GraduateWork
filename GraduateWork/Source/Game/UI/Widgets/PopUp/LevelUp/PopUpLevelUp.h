#pragma once
#include "../../../../../Core/UI/UIBase/UIBase.h"

class PopUpLevelUp
    : public UIBase
{
public:
    PopUpLevelUp(Object* Owner, const Slot& LayoutSlot, UIBase* Parent = nullptr);

    void Awake() override;
};
