#include "WalkInLineComponent.h"
#include "../../../Core/Object/Object.h"

WalkInLineComponent::WalkInLineComponent(Object* NewOwner, float NewMoveSpeed)
    : ActorComponent(NewOwner), MoveSpeed(NewMoveSpeed)
{
}

void WalkInLineComponent::Awake()
{
     Velocity = GetOwner()->GetComponent<VelocityComponent>();
}

void WalkInLineComponent::OnInteraction(Object* Other)
{
    if (!Velocity) return;
    Velocity->SetVelocity(MoveSpeed, 0.0f);
}
