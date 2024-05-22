#include "Player.h"

#include <array>

#include "../../../Core/Animation/Animation.h"
#include "../../../Core/Component/Movement/MovementComponent.h"
#include "../../../Core/Component/Sprite/SpriteComponent.h"
#include "../../../Core/Directory/Directory.h"
#include "../../../Core/Component/Animation/AnimationComponent.h"
#include "../../../Core/Component/Camera/CameraComponent.h"
#include "../../../Core/Component/Collider/BoxCollider/BoxColliderComponent.h"
#include "../../../Core/StaticFunctions/Debug.h"
#include "../../Components/Ability/AbilityComponent.h"
#include "../../Components/Ability/AbilityContext/AbilityContext.h"
#include "../../Components/Attribute/Player/PlayerAttribute.h"
#include "../../UI/HUD/PlayerHUD.h"
#include "../Enemy/Enemy.h"

Player::Player(SharedContext* Context, Object* Instigator, const Vector2& Position)
    : Actor(Context, Instigator, Position)
{
    SetName("Player_");

    CameraComp = AddComponent<CameraComponent>(this);
    CameraComp->UpdateZoom(0.5f);

    AddComponent<InteractComponent>(this);

    const auto Collider = AddComponent<BoxColliderComponent>(this);
    Collider->SetSize(85.0f, 100.0f);
    Collider->SetLayer(CollisionLayer::Player);

    AddComponent<PlayerHUD>(this);
    AttributeComp = AddComponent<PlayerAttribute>(this);
    MovementComp = AddComponent<MovementComponent>(this);

    AbilityComp = AddComponent<AbilityComponent>(this);

    GetTransform()->SetScale(7.0f);
}

void Player::CreateAnimation()
{
    // Atlas Texture
    const int KnightID = GetContext()->TextureAllocator->Add(Directory::GetInstance().GetTexture("KnightAtlas.png"));
    // ~Atlas Texture

    // Sprite Size
    constexpr int FrameWidth = 13;
    constexpr int FrameHeight = 16;
    // ~Sprite Size

    // Animation Frame Time
    constexpr float IdleAnimFrameTime = 0.2f;
    constexpr float WalkAnimFrameTime = 0.15f;
    // ~Animation Frame Time

    constexpr std::array<int, 4> KnightYFrame{0, 16, 32, 48};
    constexpr std::array<int, 6> KnightXFrame{2, 18, 34, 50, 66, 82};

    std::shared_ptr<AnimationComponent> AnimComp = GetAnimation();

    // Idle Animation
    const std::shared_ptr<Animation> RightIdleAnimation = std::make_shared<Animation>();
    for (auto XFrame : KnightXFrame)
        RightIdleAnimation->AddFrame(KnightID, XFrame, KnightYFrame[0], FrameWidth, FrameHeight, IdleAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Right, AnimationState::Idle, RightIdleAnimation);

    const std::shared_ptr<Animation> LeftIdleAnimation = std::make_shared<Animation>();
    for (auto XFrame : KnightXFrame)
        LeftIdleAnimation->AddFrame(KnightID, XFrame, KnightYFrame[1], FrameWidth, FrameHeight, IdleAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Left, AnimationState::Idle, LeftIdleAnimation);
    // ~Idle Animation

    // Walk Animation
    const std::shared_ptr<Animation> RightWalkAnimation = std::make_shared<Animation>();
    for (auto XFrame : KnightXFrame)
        RightWalkAnimation->AddFrame(KnightID, XFrame, KnightYFrame[2], FrameWidth, FrameHeight, WalkAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Right, AnimationState::Walk, RightWalkAnimation);

    const std::shared_ptr<Animation> LeftWalkAnimation = std::make_shared<Animation>();
    for (auto XFrame : KnightXFrame)
        LeftWalkAnimation->AddFrame(KnightID, XFrame, KnightYFrame[3], FrameWidth, FrameHeight, WalkAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Left, AnimationState::Walk, LeftWalkAnimation);
    // ~Walk Animation
}

void Player::Awake()
{
    Actor::Awake();

    GetTag()->Set(Tag::Player);
    GetSprite()->SetDrawLayer(DrawLayer::Entities);

    AbilityComp->AddAbility("Shuriken", AbilityTag::Shuriken);
}

void Player::HandleDamage(std::shared_ptr<ColliderComponent> Other) const
{
    if (const Object* Instigator = Other->GetOwner();
        Instigator->GetTag()->Compare(Tag::Enemy))
    {
        const Enemy* InstigatorEnemy = static_cast<const Enemy*>(Instigator);
        if (!InstigatorEnemy || !InstigatorEnemy->GetAttributeComp()) return;

        AttributeComp->ApplyHealthChange(InstigatorEnemy->GetAttributeComp());
    }
}

void Player::OnCollisionBeginOverlap(std::shared_ptr<ColliderComponent> Other)
{
    Actor::OnCollisionBeginOverlap(Other);

    HandleDamage(Other);
}

void Player::OnCollisionStayOverlap(std::shared_ptr<ColliderComponent> Other)
{
    Actor::OnCollisionStayOverlap(Other);

    HandleDamage(Other);
}

void Player::OnHealthChange(Object* Instigator, float Delta, bool IsDead)
{
    if (IsDead) Debug::GetInstance().Log(TextFormat("Player DEAD!"));
}
