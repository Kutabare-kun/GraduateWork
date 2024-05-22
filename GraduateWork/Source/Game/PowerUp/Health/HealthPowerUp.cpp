#include "HealthPowerUp.h"

#include <array>
#include <ranges>

#include "../../../Core/Animation/Animation.h"
#include "../../../Core/Component/Animation/AnimationComponent.h"
#include "../../../Core/Component/Collider/BoxCollider/BoxColliderComponent.h"
#include "../../../Core/Component/Sprite/SpriteComponent.h"
#include "../../../Core/Directory/Directory.h"
#include "../../../Core/Timer/Manager/TimerManager.h"
#include "../../Components/Attribute/AttributeComponent.h"
#include "../../Actors/Player/Player.h"

HealthPowerUp::HealthPowerUp(SharedContext* Context, Object* Instigator, const Vector2& Position)
    : PowerUpBase(Context, Instigator, Position)
{
    SetName("HealthPowerUp_");

    const auto Collider = AddComponent<BoxColliderComponent>(this);
    Collider->SetSize(35.0f, 50.0f);
    Collider->SetLayer(CollisionLayer::PowerUp);

    GetTransform()->SetScale(5.0f);
}

void HealthPowerUp::Awake()
{
    PowerUpBase::Awake();

    GetTag()->Set(Tag::PowerUp);
    GetSprite()->SetDrawLayer(DrawLayer::PowerUp);
}

void HealthPowerUp::CreateAnimation()
{
    // Atlas Texture
    const int HealthPowerUpID = GetContext()->TextureAllocator->Add(
        Directory::GetInstance().GetTexture("HealthPowerUpAtlas.png"));
    // ~Atlas Texture

    // Sprite Size
    constexpr int FrameWidth = 7;
    constexpr int FrameHeight = 10;
    // ~Sprite Size

    // Animation Frame Time
    constexpr float IdleAnimFrameTime = 0.15f;
    // ~Animation Frame Time

    constexpr int PowerUpYFrame{0};
    constexpr std::array<int, 7> PowerUpXFrame{0, 7, 14, 21, 28, 35, 42};

    std::shared_ptr<AnimationComponent> AnimComp = GetAnimation();

    // Idle Animation
    const std::shared_ptr<Animation> RightIdleAnimation = std::make_shared<Animation>();
    RightIdleAnimation->AddFrame(HealthPowerUpID, PowerUpXFrame[0], PowerUpYFrame, FrameWidth, FrameHeight, 3.0f);
    for (auto XFrame : PowerUpXFrame | std::views::drop(1))
        RightIdleAnimation->AddFrame(HealthPowerUpID, XFrame, PowerUpYFrame, FrameWidth, FrameHeight,
                                     IdleAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Right, AnimationState::Idle, RightIdleAnimation);
    // ~Idle Animation
}

void HealthPowerUp::OnTakePowerUp(Player* ThisPlayer)
{
    const float Heal = ThisPlayer->GetAttributeComp()->ApplyHeal(HealthValue, HealthByPercent);
    if (Heal <= FLT_EPSILON) return;

    GetContext()->TimerManagerSys->AddTimer([&]()
    {
        if (this) QueueForRemoval();
    }, 0.0f);
}
