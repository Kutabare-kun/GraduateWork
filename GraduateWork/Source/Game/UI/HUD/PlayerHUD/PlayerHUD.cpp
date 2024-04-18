#include "PlayerHUD.h"

PlayerHUD::PlayerHUD(Object* Owner)
    : HUD(Owner)
{
    
}

void PlayerHUD::Awake()
{
    GameUI = AddWidget<WidgetGameUI>(GetOwner(), Rectangle{0, 0, 0, 0}, nullptr, Alignment::Full);
    GameUI->AddToViewport();
    
    HUD::Awake();
}

void PlayerHUD::Draw()
{
    HUD::Draw();
}
