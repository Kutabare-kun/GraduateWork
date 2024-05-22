#include "AbilityUpgradePowerUp.h"

#include <array>
#include <random>
#include <ranges>

#include "../../../Core/Animation/Animation.h"
#include "../../../Core/Component/Animation/AnimationComponent.h"
#include "../../../Core/Component/Collider/BoxCollider/BoxColliderComponent.h"
#include "../../../Core/Component/Sprite/SpriteComponent.h"
#include "../../../Core/Directory/Directory.h"
#include "../../../Core/Timer/Manager/TimerManager.h"
#include "../../Actors/Player/Player.h"
#include "../../Components/Ability/AbilityComponent.h"

AbilityUpgradePowerUp::AbilityUpgradePowerUp(SharedContext* Context, Object* Instigator, const Vector2& Position)
    : PowerUpBase(Context, Instigator, Position)
{
    SetName("AbilityUpgradePowerUp_");

    const auto Collider = AddComponent<BoxColliderComponent>(this);
    Collider->SetSize(80.0f, 80.0f);
    Collider->SetLayer(CollisionLayer::PowerUp);

    GetTransform()->SetScale(5.0f);
}

void AbilityUpgradePowerUp::Awake()
{
    PowerUpBase::Awake();

    GetTag()->Set(Tag::PowerUp);
    GetSprite()->SetDrawLayer(DrawLayer::PowerUp);
}

void AbilityUpgradePowerUp::CreateAnimation()
{
    // Atlas Texture
    const int UpgradeAbilityPowerUpID = GetContext()->TextureAllocator->Add(
        Directory::GetInstance().GetTexture("UpgradeAbilityPowerUpAtlas.png"));
    // ~Atlas Texture

    // Sprite Size
    constexpr int FrameWidth = 16;
    constexpr int FrameHeight = 16;
    // ~Sprite Size

    // Animation Frame Time
    constexpr float IdleAnimFrameTime = 0.15f;
    // ~Animation Frame Time

    constexpr int PowerUpYFrame{0};
    constexpr std::array<int, 8> PowerUpXFrame{0, 16, 32, 48, 64, 80, 96, 112};

    std::shared_ptr<AnimationComponent> AnimComp = GetAnimation();

    // Idle Animation
    const std::shared_ptr<Animation> RightIdleAnimation = std::make_shared<Animation>();
    RightIdleAnimation->AddFrame(UpgradeAbilityPowerUpID, PowerUpXFrame[0], PowerUpYFrame, FrameWidth, FrameHeight, 3.0f);
    for (auto XFrame : PowerUpXFrame | std::ranges::views::drop(1))
        RightIdleAnimation->AddFrame(UpgradeAbilityPowerUpID, XFrame, PowerUpYFrame, FrameWidth, FrameHeight,
                                     IdleAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Right, AnimationState::Idle, RightIdleAnimation);
    // ~Idle Animation
}

void AbilityUpgradePowerUp::OnTakePowerUp(Player* ThisPlayer)
{
    std::vector<AbilityTag> AbilityTags = ThisPlayer->GetAbility()->GetAbilities();

    std::random_device RandomDevice;
    std::mt19937 Generator(RandomDevice());
    std::uniform_int_distribution<int> Distribution(0, static_cast<int>(static_cast<int>(AbilityTags.size()) - 1));

    ThisPlayer->GetAbility()->LevelUpAbility(AbilityTags[Distribution(Generator)]);

    GetContext()->TimerManagerSys->AddTimer([&]()
    {
        QueueForRemoval();
    }, 0.0f);
}
