#pragma once
#include "../Enemy.h"

class GoblinEnemy
    : public Enemy
{
public:
    GoblinEnemy(SharedContext* Context, const Vector2& Position);

protected:
    void CreateAnimation() override;
};
