#pragma once
#include <memory>

struct Blackboard;

class BTNode
{
public:
    BTNode(std::shared_ptr<Blackboard> NodeBlackboard);
    virtual ~BTNode() = default;

    virtual bool Run() = 0;

    std::shared_ptr<Blackboard> GetBlackboard() const { return NodeBlackboard; }

private:
    std::shared_ptr<Blackboard> NodeBlackboard;
};
