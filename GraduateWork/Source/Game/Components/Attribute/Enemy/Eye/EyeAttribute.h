#pragma once
#include "../../AttributeComponent.h"

class EyeAttribute
    : public AttributeComponent
{
public:
    EyeAttribute(Object* Owner);

    void Awake() override;
};
