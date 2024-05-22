#include "InteractComponent.h"

#include "../../../Core/Algorithm/Raycast/Raycast.h"
#include "../../../Core/Object/Object.h"
#include "../../../Core/Component/Movement/MovementComponent.h"
#include "../../../Core/Interface/Iteractable/IInteractable.h"

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

    const RaycastResult Result = GetOwner()->GetContext()->RaycastSys->Cast(StartPosition, EndPosition, GetOwner()->GetInstanceID()->GetID());

    if (Result.Collision)
    {
        const auto Interactables = Result.Collision->GetComponents<IInteractable>();
        for (const auto& Interface : Interactables)
        {
            Interface->OnInteraction(GetOwner());
        }
    }
}
