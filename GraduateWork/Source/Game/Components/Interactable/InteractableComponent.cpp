#include "InteractableComponent.h"

#include "../../../Core/StaticFunctions/Debug.h"

InteractableComponent::InteractableComponent(Object* Owner)
    : ActorComponent(Owner)
{
}

void InteractableComponent::OnInteraction(Object* Other)
{
    Debug::GetInstance().Log(TextFormat("[%s] Interacted with [%s]", Other->GetName().c_str(), GetOwner()->GetName().c_str()));
}
