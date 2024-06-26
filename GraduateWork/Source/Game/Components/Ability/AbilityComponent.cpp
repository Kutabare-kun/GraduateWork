#include "AbilityComponent.h"

#include "../../../Core/Collection/ObjectCollection.h"
#include "../../../Core/Timer/Manager/TimerManager.h"
#include "Ability/Shuriken/ShurikenAbility.h"
#include "AbilityContext/AbilityContext.h"

AbilityComponent::AbilityComponent(Object* Owner)
    : ActorComponent(Owner)
{
}

void AbilityComponent::AddAbility(std::shared_ptr<AbilityContext> NewAbility)
{
    auto Iter = Abilities.emplace(NewAbility->GetAbilityTag(), NewAbility);
    std::shared_ptr<AbilityContext>& ThisAbility = Iter.first->second;

    const float Cooldown = NewAbility->GetInfo().Cooldown;

    std::shared_ptr<Timer> AbilityTimer = GetOwner()->GetContext()->TimerManagerSys->AddTimer([&]()
    {
        this->SpawnAbility(ThisAbility);
    }, Cooldown, true);

    NewAbility->SetAbilityTimer(AbilityTimer);
}

std::vector<AbilityTag> AbilityComponent::GetAbilities() const
{
    std::vector<AbilityTag> AbilityTags;
    for (auto& Key : Abilities | std::views::keys)
    {
        AbilityTags.emplace_back(Key);
    }

    return AbilityTags;
}

void AbilityComponent::AddAbility(const std::string& AbilityName, AbilityTag Tag)
{
    std::shared_ptr<AbilityContext> ThisAbilityContext = std::make_shared<AbilityContext>(std::move(AbilityName), Tag);
    AddAbility(ThisAbilityContext);
}

void AbilityComponent::LevelUpAbility(AbilityTag Tag)
{
    Abilities[Tag]->LevelUp();
}

void AbilityComponent::SpawnAbility(std::shared_ptr<AbilityContext>& AbilityInfo)
{
    if (!GetOwner()) return;
    SharedContext* ThisContext = GetOwner()->GetContext();

    const Vector2 Position = GetOwner()->GetTransform()->GetPosition();
    switch (AbilityInfo->GetAbilityTag())
    {
    case AbilityTag::Slash:
        {
            //Context->Objects->CreateObject<Ability>(ThisContext, GetOwner(), Position, NewAbility->GetInfo().Damage);
        }
        break;
    case AbilityTag::Shuriken:
        {
            ThisContext->Objects->CreateObject<ShurikenAbility>(&*ThisContext, GetOwner(), Position,
                                                                AbilityInfo->GetInfo().Damage);
        }
    }
}
