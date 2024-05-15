#pragma once
#include <memory>
#include <vector>

#include "../Node/BTNode.h"

class BTCompositeNode
    : public BTNode
{
public:
    template<typename Type>
    std::unique_ptr<BTNode> AddChild()
    {
        std::unique_ptr<Type> InsertedNode = Children.emplace_back<Type>();
        return std::dynamic_pointer_cast<BTNode>(InsertedNode);
    }

public:
    const std::vector<std::unique_ptr<BTNode>>& GetChildren() const { return Children; }
    void RemoveChild(std::unique_ptr<BTNode>& Child);
    
private:
    std::vector<std::unique_ptr<BTNode>> Children;
};
