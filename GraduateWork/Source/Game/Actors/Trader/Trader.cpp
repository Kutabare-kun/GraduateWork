#include "Trader.h"

#include "../../../Core/Component/Collider/BoxCollider/BoxColliderComponent.h"
#include "../../Components/WalkInLine/WalkInLineComponent.h"
#include "../../../Core/Component/Velocity/VelocityComponent.h"

Trader::Trader(SharedContext* Context, const Vector2& Position)
    : Actor(Context, Position)
{
    SetName("Trader_");
    
    AddComponent<InteractableComponent>(this);

    const auto Collider = AddComponent<BoxColliderComponent>(this);
    Collider->SetSize(165 * 0.4f, 145 * 0.4f);
    Collider->SetOffset(0.0f, 14.0f);
    Collider->SetLayer(CollisionLayer::NPC);

    AddComponent<WalkInLineComponent>(this);
    AddComponent<VelocityComponent>(this);
}

void Trader::Awake()
{
    Actor::Awake();
}

void Trader::Update(float DeltaTime)
{
    Actor::Update(DeltaTime);
}

void Trader::LateUpdate(float DeltaTime)
{
    Actor::LateUpdate(DeltaTime);
}

void Trader::Draw(const Camera2D& OwnerCamera)
{
    Actor::Draw(OwnerCamera);
}

void Trader::CreateAnimation()
{
}
