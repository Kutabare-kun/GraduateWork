#pragma once
#include "../../Object/Object.h"

class IInteractable
{
public:
    virtual void OnInteraction(Object* Other) = 0;
};
