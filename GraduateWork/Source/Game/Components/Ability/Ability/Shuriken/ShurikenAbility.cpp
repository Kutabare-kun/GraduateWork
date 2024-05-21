#include "ShurikenAbility.h"

#include <array>
#include <raymath.h>

#include "../../../../../Core/Animation/Animation.h"
#include "../../../../../Core/Component/Animation/AnimationComponent.h"
#include "../../../../../Core/Component/Collider/BoxCollider/BoxColliderComponent.h"
#include "../../../../../Core/Component/Velocity/VelocityComponent.h"
#include "../../../../../Core/Directory/Directory.h"
#include "../../../../../Core/StaticFunctions/Debug.h"
#include "../../../../../Core/Timer/Manager/TimerManager.h"
#include "../../../../Actors/Enemy/Enemy.h"
#include "../../../Attribute/AttributeComponent.h"

class Animation;

ShurikenAbility::ShurikenAbility(SharedContext* Context, Object* Instigator, const Vector2& Position, float Damage)
    : Ability(Context, Instigator, Position, Damage)
{
    const auto Collider = AddComponent<BoxColliderComponent>(this);
    Collider->SetSize(75.0f, 75.0f);
    Collider->SetLayer(CollisionLayer::Ability);

    VelocityComp = AddComponent<VelocityComponent>(this);

    GetTransform()->SetScale(5.0f);
}

void ShurikenAbility::Awake()
{
    Ability::Awake();

    GetContext()->TimerManagerSys->AddTimer([this]()
    {
        QueueForRemoval();
    }, 5.0f, false);

    const Vector2 OwnerPosition = GetTransform()->GetPosition();
    const Vector2 MousePosition = GetScreenToWorld2D(GetMousePosition(), *GetContext()->Camera);
    const Vector2 Direction = Vector2Subtract(MousePosition, OwnerPosition);
    const Vector2 NormalizedDirection = Vector2Normalize(Direction);

    VelocityComp->SetVelocity(Vector2Scale(NormalizedDirection, Speed));

    Debug::GetInstance().Log(TextFormat("Direction: %f, %f", NormalizedDirection.x, NormalizedDirection.y));
}

void ShurikenAbility::OnEveryHit(Enemy* Target)
{
    Ability::OnEveryHit(Target);

    std::shared_ptr<AttributeComponent> TargetAttributeComp = Target->GetAttributeComp();
    if (!TargetAttributeComp) return;

    if (!GetInstigator()) return;

    std::shared_ptr<AttributeComponent> InstigatorAttributeComp = GetInstigator()->GetComponent<AttributeComponent>();
    if (!InstigatorAttributeComp) return;

    TargetAttributeComp->ApplyHealthChange(InstigatorAttributeComp, Damage);
}

void ShurikenAbility::CreateAnimation()
{
    // Atlas Texture
    const int ShurikenID = GetContext()->TextureAllocator->
                                         Add(Directory::GetInstance().GetTexture("ShurikenAtlas.png"));
    // ~Atlas Texture

    // Sprite Size
    constexpr int FrameWidth = 15;
    constexpr int FrameHeight = 15;
    // ~Sprite Size

    // Animation Frame Time
    constexpr float IdleAnimFrameTime = 0.2f;
    // ~Animation Frame Time

    constexpr int ShurikenYFrame{};
    constexpr std::array<int, 4> ShurikenXFrame{0, 15, 30, 45};

    std::shared_ptr<AnimationComponent> AnimComp = GetAnimation();

    // Idle Animation
    const std::shared_ptr<Animation> RightIdleAnimation = std::make_shared<Animation>();
    for (auto XFrame : ShurikenXFrame)
        RightIdleAnimation->AddFrame(ShurikenID, XFrame, ShurikenYFrame, FrameWidth, FrameHeight, IdleAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Right, AnimationState::Idle, RightIdleAnimation);

    const std::shared_ptr<Animation> LeftIdleAnimation = std::make_shared<Animation>();
    for (auto XFrame : ShurikenXFrame)
        LeftIdleAnimation->AddFrame(ShurikenID, XFrame, ShurikenYFrame, FrameWidth, FrameHeight, IdleAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Left, AnimationState::Idle, LeftIdleAnimation);
    // ~Idle Animation
}
