#include "SlimeAttribute.h"

SlimeAttribute::SlimeAttribute(Object* Owner)
    : AttributeComponent(Owner)
{
}

void SlimeAttribute::Awake()
{
    AttributeComponent::Awake();

    auto [MaxHealthIter, IsMaxHealthEmplaced] = Attributes.emplace(MainAttribute::MaxHealth,
                                                                   std::make_shared<AttributeData>(5.0f, 20.0f));
    if (IsMaxHealthEmplaced) MaxHealthIter->second->Initialize(100.0f);

    auto [HealthIter, IsHealthEmplaced] = Attributes.emplace(MainAttribute::Health,
                                                             std::make_shared<AttributeData>(5.0f, 20.0f));
    if (IsHealthEmplaced) HealthIter->second->Initialize(1.0f, 1.0f);
    if (IsHealthEmplaced) HealthIter->second->SetParent(MaxHealthIter->second);

    auto [MoveSpeedIter, IsMoveSpeedEmplaced] = Attributes.emplace(MainAttribute::MoveSpeed,
                                                                   std::make_shared<AttributeData>(5.0f, 150.0f));
    if (IsMoveSpeedEmplaced) MoveSpeedIter->second->Initialize(1.2f, 0.8f);

    auto [AttackIter, IsAttackEmplaced] = Attributes.emplace(MainAttribute::Attack,
                                                             std::make_shared<AttributeData>(5.0f, 15.0f));
    if (IsAttackEmplaced) AttackIter->second->Initialize(100.0f, 0.2f);

    auto [DefenseIter, IsDefenseEmplaced] = Attributes.emplace(MainAttribute::Defense,
                                                               std::make_shared<AttributeData>(0.1f, 1.0f));
    if (IsDefenseEmplaced) DefenseIter->second->Initialize(2.0f, 0.5f);

    auto [CriticalChanceIter, IsCriticalChanceEmplaced] = Attributes.emplace(MainAttribute::CriticalChance,
                                                                             std::make_shared<
                                                                                 AttributeData>(0.1f, 1.0f));
    if (IsCriticalChanceEmplaced) CriticalChanceIter->second->Initialize(1.0f, 0.8f);

    auto [CriticalDamageIter, IsCriticalDamageEmplaced] = Attributes.emplace(MainAttribute::CriticalDamage,
                                                                             std::make_shared<
                                                                                 AttributeData>(0.1f, 2.0f));
    if (IsCriticalDamageEmplaced) CriticalDamageIter->second->Initialize(1.0f, 0.8f);
}
