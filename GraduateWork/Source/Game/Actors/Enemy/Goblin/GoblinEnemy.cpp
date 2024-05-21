#include "GoblinEnemy.h"

#include <array>

#include "../../../../Core/Animation/Animation.h"
#include "../../../../Core/Component/Animation/AnimationComponent.h"
#include "../../../../Core/Component/Collider/BoxCollider/BoxColliderComponent.h"
#include "../../../../Core/Directory/Directory.h"
#include "../../../Components/Attribute/Enemy/Goblin/GoblinAttribute.h"

GoblinEnemy::GoblinEnemy(SharedContext* Context, Object* Instigator, const Vector2& Position)
    : Enemy(Context, Instigator, Position)
{
    SetName("Goblin_");

    const auto Collider = AddComponent<BoxColliderComponent>(this);
    Collider->SetSize(66.0f, 70.0f);
    Collider->SetLayer(CollisionLayer::Enemy);

    AttributeComp = AddComponent<GoblinAttribute>(this);
    AddComponent<MovementComponent>(this, 200.0f);

    GetTransform()->SetScale(5.0f);
}

void GoblinEnemy::CreateAnimation()
{
    // Atlas Texture
    const int GoblinID = GetContext()->TextureAllocator->Add(Directory::GetInstance().GetTexture("GoblinAtlas.png"));
    // ~Atlas Texture

    // Sprite Size
    constexpr int FrameWidth = 13;
    constexpr int FrameHeight = 16;
    // ~Sprite Size

    // Animation Frame Time
    constexpr float IdleAnimFrameTime = 0.2f;
    constexpr float WalkAnimFrameTime = 0.15f;
    // ~Animation Frame Time

    constexpr std::array<int, 4> GoblinYFrame{0, 16, 32, 48};
    constexpr std::array<int, 6> GoblinXFrame{2, 18, 34, 50, 66, 82};

    std::shared_ptr<AnimationComponent> AnimComp = GetAnimation();

    // Idle Animation
    const std::shared_ptr<Animation> RightIdleAnimation = std::make_shared<Animation>();
    for (auto XFrame : GoblinXFrame)
        RightIdleAnimation->AddFrame(GoblinID, XFrame, GoblinYFrame[0], FrameWidth, FrameHeight, IdleAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Right, AnimationState::Idle, RightIdleAnimation);

    const std::shared_ptr<Animation> LeftIdleAnimation = std::make_shared<Animation>();
    for (auto XFrame : GoblinXFrame)
        LeftIdleAnimation->AddFrame(GoblinID, XFrame, GoblinYFrame[1], FrameWidth, FrameHeight, IdleAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Left, AnimationState::Idle, LeftIdleAnimation);
    // ~Idle Animation

    // Walk Animation
    const std::shared_ptr<Animation> RightWalkAnimation = std::make_shared<Animation>();
    for (auto XFrame : GoblinXFrame)
        RightWalkAnimation->AddFrame(GoblinID, XFrame, GoblinYFrame[2], FrameWidth, FrameHeight, WalkAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Right, AnimationState::Walk, RightWalkAnimation);

    const std::shared_ptr<Animation> LeftWalkAnimation = std::make_shared<Animation>();
    for (auto XFrame : GoblinXFrame)
        LeftWalkAnimation->AddFrame(GoblinID, XFrame, GoblinYFrame[3], FrameWidth, FrameHeight, WalkAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Left, AnimationState::Walk, LeftWalkAnimation);
    // ~Walk Animation
}
