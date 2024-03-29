#pragma once
#include <map>
#include <memory>
#include <unordered_map>

#include "../ActorComponent.h"
#include "../../Animation/Animation.h"

enum class AnimationState
{
    None,
    Idle,
    Walk
};

enum class FacingDirection
{
    None,
    Left,
    Right,
    Up,
    Down
};

class SpriteComponent;

class AnimationComponent
    : public ActorComponent
{
public:
    AnimationComponent(Object* NewOwner);
    
    void Awake() override;
    void UpdateSprite();

    void Update(float DeltaTime) override;
    
    // Add animation to object. We need its state as well 
    // so that we can switch to it.
    void AddAnimation(FacingDirection Direction, AnimationState State, std::shared_ptr<Animation> Animation);
	
    // Set current animation states.
    void SetAnimationState(AnimationState State);

    void SetAnimationDirection(FacingDirection Direction);
    FacingDirection GetAnimationDirection() const { return AnimDirection; }
	
    // Returns current animation state.
    const AnimationState& GetAnimationState() const;
    
private:
    std::shared_ptr<SpriteComponent> Sprite;
    std::map<AnimationState, std::shared_ptr<Animation>> Animations;
    std::unordered_map<FacingDirection, std::map<AnimationState, std::shared_ptr<Animation>>> DirectionalAnimations;

    FacingDirection AnimDirection = FacingDirection::None;
	
    // We store a reference to the current animation so we 
    // can quickly update and draw it.
    std::pair<AnimationState, std::shared_ptr<Animation>> CurrentAnimation; 
};
