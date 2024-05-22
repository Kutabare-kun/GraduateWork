#include "PowerUpBase.h"

#include "../Actors/Player/Player.h"
#include "../../Core/Timer/Manager/TimerManager.h"

PowerUpBase::PowerUpBase(SharedContext* Context, Object* Instigator, const Vector2& Position)
    : Actor(Context, Instigator, Position)
{
}

void PowerUpBase::Awake()
{
    Actor::Awake();

    GetContext()->TimerManagerSys->AddTimer([&]()
    {
        if (this) QueueForRemoval();
    }, TimeToRemove);
}

void PowerUpBase::OnCollisionBeginOverlap(std::shared_ptr<ColliderComponent> Other)
{
    Actor::OnCollisionBeginOverlap(Other);

    if (!Other->GetOwner()->GetTag()->Compare(Tag::Player)) return;
    OnTakePowerUp(static_cast<Player*>(Other->GetOwner()));
}
