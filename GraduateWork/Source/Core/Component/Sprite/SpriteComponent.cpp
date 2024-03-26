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
    const Vector2& Position = Transform->GetPosition();
    DrawTexturePro(Sprite, SourceRect,
        {Position.x, Position.y, SourceRect.width * Transform->GetScale(), SourceRect.height * Transform->GetScale()},
        {SourceRect.width * Transform->GetOrigin().x, SourceRect.height * Transform->GetOrigin().y},
        Transform->GetRotation(),
        Tint);
}

void SpriteComponent::Awake()
{
    ActorComponent::Awake();

    Transform = GetOwner()->GetComponent<TransformComponent>();
}

void SpriteComponent::SetTextureAllocator(ResourceAllocator<TextureResource>* NewTextureAllocator)
{
    TextureAllocator = NewTextureAllocator;
}

void SpriteComponent::Load(int Id)
{
    if (TextureAllocator && Id != -1 && Id != CurrentTextureID)
    {
        CurrentTextureID = Id;
        Sprite = TextureAllocator->Get(Id)->Get();
    }
}

void SpriteComponent::Load(const std::string& FilePath)
{
    if (TextureAllocator)
    {
        const int TextureID = TextureAllocator->Add(FilePath);
        if (TextureID <= 0 || TextureID == CurrentTextureID) return;
        
        Load(TextureID);
    }
}

Vector2 SpriteComponent::GetSpriteSize() const
{
    return { static_cast<float>(Sprite.width), static_cast<float>(Sprite.height) };
}
