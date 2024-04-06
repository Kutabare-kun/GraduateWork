#pragma once
#include <memory>
#include <raylib.h>
#include <string>

#include "../ActorComponent.h"
#include "../../Allocator/ResourceAllocator.h"
#include "../Drawable/DrawableComponent.h"

class TextureResource;
class TransformComponent;

class SpriteComponent
    : public ActorComponent, public DrawableComponent
{
public:
    explicit SpriteComponent(class Object* NewOwner, const Color& NewTint = WHITE);
    virtual ~SpriteComponent() override;

    void Awake() override;
    void Start() override;

    void Draw() override;

    bool ContinueToDraw() const override;

    void Load(int Id);
    void Load(const std::string& FilePath);

    const Texture2D& GetSprite() const { return Sprite; }
    const Color& GetTint() const { return Tint; }

    Vector2 GetSpriteSize() const;

    void SetTextureRect(const Rectangle& NewRect) { SourceRect = NewRect; }
    void SetTint(const Color& NewTint) { Tint = NewTint; }
    void SetScale(Vector2 NewScale);
    
private:
    Texture2D Sprite;
    Rectangle SourceRect;
    std::shared_ptr<TransformComponent> Transform;
    Color Tint;

    int CurrentTextureID = -1;
};
