#pragma once
#include "../../../../Core/UI/HUD/HUD.h"

class PlayerHUD
    : public HUD
{
public:
    PlayerHUD(Object* Owner);

    void Draw() override;
};
