#include "ShurikenAbility.h"

ShurikenAbility::ShurikenAbility(SharedContext* Context, Object* Instigator, const Vector2& Position, float Damage)
    : Ability(Context, Instigator, Position, Damage)
{
}

void ShurikenAbility::OnEveryHit(Enemy* Target)
{
    
}
