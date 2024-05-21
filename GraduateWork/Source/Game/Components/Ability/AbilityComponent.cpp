#include "AbilityComponent.h"

#include "../../../Core/Collection/ObjectCollection.h"
#include "../../../Core/Timer/Manager/TimerManager.h"
#include "Ability/Shuriken/ShurikenAbility.h"
#include "AbilityContext/AbilityContext.h"

AbilityComponent::AbilityComponent(Object* Owner)
    : ActorComponent(Owner)
{
}

void AbilityComponent::Awake()
{
    ActorComponent::Awake();
}

void AbilityComponent::AddAbility(std::shared_ptr<AbilityContext> NewAbility)
{
    Abilities.emplace(NewAbility->GetAbilityTag(), NewAbility);
    SharedContext* Context = GetOwner()->GetContext();
    TimerManager* TimerManagerSys = Context->TimerManagerSys;

    const float Cooldown = NewAbility->GetInfo().Cooldown;

    std::shared_ptr<Timer> AbilityTimer = TimerManagerSys->AddTimer([&]()
    {
        if (!GetOwner()) return;

        const Vector2 Position = GetOwner()->GetTransform()->GetPosition();
        switch (NewAbility->GetAbilityTag())
        {
        case AbilityTag::Slash:
            {
                //Context->Objects->CreateObject<Ability>(Context, GetOwner(), Position, NewAbility->GetInfo().Damage);
            }
            break;
        case AbilityTag::Shuriken:
            {
                Context->Objects->CreateObject<ShurikenAbility>(Context, GetOwner(), Position, NewAbility->GetInfo().Damage);
            }
        }
    }, Cooldown, true);

    NewAbility->SetAbilityTimer(AbilityTimer);
}
