#include "EyeEnemy.h"

#include <array>

#include "../../../../Core/Animation/Animation.h"
#include "../../../../Core/Component/Animation/AnimationComponent.h"
#include "../../../../Core/Component/Collider/BoxCollider/BoxColliderComponent.h"
#include "../../../Components/Attribute/AttributeComponent.h"
#include "../../../../Core/Directory/Directory.h"

EyeEnemy::EyeEnemy(SharedContext* Context, Object* Instigator, const Vector2& Position)
    : Enemy(Context, Instigator, Position)
{
    SetName("Eye_");

    const auto Collider = AddComponent<BoxColliderComponent>(this);
    Collider->SetSize(66.0f, 58.0f);
    Collider->SetOffset(0.0f, 0.0f);
    Collider->SetLayer(CollisionLayer::Enemy);

    AttributeComp = AddComponent<AttributeComponent>(this);
    AddComponent<MovementComponent>(this, 200.0f);

    GetTransform()->SetScale(5.0f);
}

void EyeEnemy::CreateAnimation()
{
    // Atlas Texture
    const int EyeID = GetContext()->TextureAllocator->Add(Directory::GetInstance().GetTexture("EyeAtlas.png"));
    // ~Atlas Texture

    // Sprite Size
    constexpr int FrameWidth = 12;
    constexpr int FrameHeight = 10;
    // ~Sprite Size

    // Animation Frame Time
    constexpr float IdleAnimFrameTime = 0.2f;
    constexpr float WalkAnimFrameTime = 0.15f;
    // ~Animation Frame Time

    constexpr std::array<int, 2> EyeYFrame{3, 19};
    constexpr std::array<int, 4> EyeXFrame{3, 18, 35, 50};

    std::shared_ptr<AnimationComponent> AnimComp = GetAnimation();

    // Idle Animation
    const std::shared_ptr<Animation> RightIdleAnimation = std::make_shared<Animation>();
    for (auto XFrame : EyeXFrame)
        RightIdleAnimation->AddFrame(EyeID, XFrame, EyeYFrame[0], FrameWidth, FrameHeight, IdleAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Right, AnimationState::Idle, RightIdleAnimation);

    const std::shared_ptr<Animation> LeftIdleAnimation = std::make_shared<Animation>();
    for (auto XFrame : EyeXFrame)
        LeftIdleAnimation->AddFrame(EyeID, XFrame, EyeYFrame[1], FrameWidth, FrameHeight, IdleAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Left, AnimationState::Idle, LeftIdleAnimation);
    // ~Idle Animation

    // Walk Animation
    const std::shared_ptr<Animation> RightWalkAnimation = std::make_shared<Animation>();
    for (auto XFrame : EyeXFrame)
        RightWalkAnimation->AddFrame(EyeID, XFrame, EyeYFrame[0], FrameWidth, FrameHeight, WalkAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Right, AnimationState::Walk, RightWalkAnimation);

    const std::shared_ptr<Animation> LeftWalkAnimation = std::make_shared<Animation>();
    for (auto XFrame : EyeXFrame)
        LeftWalkAnimation->AddFrame(EyeID, XFrame, EyeYFrame[1], FrameWidth, FrameHeight, WalkAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Left, AnimationState::Walk, LeftWalkAnimation);
    // ~Walk Animation
}
