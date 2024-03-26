#pragma once
#include "../ActorComponent.h"
#include "raylib.h"

class TransformComponent
    : public ActorComponent
{
public:
    TransformComponent(class Object* NewOwner, const Vector2& NewPosition = {0.0f, 0.0f},
                       const Vector2& NewOrigin = {0.0f, 0.0f}, float NewRotation = 0.0f, Vector2 NewScale = {1.0f, 1.0f});
    virtual ~TransformComponent() override = default;

    void SetPosition(const Vector2& NewPosition);
    void SetRotation(float NewRotation);
    void SetScale(Vector2 NewScale);
    void SetOrigin(const Vector2& NewOrigin);

    void AddPosition(const Vector2& DeltaPosition);
    void AddRotation(float DeltaRotation);
    void AddScale(Vector2 DeltaScale);
    void AddOrigin(const Vector2& DeltaOrigin);

    const Vector2& GetPosition() const { return Position; }
    float GetRotation() const { return Rotation; }
    const Vector2& GetScale() const { return Scale; }
    const Vector2& GetOrigin() const { return Origin; }

private:
    Vector2 Position;
    Vector2 Origin;
    float Rotation;
    Vector2 Scale;
};
