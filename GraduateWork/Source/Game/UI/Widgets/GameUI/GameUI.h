#pragma once
#include "../../../../Core/UI/Panel/UIPanel.h"

class UIBar;

class GameUI
    : public UIPanel
{
public:
    GameUI(Object* Owner, const Slot& LayoutSlot, UIBase* Parent);

    void Awake() override;

    std::shared_ptr<UIBar> GetHealthBar() const { return HealthBar; }

private:
    std::shared_ptr<UIBar> HealthBar;
};
