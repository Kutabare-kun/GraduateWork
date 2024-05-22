#pragma once
#include <memory>
#include <raylib.h>

#include "../ActorComponent.h"

enum class CollisionLayer
{
    Default = 1,    // Bitmask 0001
    Player  = 2,    // Bitmask 0010
    Tile    = 3,    // Bitmask 0011
    Enemy   = 4,    // Bitmask 0100
    NPC     = 5,    // Bitmask 0101
    Ability = 6,    // Bitmask 0110
    PowerUp = 7,    // Bitmask 0111
};

struct Manifold
{
    bool bColliding = false;
    const Rectangle* Other;
};

class ColliderComponent
    : public ActorComponent
{
public:
    ColliderComponent(Object* Owner);
    ~ColliderComponent() override;

    virtual void OnCollisionBeginOverlap(std::shared_ptr<ColliderComponent> Other) = 0;
    virtual void OnCollisionStayOverlap(std::shared_ptr<ColliderComponent> Other) = 0;
    virtual void OnCollisionEndOverlap(std::shared_ptr<ColliderComponent> Other) = 0;

    virtual Manifold Intersects(std::shared_ptr<ColliderComponent> Other) = 0;
    virtual void ResolveCollision(const Manifold& Collision) = 0;

    CollisionLayer GetLayer() const;
    void SetLayer(CollisionLayer NewLayer);

private:
    CollisionLayer Layer;
};
