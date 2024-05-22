#include "PlayerAttribute.h"

#include "../../../../Core/Object/Object.h"
#include "../../../../Core/Timer/Manager/TimerManager.h"
#include "../../../../Core/UI/Bar/UIBar.h"
#include "../../../UI/HUD/PlayerHUD.h"
#include "../../../UI/Widgets/GameUI/GameUI.h"

PlayerAttribute::PlayerAttribute(Object* Owner)
    : AttributeComponent(Owner)
{
}

void PlayerAttribute::Awake()
{
    AttributeComponent::Awake();

    auto [MaxHealthIter, IsMaxHealthEmplaced] = Attributes.emplace(MainAttribute::MaxHealth,
                                                                   std::make_shared<AttributeData>(5.0f, 100.0f));
    if (IsMaxHealthEmplaced) MaxHealthIter->second->Initialize(100.0f);

    auto [HealthIter, IsHealthEmplaced] = Attributes.emplace(MainAttribute::Health,
                                                             std::make_shared<AttributeData>(5.0f, 100.0f));
    if (IsHealthEmplaced) HealthIter->second->Initialize(1.0f, 1.0f);
    if (IsHealthEmplaced) HealthIter->second->SetParent(MaxHealthIter->second);

    auto [MoveSpeedIter, IsMoveSpeedEmplaced] = Attributes.emplace(MainAttribute::MoveSpeed,
                                                                   std::make_shared<AttributeData>(5.0f, 800.0f));
    if (IsMoveSpeedEmplaced) MoveSpeedIter->second->Initialize(1.2f, 0.8f);

    auto [AttackIter, IsAttackEmplaced] = Attributes.emplace(MainAttribute::Attack,
                                                             std::make_shared<AttributeData>(5.0f, 20.0f));
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
