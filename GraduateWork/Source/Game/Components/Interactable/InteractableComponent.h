#pragma once
#include "../../../Core/Component/ActorComponent.h"
#include "../../../Core/Interface/Iteractable/IInteractable.h"

class InteractableComponent
    : public ActorComponent, public IInteractable
{
public:
    InteractableComponent(Object* Owner);

    void OnInteraction(Object* Other) override;
};
