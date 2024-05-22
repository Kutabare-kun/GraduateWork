#pragma once
#include "../PowerUpBase.h"

class HealthPowerUp
    : public PowerUpBase
{
public:
    HealthPowerUp(SharedContext* Context, Object* Instigator, const Vector2& Position);

    void Awake() override;

protected:
    void CreateAnimation() override;

    void OnTakePowerUp(Player* ThisPlayer) override;

    float HealthValue = 10.0f;
    float HealthByPercent = 0.010f;
};
