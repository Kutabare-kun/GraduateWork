#pragma once
#include <map>
#include <memory>
#include <string>

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

    void AddAbility(std::shared_ptr<AbilityContext> NewAbility);
    void AddAbility(const std::string& AbilityName, AbilityTag Tag);

protected:
    void SpawnAbility(std::shared_ptr<AbilityContext>& AbilityInfo);

private:
    std::map<AbilityTag, std::shared_ptr<AbilityContext>> Abilities;
};
