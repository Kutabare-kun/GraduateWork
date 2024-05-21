#include "Enemy.h"

#include "../../../Core/Collection/ObjectCollection.h"
#include "../../../Core/Component/Velocity/VelocityComponent.h"
#include "../../Components/BehaviorTree/Simple/BehaviorTreeSimple.h"
#include "../../../Core/Component/Sprite/SpriteComponent.h"
#include "../Player/Player.h"

Enemy::Enemy(SharedContext* Context, Object* Instigator, const Vector2& Position)
    : Actor(Context, Instigator, Position), BehaviorTreeComp(nullptr)
{
    SetName("Enemy_");

    BehaviorTreeComp = AddComponent<BehaviorTreeSimple>(this);
}

void Enemy::Awake()
{
    Actor::Awake();

    GetTag()->Set(Tag::Enemy);
    GetSprite()->SetDrawLayer(DrawLayer::Entities);

    auto BBS = std::dynamic_pointer_cast<BlackboardSimple>(BehaviorTreeComp->GetBlackboard());
    if (!BBS) return;

    BBS->Target = GetContext()->Objects->GetObject<Player>().get();
}

void Enemy::OnHealthChange(Object* Instigator, float Delta, bool IsDead)
{
    if (IsDead) QueueForRemoval();
}
