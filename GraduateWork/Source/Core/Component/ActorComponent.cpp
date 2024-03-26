#include "ActorComponent.h"

ActorComponent::ActorComponent(Object* NewOwner, bool bEnableTicks)
    : bEnableTicks(bEnableTicks), Owner(NewOwner)
{}

void ActorComponent::Awake()
{}

void ActorComponent::Start()
{}

void ActorComponent::Update(float DeltaTime)
{}

void ActorComponent::LateUpdate(float DeltaTime)
{}

void ActorComponent::Draw()
{}
