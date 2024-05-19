#pragma once
#include "../../../../../../Core/Component/BehaviorTree/Node/BTNode.h"

class MoveToTarget
    : public BTNode
{
public:
    MoveToTarget(std::shared_ptr<Blackboard> NodeBlackboard);

    bool Run() override;

    void SetDistance(float NewDistance) { ThresholdDistance = NewDistance; }
    float GetDistance() const { return ThresholdDistance; }

private:
    float ThresholdDistance = 5.0f;
};
