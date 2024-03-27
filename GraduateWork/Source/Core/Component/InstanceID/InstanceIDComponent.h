#pragma once
#include "../ActorComponent.h"

class InstanceIDComponent
    : public ActorComponent
{
public:
    InstanceIDComponent(Object* Owner);
    ~InstanceIDComponent() override;

    int GetInstanceID() const;

private:
    static int InstanceCounter;
    int InstanceID;
};
