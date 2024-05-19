#pragma once
#include <memory>

#include "../ActorComponent.h"

class BTSequence;

struct Blackboard
{
    Blackboard(Object* Owner)
        : Owner(Owner)
    {
    }

    virtual ~Blackboard() = default;

    void UpdateDeltaTime(float DeltaTime)
    {
        this->_DeltaTime = DeltaTime;
    }
    
    Object* GetOwner() const { return Owner; }
    float GetDeltaTime() const { return _DeltaTime; }

private:
    Object* Owner;
    float _DeltaTime = 0.0f;
};

class BehaviorTree
    : public ActorComponent
{
public:
    BehaviorTree(Object* Owner);

    void Awake() override;

    void Update(float DeltaTime) override;

    const std::shared_ptr<BTSequence>& GetRoot() { return Root; }
    std::shared_ptr<Blackboard> GetBlackboard() { return Blackboard; }

protected:
    std::shared_ptr<BTSequence> Root;
    std::shared_ptr<Blackboard> Blackboard;
};
