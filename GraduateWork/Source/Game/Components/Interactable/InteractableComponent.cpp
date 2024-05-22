#include "InteractableComponent.h"

InteractableComponent::InteractableComponent(Object* Owner)
    : ActorComponent(Owner)
{
}

void InteractableComponent::OnInteraction(Object* Other)
{
}
