#pragma once
#include <raylib.h>

#include "../Object.h"

class AnimationComponent;
class SpriteComponent;

class Actor
    : public Object
{
public:
    // Constructor
    Actor(SharedContext* Context, Object* Instigator, const Vector2& Position);

    // Destructor
    ~Actor() override = default;

    // Calling after constructor
    void Awake() override;

    virtual void OnHealthChange(Object* Instigator, float Delta, bool IsDead);

    // Return rectangle of actor
    Rectangle GetActorRectangle();

    // Return rectangle of actor
    Rectangle GetActorRectangle() const;

    std::shared_ptr<SpriteComponent> GetSprite() const { return SpriteComp; }
    std::shared_ptr<AnimationComponent> GetAnimation() const { return AnimationComp; }

protected:
    virtual void CreateAnimation() = 0;
    
    std::shared_ptr<SpriteComponent> SpriteComp;
    std::shared_ptr<AnimationComponent> AnimationComp;
};
