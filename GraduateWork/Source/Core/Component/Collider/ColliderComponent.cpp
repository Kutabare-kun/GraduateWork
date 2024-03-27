#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(Object* Owner)
    : ActorComponent(Owner),
    Layer(CollisionLayer::Default)
{}

ColliderComponent::~ColliderComponent()
{}

CollisionLayer ColliderComponent::GetLayer() const
{
    return Layer;
}

void ColliderComponent::SetLayer(CollisionLayer NewLayer)
{
    Layer = NewLayer;
}
