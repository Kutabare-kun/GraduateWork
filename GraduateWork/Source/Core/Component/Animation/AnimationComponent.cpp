#include "AnimationComponent.h"

#include "../../Object/Actor/Actor.h"
#include "../Sprite/SpriteComponent.h"

AnimationComponent::AnimationComponent(Object* NewOwner)
    : ActorComponent(NewOwner)
{
}

void AnimationComponent::Awake()
{
    ActorComponent::Awake();

    Sprite = GetOwner()->GetComponent<SpriteComponent>();
}

void AnimationComponent::UpdateSprite()
{
    const auto& Frame = CurrentAnimation.second->GetCurrentFrame();
    Sprite->Load(Frame->Id);
    
    Sprite->SetTextureRect(Frame->GetRect());
}

void AnimationComponent::Update(float DeltaTime)
{
    ActorComponent::Update(DeltaTime);

    if (!Sprite) return;
    if (!CurrentAnimation.second->UpdateFrame(DeltaTime)) return;
    
    UpdateSprite();
}

void AnimationComponent::AddAnimation(FacingDirection Direction, AnimationState State, std::shared_ptr<Animation> Animation)
{
    DirectionalAnimations[Direction][State] = Animation;
    
    if (CurrentAnimation.first != AnimationState::None) return;
    CurrentAnimation = { State, Animation };
}

void AnimationComponent::SetAnimationState(AnimationState State)
{
    if (CurrentAnimation.first == State) return;
    
    auto Iter = Animations.find(State);
    if (Iter == Animations.end()) return;

    CurrentAnimation = { State, Iter->second };
    CurrentAnimation.second->Reset();
}

void AnimationComponent::SetAnimationDirection(FacingDirection Direction)
{
    if (AnimDirection == Direction) return;
    AnimDirection = Direction;

    Animations = DirectionalAnimations[AnimDirection];
    
    AnimationState State = CurrentAnimation.first;
    CurrentAnimation = std::make_pair(State, Animations[State]);

    UpdateSprite();
}

const AnimationState& AnimationComponent::GetAnimationState() const
{
    return CurrentAnimation.first;
}
