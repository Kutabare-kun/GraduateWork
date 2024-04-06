#include "InstanceIDComponent.h"

unsigned int InstanceIDComponent::InstanceCounter = 0;

InstanceIDComponent::InstanceIDComponent(Object* Owner)
    : ActorComponent(Owner), InstanceID(InstanceCounter++)
{
}

InstanceIDComponent::~InstanceIDComponent()
{
}

unsigned int InstanceIDComponent::GetID() const
{
    return InstanceID;
}
