#include "ActorComponent.h"

ActorComponent::ActorComponent(Actor* NewOwner, bool bEnableTicks)
    : bEnableTicks(bEnableTicks), Owner(NewOwner)
{}

void ActorComponent::AttachTo(Actor* NewOwner)
{
    Owner = NewOwner;
}

void ActorComponent::BeginPlay()
{}

void ActorComponent::EventTick(float DeltaTime)
{}

void ActorComponent::Draw()
{}
