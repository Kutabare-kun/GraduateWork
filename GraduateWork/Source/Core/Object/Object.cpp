#include "Object.h"

void Object::Awake()
{
    for (auto& Component : Components)
    {
        Component->Awake();
    }
}

void Object::Start()
{
    for (auto& Component : Components)
    {
        Component->Start();
    }
}

void Object::Update(float DeltaTime)
{
    for (auto& Component : Components)
    {
        Component->Update(DeltaTime);
    }
}

void Object::LateUpdate(float DeltaTime)
{
    for (auto& Component : Components)
    {
        Component->LateUpdate(DeltaTime);
    }
}

void Object::Draw(const Camera2D& OwnerCamera)
{
    for (const auto& Comp : DrawableComp)
    {
        Comp->Draw(OwnerCamera);
    }
}

void Object::OnCollisionBeginOverlap(std::shared_ptr<ColliderComponent> Other)
{
    for (const auto& Collider : Collidables)
    {
        Collider->OnCollisionBeginOverlap(Other);
    }
}

void Object::OnCollisionStayOverlap(std::shared_ptr<ColliderComponent> Other)
{
    for (const auto& Collider : Collidables)
    {
        Collider->OnCollisionStayOverlap(Other);
    }
}

void Object::OnCollisionEndOverlap(std::shared_ptr<ColliderComponent> Other)
{
    for (const auto& Collider : Collidables)
    {
        Collider->OnCollisionEndOverlap(Other);
    }
}

bool Object::IsQueuedForRemoval()
{
    return bQueuedForRemoval;
}

void Object::QueueForRemoval()
{
    bQueuedForRemoval = true;
}
