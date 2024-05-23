#pragma once
#include "../../../../Core/UI/UIBase/UIBase.h"

class PauseWidget
    : public UIBase
{
public:
    PauseWidget(Object* Owner, const Slot& LayoutSlot, UIBase* Parent = nullptr);

    void Awake() override;
};
