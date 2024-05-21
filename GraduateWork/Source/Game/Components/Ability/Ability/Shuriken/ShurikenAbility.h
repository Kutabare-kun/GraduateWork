#pragma once
#include "../Ability.h"

class ShurikenAbility
    : public Ability
{
public:
    ShurikenAbility(SharedContext* Context, Object* Instigator, const Vector2& Position, float Damage);

    void OnEveryHit(Enemy* Target) override;
};
