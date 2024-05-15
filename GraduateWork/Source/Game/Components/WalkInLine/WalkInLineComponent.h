#pragma once
#include "../../../Core/Component/ActorComponent.h"
#include "../../../Core/Component/Velocity/VelocityComponent.h"
#include "../Interactable/InteractableComponent.h"

class WalkInLineComponent
    : public ActorComponent, public IInteractable
{
public:
    explicit WalkInLineComponent(class Object* NewOwner, float NewMoveSpeed = 100.0f);

    void Awake() override;

    void OnInteraction(Object* Other) override;

private:
    std::shared_ptr<VelocityComponent> Velocity;
    float MoveSpeed;
};
