#include "SpriteComponent.h"

#include "../Transform/TransformComponent.h"
#include "../../Actors/Actor.h"

SpriteComponent::SpriteComponent(Actor* NewOwner, const std::string& TexturePath, const Color& NewTint)
    : ActorComponent(NewOwner), Tint(NewTint)
{
    Sprite = LoadTexture(TexturePath.c_str());
}

SpriteComponent::~SpriteComponent()
{
    UnloadTexture(Sprite);
}

void SpriteComponent::BeginPlay()
{
    Transform = GetOwner()->GetComponent<TransformComponent>();
}

void SpriteComponent::Draw()
{
    DrawTextureEx(Sprite, Transform->GetPosition(), Transform->GetRotation(), Transform->GetScale(), Tint);
}

void SpriteComponent::EventTick(float DeltaTime)
{
    ActorComponent::EventTick(DeltaTime);
}
