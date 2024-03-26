#pragma once
#include <map>
#include <memory>

#include "../ActorComponent.h"

class SpriteComponent;

enum class AnimationState
{
    None,
    Idle,
    Walk
};

class Animation;

class AnimationComponent
    : public ActorComponent
{
public:
    AnimationComponent(Object* NewOwner);
    
    void Awake() override;
    
    void Update(float DeltaTime) override;
    
    // Add animation to object. We need its state as well 
    // so that we can switch to it.
    void AddAnimation(AnimationState State, std::shared_ptr<Animation> Animation);
	
    // Set current animation states.
    void SetAnimationState(AnimationState State); 
	
    // Returns current animation state.
    const AnimationState& GetAnimationState() const; 
    
private:
    std::shared_ptr<SpriteComponent> Sprite;
    std::map<AnimationState, std::shared_ptr<Animation>> Animations;
	
    // We store a reference to the current animation so we 
    // can quickly update and draw it.
    std::pair<AnimationState, std::shared_ptr<Animation>> CurrentAnimation; 
};
