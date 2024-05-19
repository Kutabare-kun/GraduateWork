#pragma once
#include "../../../Core/Component/BehaviorTree/BehaviorTree.h"
#include "../../../Core/Object/Actor/Actor.h"

class Enemy
    : public Actor
{
public:
    Enemy(SharedContext* Context, const Vector2& Position);

    ~Enemy() override = default;

    void Awake() override;

    std::shared_ptr<BehaviorTree> GetBehaviorTree() const { return BehaviorTreeComp; }

protected:
    std::shared_ptr<BehaviorTree> BehaviorTreeComp;
};
