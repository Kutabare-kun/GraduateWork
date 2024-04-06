#include "Actor.h"
#include "../../Component/Sprite/SpriteComponent.h"
#include "../../Component/Animation/AnimationComponent.h"

Actor::Actor(SharedContext* Context, const Vector2& Position)
    : Object(Context, Position)
{
    SpriteComp = AddComponent<SpriteComponent>(this, WHITE);
    AnimationComp = AddComponent<AnimationComponent>(this);
}

void Actor::Awake()
{
    Object::Awake();
}

void Actor::Update(float DeltaTime)
{
    Object::Update(DeltaTime);
}

void Actor::LateUpdate(float DeltaTime)
{
    Object::LateUpdate(DeltaTime);
}

void Actor::Draw()
{
    Object::Draw();
}

Rectangle Actor::GetActorRectangle()
{
    const Vector2& Position = TransformComp->GetPosition();
    const Vector2 SpriteSize = SpriteComp->GetSpriteSize();
    
    return Rectangle{Position.x, Position.y, SpriteSize.x, SpriteSize.y};
}

Rectangle Actor::GetActorRectangle() const
{
    const Vector2& Position = TransformComp->GetPosition();
    const Vector2 SpriteSize = SpriteComp->GetSpriteSize();
    
    return Rectangle{Position.x, Position.y, SpriteSize.x, SpriteSize.y};
}
