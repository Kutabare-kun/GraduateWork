#pragma once
#include "../Enemy.h"

class EyeEnemy
    : public Enemy
{
public:
    EyeEnemy(SharedContext* Context, const Vector2& Position);

protected:
    void CreateAnimation() override;
};
