#pragma once
#include "../AttributeComponent.h"

class PlayerAttribute
    : public AttributeComponent
{
public:
    PlayerAttribute(Object* Owner);

    void Awake() override;
};
