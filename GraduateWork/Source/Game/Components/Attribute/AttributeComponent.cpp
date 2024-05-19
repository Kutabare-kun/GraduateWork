#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(Object* Owner)
    : ActorComponent(Owner)
{
}

void AttributeComponent::Awake()
{
    ActorComponent::Awake();
}

float AttributeComponent::OnAttributeChange(MainAttribute Attribute, float Delta)
{
    return Attributes[Attribute]->ApplyChangingValue(Delta);
}

float AttributeComponent::OnAttributeBuffChange(MainAttribute Attribute, float Percent)
{
    return Attributes[Attribute]->ApplyChangingBuff(Percent);
}

void AttributeComponent::LevelUp()
{
    for (auto& [Key, Value] : Attributes)
    {
        Value->LevelUp();
    }
}