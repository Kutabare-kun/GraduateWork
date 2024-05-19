#include "Enemy.h"

#include "../../../Core/Collection/ObjectCollection.h"
#include "../../../Core/Component/Collider/BoxCollider/BoxColliderComponent.h"
#include "../../../Core/Component/Velocity/VelocityComponent.h"
#include "../../Components/BehaviorTree/Simple/BehaviorTreeSimple.h"
#include "../Player/Player.h"

Enemy::Enemy(SharedContext* Context, const Vector2& Position)
    : Actor(Context, Position), BehaviorTreeComp(nullptr)
{
    const auto Collider = AddComponent<BoxColliderComponent>(this);
    Collider->SetSize(165 * 0.4f, 145 * 0.4f);
    Collider->SetOffset(0.0f, 14.0f);
    Collider->SetLayer(CollisionLayer::Enemy);

    AddComponent<VelocityComponent>(this);

    BehaviorTreeComp = AddComponent<BehaviorTreeSimple>(this);
}

void Enemy::Awake()
{
    Actor::Awake();

    auto BBS = std::dynamic_pointer_cast<BlackboardSimple>(BehaviorTreeComp->GetBlackboard());
    if (!BBS) return;

    BBS->Target = GetContext()->Objects->GetObject<Player>().get();
}

void Enemy::Update(float DeltaTime)
{
    Actor::Update(DeltaTime);
}

void Enemy::LateUpdate(float DeltaTime)
{
    Actor::LateUpdate(DeltaTime);
}

void Enemy::Draw(const Camera2D& OwnerCamera)
{
    Actor::Draw(OwnerCamera);
}
