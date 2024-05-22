#include "AttributeComponent.h"

#include <fstream>
#include <random>
#include <ranges>

#include "../../../Core/Directory/Directory.h"
#include "../../../Core/Object/Actor/Actor.h"
#include "../../../Core/Timer/Manager/TimerManager.h"
#include "../../../Core/UI/Bar/UIBar.h"
#include "../../UI/HUD/PlayerHUD.h"
#include "../../UI/Widgets/GameUI/GameUI.h"

using Json = nlohmann::json;

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

    std::string Name = GetOwner()->GetName();
    Name.erase(Name.find('_'));

    Json WaveInfoJson;
    std::ifstream WaveInfoFile(Directory::GetInstance().GetData("Attribute.json"));
    WaveInfoFile >> WaveInfoJson;

    auto AttributeInfo = WaveInfoJson[Name];
    auto Info = AttributeInfo["Attribute"];

    auto ThisValue = Info["MaxHealth"].get<Attribute>();

    auto [MaxHealthIter, IsMaxHealthEmplaced] = Attributes.emplace(MainAttribute::MaxHealth,
                                                                   std::make_shared<AttributeData>(
                                                                       ThisValue.Increase, ThisValue.Base));
    if (IsMaxHealthEmplaced) MaxHealthIter->second->Initialize(ThisValue.MaxPercent, ThisValue.MinPercent);

    ThisValue = Info["Health"].get<Attribute>();

    auto [HealthIter, IsHealthEmplaced] = Attributes.emplace(MainAttribute::Health,
                                                             std::make_shared<AttributeData>(
                                                                 ThisValue.Increase, ThisValue.Base));
    if (IsHealthEmplaced) HealthIter->second->Initialize(ThisValue.MaxPercent, ThisValue.MinPercent);
    if (IsHealthEmplaced) HealthIter->second->SetParent(MaxHealthIter->second);

    ThisValue = Info["MoveSpeed"].get<Attribute>();

    auto [MoveSpeedIter, IsMoveSpeedEmplaced] = Attributes.emplace(MainAttribute::MoveSpeed,
                                                                   std::make_shared<AttributeData>(
                                                                       ThisValue.Increase, ThisValue.Base));
    if (IsMoveSpeedEmplaced) MoveSpeedIter->second->Initialize(ThisValue.MaxPercent, ThisValue.MinPercent);

    ThisValue = Info["Attack"].get<Attribute>();

    auto [AttackIter, IsAttackEmplaced] = Attributes.emplace(MainAttribute::Attack,
                                                             std::make_shared<AttributeData>(
                                                                 ThisValue.Increase, ThisValue.Base));
    if (IsAttackEmplaced) AttackIter->second->Initialize(ThisValue.MaxPercent, ThisValue.MinPercent);

    ThisValue = Info["Defence"].get<Attribute>();

    auto [DefenseIter, IsDefenseEmplaced] = Attributes.emplace(MainAttribute::Defense,
                                                               std::make_shared<AttributeData>(
                                                                   ThisValue.Increase, ThisValue.Base));
    if (IsDefenseEmplaced) DefenseIter->second->Initialize(ThisValue.MaxPercent, ThisValue.MinPercent);

    ThisValue = Info["CriticalChance"].get<Attribute>();

    auto [CriticalChanceIter, IsCriticalChanceEmplaced] = Attributes.emplace(MainAttribute::CriticalChance,
                                                                             std::make_shared<
                                                                                 AttributeData>(
                                                                                 ThisValue.Increase, ThisValue.Base));
    if (IsCriticalChanceEmplaced) CriticalChanceIter->second->Initialize(ThisValue.MaxPercent, ThisValue.MinPercent);

    ThisValue = Info["CriticalDamage"].get<Attribute>();

    auto [CriticalDamageIter, IsCriticalDamageEmplaced] = Attributes.emplace(MainAttribute::CriticalDamage,
                                                                             std::make_shared<
                                                                                 AttributeData>(
                                                                                 ThisValue.Increase, ThisValue.Base));
    if (IsCriticalDamageEmplaced) CriticalDamageIter->second->Initialize(ThisValue.MaxPercent, ThisValue.MinPercent);

    if (!GetOwner()->GetTag()->Compare(Tag::Player)) return;

    // UI
    GetOwner()->GetContext()->TimerManagerSys->AddTimer([&]()
    {
        std::shared_ptr<PlayerHUD> HUD = GetOwner()->GetComponent<PlayerHUD>();
        std::shared_ptr<GameUI> GameUI = HUD->GetGameUIWidget();
        std::shared_ptr<UIBar> HealthBar = GameUI->GetHealthBar();

        OnHealthChangeUI = std::bind(&UIBar::UpdatePercentage, HealthBar, std::placeholders::_1);
    }, 1.0f);
    // ~UI
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
    }, TimeHealthChange);

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
    if (GetOwner()->GetTag()->Compare(Tag::Player))
    {
        const std::shared_ptr<AttributeData> TargetMaxHealth = GetAttribute(MainAttribute::MaxHealth);
        OnHealthChangeUI(TargetHealth->GetCurrentValue() / TargetMaxHealth->GetCurrentValue());
    }
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
    }, TimeHealthChange);

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
    if (GetOwner()->GetTag()->Compare(Tag::Player))
    {
        const std::shared_ptr<AttributeData> TargetMaxHealth = GetAttribute(MainAttribute::MaxHealth);
        OnHealthChangeUI(TargetHealth->GetCurrentValue() / TargetMaxHealth->GetCurrentValue());
    }
    return TakeDamage;
}

float AttributeComponent::ApplyHeal(float Delta, float Percent)
{
    const std::shared_ptr<AttributeData> TargetHealth = GetAttribute(MainAttribute::Health);
    if (TargetHealth->GetCurrentValue() <= FLT_EPSILON) return 0.0f;

    const std::shared_ptr<AttributeData> TargetMaxHealth = GetAttribute(MainAttribute::MaxHealth);
    const float Heal = TargetHealth->ApplyChangingValue(Delta + TargetMaxHealth->GetCurrentValue() * Percent);

    OnHealthChange(nullptr, Heal, TargetHealth->GetCurrentValue() <= 0.0f);
    if (GetOwner()->GetTag()->Compare(Tag::Player))
    {
        const std::shared_ptr<AttributeData> TargetMaxHealth = GetAttribute(MainAttribute::MaxHealth);
        OnHealthChangeUI(TargetHealth->GetCurrentValue() / TargetMaxHealth->GetCurrentValue());
    }
    return Heal;
}
