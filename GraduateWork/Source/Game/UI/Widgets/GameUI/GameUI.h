#pragma once
#include "../../../../Core/UI/Panel/UIPanel.h"

class GameUI
    : UIPanel
{
public:
    GameUI(Object* Owner, const Slot& LayoutSlot, UIBase* Parent);

    void Awake() override;

private:
    
};
