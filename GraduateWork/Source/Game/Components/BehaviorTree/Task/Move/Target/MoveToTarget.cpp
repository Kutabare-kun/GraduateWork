#include "MoveToTarget.h"

#include <raylib.h>
#include <raymath.h>

#include "../../../../../../Core/Object/Object.h"
#include "../../../Simple/BehaviorTreeSimple.h"

MoveToTarget::MoveToTarget(std::shared_ptr<Blackboard> NodeBlackboard)
    : BTNode(NodeBlackboard)
{
}

bool MoveToTarget::Run()
{
    std::shared_ptr<Blackboard> BB = GetBlackboard();
    if (!BB) return false;

    std::shared_ptr<BlackboardSimple> BBS = std::dynamic_pointer_cast<BlackboardSimple>(BB);
    if (!BBS) return false;

    if (!BBS->Target) return false;

    if (BBS->MoveToLocation) return false;

    std::shared_ptr<TransformComponent> TargetTransformComp = BBS->Target->GetTransform();
    if (!TargetTransformComp) return false;

    std::shared_ptr<TransformComponent> OwnerTransformComp = BBS->GetOwner()->GetTransform();
    if (!OwnerTransformComp) return false;

    std::shared_ptr<MovementComponent> MovementComp = BBS->GetOwner()->GetComponent<MovementComponent>();
    if (!MovementComp) return false;

    const Vector2 MoveTo = Vector2Subtract(TargetTransformComp->GetPosition(), OwnerTransformComp->GetPosition());
    const float Distance = Vector2Distance(OwnerTransformComp->GetPosition(), TargetTransformComp->GetPosition());

    if (Distance < GetDistance()) return false;

    MovementComp->InputValue(1.0f, Vector2Normalize(MoveTo));
    return Distance > GetDistance();
}
