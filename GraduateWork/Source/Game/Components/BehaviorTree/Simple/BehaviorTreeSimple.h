#pragma once
#include "../../../../Core/Component/BehaviorTree/BehaviorTree.h"

#include <raylib.h>

struct BlackboardSimple
    : public Blackboard
{
    BlackboardSimple(Object* Owner)
        : Blackboard(Owner)
    {
    }

    Object* Target = nullptr;
    std::unique_ptr<Vector2> MoveToLocation = nullptr;
};

class BehaviorTreeSimple
    : public BehaviorTree
{
public:
    BehaviorTreeSimple(Object* Owner);

    void Awake() override;
};
