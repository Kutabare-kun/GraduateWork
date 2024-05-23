#pragma once
#include "../../../../Core/UI/Panel/UIPanel.h"

class LevelBorder;
class UIBar;

class GameUI
    : public UIPanel
{
public:
    GameUI(Object* Owner, const Slot& LayoutSlot, UIBase* Parent);

    void Awake() override;

    std::shared_ptr<UIBar> GetHealthBar() const { return HealthBar; }
    std::shared_ptr<LevelBorder> GetLevelBorderWidget() const { return LevelBorderWidget; }

private:
    std::shared_ptr<UIBar> HealthBar;
    std::shared_ptr<LevelBorder> LevelBorderWidget;
};
