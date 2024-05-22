#pragma once
#include <functional>
#include <map>
#include <memory>

#include "../../../Core/Component/ActorComponent.h"
#include "Data/AttributeData.h"

enum class MainAttribute
{
    Health,
    MaxHealth,

    MoveSpeed,

    Attack,
    Defense,

    CriticalChance,
    CriticalDamage
};

class AttributeComponent
    : public ActorComponent
{
public:
    AttributeComponent(Object* Owner);

    void Awake() override;

    void LevelUp();

    float ApplyHealthChange(std::shared_ptr<AttributeComponent> Instigator);
    float ApplyHealthChange(std::shared_ptr<AttributeComponent> Instigator, float Delta);
    float ApplyHeal(float Delta, float Percent = 0.0f);

    float OnAttributeChange(MainAttribute Attribute, float Delta);
    float OnAttributeBuffChange(MainAttribute Attribute, float Percent);

    std::shared_ptr<AttributeData> GetAttribute(MainAttribute Attribute = MainAttribute::Health) { return Attributes[Attribute]; }

protected:
    std::map<MainAttribute, std::shared_ptr<AttributeData>> Attributes;

    bool bIsEnableTakeDamage = true;

    float TimeHealthChange = 0.2f;

    std::function<void(Object*, float, bool)> OnHealthChange;
    std::function<void(float)> OnHealthChangeUI;
};
