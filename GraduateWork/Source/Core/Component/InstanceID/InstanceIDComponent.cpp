#include "InstanceIDComponent.h"

int InstanceIDComponent::InstanceCounter = 0;

InstanceIDComponent::InstanceIDComponent(Object* Owner)
    : ActorComponent(Owner), InstanceID(InstanceCounter++)
{
}

InstanceIDComponent::~InstanceIDComponent()
{
}

int InstanceIDComponent::GetInstanceID() const
{
    return InstanceID;
}
