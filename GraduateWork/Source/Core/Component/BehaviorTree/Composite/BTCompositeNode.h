#pragma once
#include <memory>
#include <vector>

#include "../Node/BTNode.h"

class BTCompositeNode
    : public BTNode
{
public:
    template <typename Type, typename... Arguments>
    std::shared_ptr<Type> AddChild(Arguments&&... Args)
    {
        static_assert(std::is_base_of_v<BTNode, Type>, "Type must derive from BTNode");

        auto Child = std::make_shared<Type>(std::forward<Arguments>(Args)...);
        Children.push_back(Child);
        return Child;
    }

public:
    BTCompositeNode(std::shared_ptr<Blackboard> NodeBlackboard);

    const std::vector<std::shared_ptr<BTNode>>& GetChildren() const { return Children; }
    void RemoveChild(std::shared_ptr<BTNode>& Child);

private:
    std::vector<std::shared_ptr<BTNode>> Children;
};
