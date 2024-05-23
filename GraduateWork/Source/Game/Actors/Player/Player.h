#pragma once
#include "../../../Core/Object/Actor/Actor.h"
#include "../../Interface/Level/Ilevel.h"

class LevelComponent;
class AbilityComponent;
class AttributeComponent;
class CameraComponent;
class MovementComponent;

class Player final
    : public Actor, public Ilevel
{
public:
    Player(SharedContext* Context, Object* Instigator, const Vector2& Position = {0.0f, 0.0f });
    ~Player() override = default;

    void Awake() override;

    void OnCollisionBeginOverlap(std::shared_ptr<ColliderComponent> Other) override;
    void OnCollisionStayOverlap(std::shared_ptr<ColliderComponent> Other) override;
    void OnHealthChange(Object* Instigator, float Delta, bool IsDead) override;
    
    void HandleDamage(std::shared_ptr<ColliderComponent> Other) const;

    unsigned GetLevel() const override;

    std::shared_ptr<MovementComponent> GetMovement() const { return MovementComp; }
    std::shared_ptr<CameraComponent> GetCamera() const { return CameraComp; }
    std::shared_ptr<AttributeComponent> GetAttributeComp() const { return AttributeComp; }
    std::shared_ptr<AbilityComponent> GetAbility() const { return AbilityComp; }
    std::shared_ptr<LevelComponent> GetLevelComp() const override { return LevelComp;}

protected:
    std::shared_ptr<MovementComponent> MovementComp;
    std::shared_ptr<CameraComponent> CameraComp;
    std::shared_ptr<AttributeComponent> AttributeComp;
    std::shared_ptr<AbilityComponent> AbilityComp;
    std::shared_ptr<LevelComponent> LevelComp;

private:
    void CreateAnimation() override;
};
