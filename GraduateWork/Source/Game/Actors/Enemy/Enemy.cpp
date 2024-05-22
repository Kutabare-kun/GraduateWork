#include "Enemy.h"

#include "../../../Core/Collection/ObjectCollection.h"
#include "../../../Core/Component/Velocity/VelocityComponent.h"
#include "../../Components/BehaviorTree/Simple/BehaviorTreeSimple.h"
#include "../../../Core/Component/Sprite/SpriteComponent.h"
#include "../../../Core/Timer/Manager/TimerManager.h"
#include "../../UI/HUD/PlayerHUD.h"
#include "../../UI/Widgets/PopUp/PopUpDamage.h"
#include "../Player/Player.h"

Enemy::Enemy(SharedContext* Context, Object* Instigator, const Vector2& Position)
    : Actor(Context, Instigator, Position), BehaviorTreeComp(nullptr)
{
    SetName("Enemy_");

    BehaviorTreeComp = AddComponent<BehaviorTreeSimple>(this);
}

void Enemy::Awake()
{
    Actor::Awake();

    GetTag()->Set(Tag::Enemy);
    GetSprite()->SetDrawLayer(DrawLayer::Entities);

    auto BBS = std::dynamic_pointer_cast<BlackboardSimple>(BehaviorTreeComp->GetBlackboard());
    if (!BBS) return;

    BBS->Target = GetContext()->Objects->GetObject<Player>().get();
}

void Enemy::OnHealthChange(Object* Instigator, float Delta, bool IsDead)
{
    std::shared_ptr<PlayerHUD> HUD = Instigator->GetComponent<PlayerHUD>();
    if (HUD)
    {
        const Vector2 EnemyPos = GetTransform()->GetPosition();

        Slot PopUpSlot{
            Padding{0.0f},
            Crop{0.0f},
            Rectangle{EnemyPos.x, EnemyPos.y, 200.0f, 80.0f}
        };

        std::shared_ptr<PopUpDamage> UIDamage = std::make_shared<PopUpDamage>(Instigator, PopUpSlot, nullptr, Delta);
        HUD->Add(UIDamage);
    }

    if (IsDead)
    {
        GetContext()->TimerManagerSys->AddTimer([&]()
        {
            QueueForRemoval();
        }, 0.0f);
    }
}
