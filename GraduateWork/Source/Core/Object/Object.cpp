#include "Object.h"

Object::Object(SharedContext* Context, const Vector2& Position)
    : bQueuedForRemoval(false), Context(Context), Name("Object_")
{
    TransformComp = AddComponent<TransformComponent>(this, Position);
    InstanceIDComp = AddComponent<InstanceIDComponent>(this);
    TagComp = AddComponent<TagComponent>(this);
}

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

void Object::Draw()
{
    for (const auto& Comp : DrawableComp)
    {
        Comp->Draw();
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
