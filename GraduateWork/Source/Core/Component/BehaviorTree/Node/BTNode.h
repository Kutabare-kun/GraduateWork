#pragma once

class BTNode
{
public:
    virtual ~BTNode() = default;

    virtual bool Run() = 0;
};