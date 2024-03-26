#include "AnimationComponent.h"

#include "../../Animation/Animation.h"
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

void AnimationComponent::Update(float DeltaTime)
{
    ActorComponent::Update(DeltaTime);

    if (Sprite == nullptr) return;

    bool bNewFrame = CurrentAnimation.second->UpdateFrame(DeltaTime);
    if (!bNewFrame) return;
    
    const auto& Frame = CurrentAnimation.second->GetCurrentFrame();
    Sprite->Load(Frame->Id);
    
    Sprite->SetTextureRect(Frame->GetRect());
}

void AnimationComponent::AddAnimation(AnimationState State, std::shared_ptr<Animation> Animation)
{
    auto Result = Animations.insert({ State, Animation });
    if (CurrentAnimation.first == AnimationState::None)
    {
        CurrentAnimation = { State, Animation };
    }
}

void AnimationComponent::SetAnimationState(AnimationState State)
{
    if (CurrentAnimation.first == State) return;
    
    auto Iter = Animations.find(State);
    if (Iter == Animations.end()) return;

    CurrentAnimation = { State, Iter->second };
    CurrentAnimation.second->Reset();
}

const AnimationState& AnimationComponent::GetAnimationState() const
{
    return CurrentAnimation.first;
}
