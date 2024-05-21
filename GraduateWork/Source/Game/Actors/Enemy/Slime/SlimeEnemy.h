#pragma once
#include "../Enemy.h"

class SlimeEnemy
    : public Enemy
{
public:
    SlimeEnemy(SharedContext* Context, Object* Instigator, const Vector2& Position);

protected:
    void CreateAnimation() override;
};
