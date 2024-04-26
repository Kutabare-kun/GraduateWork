#include "Player.h"

#include "../../../Core/Animation/Animation.h"
#include "../../../Core/Component/Movement/MovementComponent.h"
#include "../../../Core/Component/Sprite/SpriteComponent.h"
#include "../../../Core/Directory/Directory.h"
#include "../../../Core/Component/Animation/AnimationComponent.h"
#include "../../../Core/Component/Camera/CameraComponent.h"
#include "../../../Core/Component/Collider/BoxCollider/BoxColliderComponent.h"
#include "../../UI/HUD/PlayerHUD.h"

class InteractComponent;

Player::Player(SharedContext* Context, const Vector2& Position, float Speed)
    : Actor(Context, Position)
{
    SetName("Player_");
    
    MovementComp = AddComponent<MovementComponent>(this, Speed);
    
    CameraComp = AddComponent<CameraComponent>(this);
    CameraComp->UpdateZoom(0.5f);

    AddComponent<InteractComponent>(this);

    const auto Collider = AddComponent<BoxColliderComponent>(this);
    Collider->SetSize(165 * 0.4f, 145 * 0.4f);
    Collider->SetOffset(0.0f, 14.0f);
    Collider->SetLayer(CollisionLayer::Player);

    AddComponent<PlayerHUD>(this);
}

Player::~Player()
{
}

void Player::CreateAnimation()
{
    // Atlas Texture
    const int RightVikingTextureID = GetContext()->TextureAllocator->Add(Directory::GetInstance().GetTexture("RightViking.png"));
    const int LeftVikingTextureID = GetContext()->TextureAllocator->Add(Directory::GetInstance().GetTexture("LeftViking.png"));
    // ~Atlas Texture

    // Sprite Size
    constexpr int FrameWidth = 165;
    constexpr int FrameHeight = 145;
    // ~Sprite Size

    // Animation Frame Time
    constexpr float IdleAnimFrameTime = 0.2f;
    constexpr float WalkAnimFrameTime = 0.15f;
    // ~Animation Frame Time

    std::shared_ptr<AnimationComponent> AnimComp = GetAnimation();

    // Right Animation
    const std::shared_ptr<Animation> RightIdleAnimation = std::make_shared<Animation>();
    RightIdleAnimation->AddFrame(RightVikingTextureID, 600, 0, FrameWidth, FrameHeight, IdleAnimFrameTime);
    RightIdleAnimation->AddFrame(RightVikingTextureID, 800, 0, FrameWidth, FrameHeight, IdleAnimFrameTime);
    RightIdleAnimation->AddFrame(RightVikingTextureID, 0, 145, FrameWidth, FrameHeight, IdleAnimFrameTime);
    RightIdleAnimation->AddFrame(RightVikingTextureID, 200, 0, FrameWidth, FrameHeight, IdleAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Right, AnimationState::Idle, RightIdleAnimation);

    const std::shared_ptr<Animation> RightWalkAnimation = std::make_shared<Animation>();
    RightWalkAnimation->AddFrame(RightVikingTextureID, 600, 290, FrameWidth, FrameHeight, WalkAnimFrameTime);
    RightWalkAnimation->AddFrame(RightVikingTextureID, 800, 290, FrameWidth, FrameHeight, WalkAnimFrameTime);
    RightWalkAnimation->AddFrame(RightVikingTextureID, 0, 435, FrameWidth, FrameHeight, WalkAnimFrameTime);
    RightWalkAnimation->AddFrame(RightVikingTextureID, 200, 435, FrameWidth, FrameHeight, WalkAnimFrameTime);
    RightWalkAnimation->AddFrame(RightVikingTextureID, 400, 435, FrameWidth, FrameHeight, WalkAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Right, AnimationState::Walk, RightWalkAnimation);
    // ~Right Animation

    // Left Animation
    const std::shared_ptr<Animation> LeftIdleAnimation = std::make_shared<Animation>();
    LeftIdleAnimation->AddFrame(LeftVikingTextureID, 600, 0, FrameWidth, FrameHeight, IdleAnimFrameTime);
    LeftIdleAnimation->AddFrame(LeftVikingTextureID, 800, 0, FrameWidth, FrameHeight, IdleAnimFrameTime);
    LeftIdleAnimation->AddFrame(LeftVikingTextureID, 0, 145, FrameWidth, FrameHeight, IdleAnimFrameTime);
    LeftIdleAnimation->AddFrame(LeftVikingTextureID, 200, 0, FrameWidth, FrameHeight, IdleAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Left, AnimationState::Idle, LeftIdleAnimation);

    const std::shared_ptr<Animation> LeftWalkAnimation = std::make_shared<Animation>();
    LeftWalkAnimation->AddFrame(LeftVikingTextureID, 600, 290, FrameWidth, FrameHeight, WalkAnimFrameTime);
    LeftWalkAnimation->AddFrame(LeftVikingTextureID, 800, 290, FrameWidth, FrameHeight, WalkAnimFrameTime);
    LeftWalkAnimation->AddFrame(LeftVikingTextureID, 0, 435, FrameWidth, FrameHeight, WalkAnimFrameTime);
    LeftWalkAnimation->AddFrame(LeftVikingTextureID, 200, 435, FrameWidth, FrameHeight, WalkAnimFrameTime);
    LeftWalkAnimation->AddFrame(LeftVikingTextureID, 400, 435, FrameWidth, FrameHeight, WalkAnimFrameTime);
    AnimComp->AddAnimation(FacingDirection::Left, AnimationState::Walk, LeftWalkAnimation);
    // ~Left Animation
}

void Player::Awake()
{    
    Actor::Awake();

    GetSprite()->SetDrawLayer(DrawLayer::Entities);

    CreateAnimation();
}

void Player::Update(float DeltaTime)
{
    Actor::Update(DeltaTime);
}

void Player::LateUpdate(float DeltaTime)
{
    Actor::LateUpdate(DeltaTime);
}

void Player::Draw()
{
    Actor::Draw();
}
