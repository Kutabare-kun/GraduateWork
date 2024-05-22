#include "SlimeEnemy.h"

#include <array>

#include "../../../../Core/Animation/Animation.h"
#include "../../../../Core/Component/Animation/AnimationComponent.h"
#include "../../../../Core/Component/Collider/BoxCollider/BoxColliderComponent.h"
#include "../../../Components/Attribute/AttributeComponent.h"
#include "../../../../Core/Directory/Directory.h"

class Animation;

SlimeEnemy::SlimeEnemy(SharedContext* Context, Object* Instigator, const Vector2& Position)
    : Enemy(Context, Instigator, Position)
{
    SetName("Slime_");

    const auto Collider = AddComponent<BoxColliderComponent>(this);
    Collider->SetSize(80.0f, 64.0f);
    Collider->SetLayer(CollisionLayer::Enemy);

    AttributeComp = AddComponent<AttributeComponent>(this);
    AddComponent<MovementComponent>(this, 200.0f);

    GetTransform()->SetScale(5.0f);
}

void SlimeEnemy::CreateAnimation()
{
    // Atlas Texture
    const int SlimeID = GetContext()->TextureAllocator->Add(Directory::GetInstance().GetTexture("SlimeAtlas.png"));
    // ~Atlas Texture

    // Sprite Size
    constexpr int FrameWidth = 16;
    constexpr int FrameHeight = 12;
    // ~Sprite Size

    // Animation Frame Time
    constexpr float IdleAnimFrameTime = 0.2f;
    constexpr float WalkAnimFrameTime = 0.15f;
    // ~Animation Frame Time

    constexpr std::array<int, 4> SlimeYFrame{3, 19, 35, 51};
    constexpr std::array<int, 6> SlimeXFrame{0, 16, 32, 48, 64, 80};

    std::shared_ptr<AnimationComponent> AnimComp = GetAnimation();

    // Idle Animation
    const std::shared_ptr<Animation> RightIdleAnimation = std::make_shared<Animation>();
    for (auto XFrame : SlimeXFrame)
        RightIdleAnimation->AddFrame(SlimeID, XFrame, SlimeYFrame[0], FrameWidth, FrameHeight, IdleAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Right, AnimationState::Idle, RightIdleAnimation);

    const std::shared_ptr<Animation> LeftIdleAnimation = std::make_shared<Animation>();
    for (auto XFrame : SlimeXFrame)
        LeftIdleAnimation->AddFrame(SlimeID, XFrame, SlimeYFrame[1], FrameWidth, FrameHeight, IdleAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Left, AnimationState::Idle, LeftIdleAnimation);
    // ~Idle Animation

    // Walk Animation
    const std::shared_ptr<Animation> RightWalkAnimation = std::make_shared<Animation>();
    for (auto XFrame : SlimeXFrame)
        RightWalkAnimation->AddFrame(SlimeID, XFrame, SlimeYFrame[2], FrameWidth, FrameHeight, WalkAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Right, AnimationState::Walk, RightWalkAnimation);

    const std::shared_ptr<Animation> LeftWalkAnimation = std::make_shared<Animation>();
    for (auto XFrame : SlimeXFrame)
        LeftWalkAnimation->AddFrame(SlimeID, XFrame, SlimeYFrame[3], FrameWidth, FrameHeight, WalkAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Left, AnimationState::Walk, LeftWalkAnimation);
    // ~Walk Animation
}
