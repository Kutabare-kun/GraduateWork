#pragma once
#include "../ActorComponent.h"

class InstanceIDComponent
    : public ActorComponent
{
public:
    InstanceIDComponent(Object* Owner);
    ~InstanceIDComponent() override;

    unsigned int GetID() const;

private:
    static unsigned int InstanceCounter;
    unsigned int InstanceID;
};
