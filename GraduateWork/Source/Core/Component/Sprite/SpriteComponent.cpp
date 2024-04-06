#include "SpriteComponent.h"

#include "../Transform/TransformComponent.h"
#include "../../Resource/Texture/TextureResource.h"
#include "../../Object/Actor/Actor.h"

SpriteComponent::SpriteComponent(Object* NewOwner, const Color& NewTint)
    : ActorComponent(NewOwner), Tint(NewTint)
{}

SpriteComponent::~SpriteComponent()
{}

void SpriteComponent::Draw()
{
    Vector2 Position = Transform->GetPosition();
    const Vector2& Scale = Transform->GetScale();

    Position.x -= (abs(SourceRect.width) / 2.0f * Scale.x);
    Position.y -= (abs(SourceRect.height) / 2.0f * Scale.y);
    
    DrawTexturePro(Sprite, SourceRect,
        {Position.x, Position.y, SourceRect.width * Scale.x, SourceRect.height * Scale.y},
        {SourceRect.width * Transform->GetOrigin().x, SourceRect.height * Transform->GetOrigin().y},
        Transform->GetRotation(),
        Tint);
}

bool SpriteComponent::ContinueToDraw() const
{
    return !GetOwner()->IsQueuedForRemoval();
}

void SpriteComponent::Awake()
{
    ActorComponent::Awake();

    Transform = GetOwner()->GetTransform();
}

void SpriteComponent::Start()
{
    ActorComponent::Start();
}

void SpriteComponent::Load(int Id)
{
    if (Id != -1 && Id != CurrentTextureID)
    {
        CurrentTextureID = Id;
        Sprite = GetOwner()->GetContext()->TextureAllocator->Get(Id)->Get();
    }
}

void SpriteComponent::Load(const std::string& FilePath)
{
    const int TextureID = GetOwner()->GetContext()->TextureAllocator->Add(FilePath);
    if (TextureID <= 0 || TextureID == CurrentTextureID) return;
        
    Load(TextureID);
}

Vector2 SpriteComponent::GetSpriteSize() const
{
    return { static_cast<float>(Sprite.width), static_cast<float>(Sprite.height) };
}

void SpriteComponent::SetScale(Vector2 NewScale)
{
    Transform->SetScale(NewScale);
}
