#include "MoveToLocation.h"

#include <raylib.h>
#include <raymath.h>

#include "../../../../../../Core/Object/Object.h"
#include "../../../Simple/BehaviorTreeSimple.h"
#include "../../../../../../Core/Component/Transform/TransformComponent.h"
#include "../../../../../../Core/Component/Velocity/VelocityComponent.h"

MoveToLocation::MoveToLocation(std::shared_ptr<Blackboard> NodeBlackboard)
    : BTNode(NodeBlackboard)
{
}

bool MoveToLocation::Run()
{
    std::shared_ptr<Blackboard> BB = GetBlackboard();
    if (!BB) return false;

    std::shared_ptr<BlackboardSimple> BBS = std::dynamic_pointer_cast<BlackboardSimple>(BB);
    if (!BBS) return false;

    if (!BBS->MoveToLocation) return false;

    std::shared_ptr<TransformComponent> TransformComp = BBS->GetOwner()->GetTransform();
    if (!TransformComp) return false;

    std::shared_ptr<VelocityComponent> VelocityComp = BBS->GetOwner()->GetComponent<VelocityComponent>();

    const Vector2 MoveTo = Vector2Subtract(*BBS->MoveToLocation, TransformComp->GetPosition());
    const float Distance = Vector2Distance(TransformComp->GetPosition(), *BBS->MoveToLocation);

    if (Distance < 5.0f)
    {
        VelocityComp->SetVelocity(Vector2Zero());
        return false;
    }

    VelocityComp->SetVelocity(Vector2Normalize(MoveTo));
    return Distance > 5.0f;
}
