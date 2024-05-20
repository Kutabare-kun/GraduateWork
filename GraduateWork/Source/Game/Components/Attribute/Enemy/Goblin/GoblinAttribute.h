#pragma once
#include "../../AttributeComponent.h"

class GoblinAttribute
    : public AttributeComponent
{
public:
    GoblinAttribute(Object* Owner);

    void Awake() override;
};
