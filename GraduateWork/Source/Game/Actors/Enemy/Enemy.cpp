#include "Enemy.h"

#include "../../../Core/Collection/ObjectCollection.h"
#include "../../../Core/Component/Velocity/VelocityComponent.h"
#include "../../Components/BehaviorTree/Simple/BehaviorTreeSimple.h"
#include "../../../Core/Component/Sprite/SpriteComponent.h"
#include "../Player/Player.h"

Enemy::Enemy(SharedContext* Context, const Vector2& Position)
    : Actor(Context, Position), BehaviorTreeComp(nullptr)
{
    AddComponent<MovementComponent>(this, 200.0f);

    BehaviorTreeComp = AddComponent<BehaviorTreeSimple>(this);
}

void Enemy::Awake()
{
    Actor::Awake();

    GetSprite()->SetDrawLayer(DrawLayer::Entities);

    auto BBS = std::dynamic_pointer_cast<BlackboardSimple>(BehaviorTreeComp->GetBlackboard());
    if (!BBS) return;

    BBS->Target = GetContext()->Objects->GetObject<Player>().get();
}
