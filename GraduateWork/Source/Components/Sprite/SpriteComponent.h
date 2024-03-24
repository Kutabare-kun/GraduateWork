#pragma once
#include <memory>

#include "../../Core/Component/ActorComponent.h"
#include "../../SmartPtr/SmartTexture.h"

class TransformComponent;

class SpriteComponent
    : public ActorComponent
{
public:
    SpriteComponent(class Actor* NewOwner, const std::string& TexturePath, const Color& NewTint);
    virtual ~SpriteComponent() override;

    void BeginPlay() override;

    virtual void Draw() override;

    void EventTick(float DeltaTime) override;

    const Texture2D& GetSprite() const { return Sprite; }
    const Color& GetTint() const { return Tint; }

    void SetTint(const Color& NewTint) { Tint = NewTint; }
    
private:
    Texture2D Sprite;
    std::shared_ptr<TransformComponent> Transform;
    Color Tint;
};
