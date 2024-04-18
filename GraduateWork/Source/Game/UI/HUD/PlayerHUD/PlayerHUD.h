#pragma once
#include "../../../../Core/UI/HUD/HUD.h"
#include "../../Widget/GameUI/WidgetGameUI.h"

class PlayerHUD
    : public HUD
{
public:
    PlayerHUD(Object* Owner);

    void Awake() override;

    void Draw() override;

private:
    std::shared_ptr<WidgetGameUI> GameUI;
};
