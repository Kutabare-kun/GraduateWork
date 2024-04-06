#pragma once
#include <memory>

#include "../../../Core/Component/ActorComponent.h"
#include "../../../Core/Component/Movement/MovementComponent.h"

class InteractComponent
    : public ActorComponent
{
public:
    InteractComponent(Object* Owner);

    void Awake() override;

    void Update(float DeltaTime) override;

private:
    std::shared_ptr<MovementComponent> Direction;

    float InteractDistance;
};
