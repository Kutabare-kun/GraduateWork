#pragma once
#include "../../Core/Component/ActorComponent.h"
#include "raylib.h"

class TransformComponent
    : public ActorComponent
{
public:
    TransformComponent(class Actor* NewOwner, const Vector2& NewPosition = { 0.0f, 0.0f }, float NewRotation = 0.0f, float NewScale = 1.0f);
    virtual ~TransformComponent() override = default;

    void SetPosition(const Vector2& NewPosition);
    void SetRotation(float NewRotation);
    void SetScale(float NewScale);

    void AddPosition(const Vector2& DeltaPosition);
    void AddRotation(float DeltaRotation);
    void AddScale(float DeltaScale);

    const Vector2& GetPosition() const { return Position; }
    float GetRotation() const { return Rotation; }
    float GetScale() const { return Scale; }

private:
    Vector2 Position;
    float Rotation;
    float Scale;
};
