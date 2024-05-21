#include "AttributeComponent.h"

#include <random>
#include <ranges>

#include "../../../Core/Object/Actor/Actor.h"
#include "../../../Core/Timer/Manager/TimerManager.h"

AttributeComponent::AttributeComponent(Object* Owner)
    : ActorComponent(Owner)
{
}

void AttributeComponent::Awake()
{
    ActorComponent::Awake();

    Actor* ActorOwner = static_cast<Actor*>(GetOwner());
    OnHealthChange = std::bind(&Actor::OnHealthChange, ActorOwner, std::placeholders::_1, std::placeholders::_2,
                               std::placeholders::_3);
}

float AttributeComponent::OnAttributeChange(MainAttribute Attribute, float Delta)
{
    return Attributes[Attribute]->ApplyChangingValue(Delta);
}

float AttributeComponent::OnAttributeBuffChange(MainAttribute Attribute, float Percent)
{
    return Attributes[Attribute]->ApplyChangingBuff(Percent);
}

void AttributeComponent::LevelUp()
{
    for (const auto& Value : Attributes | std::views::values)
    {
        Value->LevelUp();
    }
}

float AttributeComponent::ApplyHealthChange(std::shared_ptr<AttributeComponent> Instigator)
{
    if (!bIsEnableTakeDamage) return 0.0f;

    const std::shared_ptr<AttributeData> TargetHealth = GetAttribute(MainAttribute::Health);
    if (TargetHealth->GetCurrentValue() <= FLT_EPSILON) return 0.0f;

    bIsEnableTakeDamage = false;

    const SharedContext* Context = GetOwner()->GetContext();
    Context->TimerManagerSys->AddTimer([&]()
    {
        bIsEnableTakeDamage = true;
    }, 2.0f);

    const std::shared_ptr<AttributeData> InstigatorDamage = Instigator->GetAttribute(MainAttribute::Attack);
    const std::shared_ptr<AttributeData> CriticalChange = Instigator->GetAttribute(MainAttribute::CriticalChance);
    const std::shared_ptr<AttributeData> CriticalDamage = Instigator->GetAttribute(MainAttribute::CriticalDamage);

    std::random_device RandomDevice;
    std::mt19937 Generator(RandomDevice());
    std::uniform_real_distribution<float> Distribution(0.0f, 1.0f);

    const float ChanceToCritical = CriticalChange->GetCurrentValue() / 100.0f;
    const bool IsCritical = Distribution(Generator) <= ChanceToCritical;
    float Damage = InstigatorDamage->GetCurrentValue() * (IsCritical ? CriticalDamage->GetCurrentValue() : 1.0f);

    const std::shared_ptr<AttributeData> TargetDefense = GetAttribute(MainAttribute::Defense);

    Damage -= Damage * (TargetDefense->GetCurrentValue() / 100.0f);

    const float TakeDamage = TargetHealth->ApplyChangingValue(-Damage);

    OnHealthChange(Instigator->GetOwner(), TakeDamage, TargetHealth->GetCurrentValue() <= 0.0f);

    return TakeDamage;
}

float AttributeComponent::ApplyHealthChange(std::shared_ptr<AttributeComponent> Instigator, float Delta)
{
    if (!bIsEnableTakeDamage) return 0.0f;

    const std::shared_ptr<AttributeData> TargetHealth = GetAttribute(MainAttribute::Health);
    if (TargetHealth->GetCurrentValue() <= FLT_EPSILON) return 0.0f;

    bIsEnableTakeDamage = false;

    const SharedContext* Context = GetOwner()->GetContext();
    Context->TimerManagerSys->AddTimer([&]()
    {
        bIsEnableTakeDamage = true;
    }, 2.0f);

    const std::shared_ptr<AttributeData> CriticalChange = Instigator->GetAttribute(MainAttribute::CriticalChance);
    const std::shared_ptr<AttributeData> CriticalDamage = Instigator->GetAttribute(MainAttribute::CriticalDamage);

    std::random_device RandomDevice;
    std::mt19937 Generator(RandomDevice());
    std::uniform_real_distribution<float> Distribution(0.0f, 1.0f);

    const float ChanceToCritical = CriticalChange->GetCurrentValue() / 100.0f;
    const bool IsCritical = Distribution(Generator) <= ChanceToCritical;
    float Damage = Delta * (IsCritical ? CriticalDamage->GetCurrentValue() : 1.0f);

    const std::shared_ptr<AttributeData> TargetDefense = GetAttribute(MainAttribute::Defense);

    Damage -= Damage * (TargetDefense->GetCurrentValue() / 100.0f);

    const float TakeDamage = TargetHealth->ApplyChangingValue(-Damage);

    OnHealthChange(Instigator->GetOwner(), TakeDamage, TargetHealth->GetCurrentValue() <= 0.0f);

    return TakeDamage;
}
