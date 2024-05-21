#pragma once
#include <map>
#include <memory>

#include "../../../Core/Component/ActorComponent.h"

class AbilityContext;

enum class AbilityTag
{
    Slash,
    Shuriken,
};

class AbilityComponent
    : public ActorComponent
{
public:
    AbilityComponent(Object* Owner);

    void Awake() override;

    void AddAbility(std::shared_ptr<AbilityContext> NewAbility);

private:
    std::map<AbilityTag, std::shared_ptr<AbilityContext>> Abilities;
};
