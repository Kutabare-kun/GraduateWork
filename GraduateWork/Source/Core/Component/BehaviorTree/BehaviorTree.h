#pragma once
#include <memory>

#include "../ActorComponent.h"
#include "Node/BTNode.h"

struct Blackboard
{
    Blackboard(Object* Owner)
        : Owner(Owner)
    {
    }

    virtual ~Blackboard() = default;
    
    Object* GetOwner() const { return Owner; }

private:
    Object* Owner;
};

class BehaviorTree
    : public ActorComponent
{
public:
    BehaviorTree(Object* Owner);

    void Update(float DeltaTime) override;

    const std::unique_ptr<BTNode>& GetRoot() { return Root; }
    std::shared_ptr<Blackboard> GetBlackboard() { return Blackboard; }

private:
    std::unique_ptr<BTNode> Root;
    std::shared_ptr<Blackboard> Blackboard;
};
