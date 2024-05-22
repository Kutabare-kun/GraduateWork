#pragma once
#include "../PowerUpBase.h"

class AbilityUpgradePowerUp
    : public PowerUpBase
{
public:
    AbilityUpgradePowerUp(SharedContext* Context, Object* Instigator, const Vector2& Position);

    void Awake() override;

protected:
    void CreateAnimation() override;

    void OnTakePowerUp(Player* ThisPlayer) override;
};
