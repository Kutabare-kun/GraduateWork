#include "BehaviorTreeSimple.h"

#include "../../../../Core/Component/BehaviorTree/Sequence/BTSequence.h"
#include "../Task/FindLocation/FindLocation.h"
#include "../Task/Move/Location/MoveToLocation.h"
#include "../Task/Move/Target/MoveToTarget.h"

BehaviorTreeSimple::BehaviorTreeSimple(Object* Owner)
    : BehaviorTree(Owner)
{
}

void BehaviorTreeSimple::Awake()
{
    Blackboard = std::make_shared<BlackboardSimple>(GetOwner());

    BehaviorTree::Awake();

    GetRoot()->AddChild<FindLocation>(GetBlackboard());
    GetRoot()->AddChild<MoveToLocation>(GetBlackboard());
    GetRoot()->AddChild<MoveToTarget>(GetBlackboard());

    // TODO: Add attack to Target
    //GetRoot()->AddChild<>()
}
