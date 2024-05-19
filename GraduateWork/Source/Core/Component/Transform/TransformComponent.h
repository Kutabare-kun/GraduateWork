#pragma once
#include <memory>
#include <vector>

#include "../ActorComponent.h"
#include "raylib.h"

class TransformComponent
    : public ActorComponent
{
public:
    TransformComponent(class Object* NewOwner, const Vector2& NewPosition = {0.0f, 0.0f},
                       const Vector2& NewOrigin = {0.0f, 0.0f}, float NewRotation = 0.0f, Vector2 NewScale = {1.0f, 1.0f});
    virtual ~TransformComponent() override = default;

    void AddPosition(const Vector2& DeltaPosition);
    void AddRotation(float DeltaRotation);
    void AddScale(Vector2 DeltaScale);
    void AddOrigin(const Vector2& DeltaOrigin);
    
    void SetPosition(const Vector2& NewPosition);
    void SetRotation(float NewRotation);
    void SetScale(Vector2 NewScale);
    void SetScale(float NewScale);
    void SetOrigin(const Vector2& NewOrigin);
    void SetStatic(bool bIsStatic);

    void SetParent(std::shared_ptr<TransformComponent> NewParent);
    const std::shared_ptr<TransformComponent> GetParent() const { return Parent; }

    void AddChild(std::shared_ptr<TransformComponent> NewChild);
    void RemoveChild(std::shared_ptr<TransformComponent> Child);
    const std::vector<std::shared_ptr<TransformComponent>>& GetChildren() const { return Children; }

    const Vector2& GetPosition() const { return Position; }
    float GetRotation() const { return Rotation; }
    const Vector2& GetScale() const { return Scale; }
    const Vector2& GetOrigin() const { return Origin; }
    bool IsStatic() const { return bIsStatic; }

private:
    Vector2 Position;
    Vector2 Origin;
    float Rotation;
    Vector2 Scale;

    bool bIsStatic;

    std::shared_ptr<TransformComponent> Parent;
    std::vector<std::shared_ptr<TransformComponent>> Children;
};
