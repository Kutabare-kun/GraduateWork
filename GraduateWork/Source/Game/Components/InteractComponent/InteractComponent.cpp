#include "InteractComponent.h"

#include "../../../Core/Algorithm/Raycast/Raycast.h"
#include "../../../Core/Object/Object.h"
#include "../../../Core/Component/Movement/MovementComponent.h"
#include "../../../Core/StaticFunctions/Debug.h"

InteractComponent::InteractComponent(Object* Owner)
    : ActorComponent(Owner), InteractDistance(75.0f)
{}

void InteractComponent::Awake()
{
    Direction = GetOwner()->GetComponent<MovementComponent>();
}

void InteractComponent::Update(float DeltaTime)
{
    ActorComponent::Update(DeltaTime);

    if (!IsKeyDown(KEY_F)) return;

    const Vector2 HeadingVector = Direction->GetHeading();
    
    const Vector2 StartPosition = GetOwner()->GetTransform()->GetPosition();
    const Vector2 EndPosition = {StartPosition.x + HeadingVector.x * InteractDistance, StartPosition.y + HeadingVector.y * InteractDistance};

    RaycastResult Result = GetOwner()->GetContext()->RaycastSys->Cast(StartPosition, EndPosition, GetOwner()->GetInstanceID()->GetID());

    if (Result.Collision)
        Debug::GetInstance().Log(TextFormat("Object hit: %d", Result.Collision->GetInstanceID()->GetID()));
}
