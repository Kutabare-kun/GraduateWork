#pragma once
#include "../../../Core/Object/Actor/Actor.h"

class AbilityComponent;
class AttributeComponent;
class CameraComponent;
class MovementComponent;

class Player final
    : public Actor
{
public:
    Player(SharedContext* Context, Object* Instigator, const Vector2& Position = {0.0f, 0.0f });
    ~Player() override = default;

    void Awake() override;

    void OnCollisionBeginOverlap(std::shared_ptr<ColliderComponent> Other) override;
    void OnCollisionStayOverlap(std::shared_ptr<ColliderComponent> Other) override;
    void OnHealthChange(Object* Instigator, float Delta, bool IsDead) override;
    
    void HandleDamage(std::shared_ptr<ColliderComponent> Other) const;

    std::shared_ptr<MovementComponent> GetMovement() const { return MovementComp; }
    std::shared_ptr<CameraComponent> GetCamera() const { return CameraComp; }

protected:
    std::shared_ptr<MovementComponent> MovementComp;
    std::shared_ptr<CameraComponent> CameraComp;
    std::shared_ptr<AttributeComponent> AttributeComp;
    std::shared_ptr<AbilityComponent> AbilityComp;

private:
    void CreateAnimation() override;
};
