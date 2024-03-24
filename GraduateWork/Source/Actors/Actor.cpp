#include "Actor.h"

Actor::Actor(const std::string& TexturePath, Vector2 Posisiton, bool bEnableTicks /*= true*/)
    : Position(Posisiton)
{
    this->bEnableTicks = bEnableTicks;
    
    ActorTexture = std::make_unique<SmartTexture>(TexturePath);
}

void Actor::Draw() const
{
    ActorTexture->DrawTexture(Position);
}

Vector2& Actor::GetActorPosition()
{
    return Position;
}

const Vector2& Actor::GetActorPosition() const
{
    return Position;
}

Rectangle Actor::GetActorRectangle()
{
    const Rectangle TextureRectangle = ActorTexture->GetTextureRectangle();
    return Rectangle{Position.x, Position.y, TextureRectangle.width, TextureRectangle.height};
}

const Rectangle Actor::GetActorRectangle() const
{
    const Rectangle TextureRectangle = ActorTexture->GetTextureRectangle();
    return Rectangle{Position.x, Position.y, TextureRectangle.width, TextureRectangle.height};
}

void Actor::SetActorPosition(const Vector2& NewPosition)
{
    Position = NewPosition;
}
