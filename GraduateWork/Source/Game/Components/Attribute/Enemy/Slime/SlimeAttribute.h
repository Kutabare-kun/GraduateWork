#pragma once
#include "../../AttributeComponent.h"

class SlimeAttribute
    : public AttributeComponent
{
public:
    SlimeAttribute(Object* Owner);

    void Awake() override;
};
