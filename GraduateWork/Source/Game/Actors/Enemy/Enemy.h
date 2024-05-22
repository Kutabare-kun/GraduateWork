#pragma once
#include "../../../Core/Component/BehaviorTree/BehaviorTree.h"
#include "../../../Core/Object/Actor/Actor.h"

class AttributeComponent;

class Enemy
    : public Actor
{
public:
    Enemy(SharedContext* Context, Object* Instigator, const Vector2& Position);

    ~Enemy() override = default;

    void Awake() override;

    void OnHealthChange(Object* Instigator, float Delta, bool IsDead) override;

    std::shared_ptr<BehaviorTree> GetBehaviorTree() const { return BehaviorTreeComp; }
    std::shared_ptr<AttributeComponent> GetAttributeComp() const { return AttributeComp; }

protected:
    std::shared_ptr<BehaviorTree> BehaviorTreeComp;
    std::shared_ptr<AttributeComponent> AttributeComp;

    
};
