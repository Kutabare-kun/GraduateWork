#include "MoveToTarget.h"

#include <raylib.h>
#include <raymath.h>

#include "../../../../../../Core/Component/Velocity/VelocityComponent.h"
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

    std::shared_ptr<TransformComponent> TargetTransformComp = BBS->Target->GetTransform();
    if (!TargetTransformComp) return false;

    std::shared_ptr<TransformComponent> OwnerTransformComp = BBS->GetOwner()->GetTransform();
    if (!OwnerTransformComp) return false;

    std::shared_ptr<VelocityComponent> VelocityComp = BBS->GetOwner()->GetComponent<VelocityComponent>();
    if (!VelocityComp) return false;

    const Vector2 MoveTo = Vector2Subtract(TargetTransformComp->GetPosition(), OwnerTransformComp->GetPosition());
    const float Distance = Vector2Distance(OwnerTransformComp->GetPosition(), TargetTransformComp->GetPosition());

    if (Distance < GetDistance())
    {
        VelocityComp->SetVelocity(Vector2Zero());
        return false;
    }

    VelocityComp->SetVelocity(Vector2Normalize(MoveTo));
    return Distance > GetDistance();
}
