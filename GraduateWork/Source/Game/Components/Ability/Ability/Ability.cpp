#include "Ability.h"

#include "../../../../Core/Component/Sprite/SpriteComponent.h"
#include "../../../../Core/Component/Velocity/VelocityComponent.h"
#include "../../../Actors/Enemy/Enemy.h"

Ability::Ability(SharedContext* Context, Object* Instigator, const Vector2& Position, float Damage)
    : Actor(Context, Instigator, Position), Damage(Damage)
{
    SetName("Ability_");

    AddComponent<VelocityComponent>(this);
}

void Ability::Awake()
{
    Actor::Awake();

    GetTag()->Set(Tag::Ability);
    GetSprite()->SetDrawLayer(DrawLayer::Entities);
}

void Ability::OnCollisionBeginOverlap(std::shared_ptr<ColliderComponent> Other)
{
    Actor::OnCollisionBeginOverlap(Other);

    if (Other->GetOwner() == GetInstigator()) return;

    Enemy* Target = dynamic_cast<Enemy*>(Other->GetOwner());
    if (!Target) return;

    OnBeginHit(Target);
}

void Ability::OnCollisionStayOverlap(std::shared_ptr<ColliderComponent> Other)
{
    Actor::OnCollisionStayOverlap(Other);

    if (Other->GetOwner() == GetInstigator()) return;

    Enemy* Target = dynamic_cast<Enemy*>(Other->GetOwner());
    if (!Target) return;

    OnEveryHit(Target);
}

void Ability::CreateAnimation()
{
}

void Ability::OnBeginHit(Enemy* Target)
{
}

void Ability::OnEveryHit(Enemy* Target)
{
}
