#pragma once
#include <memory>
#include <vector>

class Object;

class DrawableSystem
{
public:
    void Add(std::vector<std::shared_ptr<Object>>& NewObjects);

    void ProcessRemovals();

    void Draw();

private:
    void Add(std::shared_ptr<Object>& NewObject);
    void Sort();

    std::vector<std::shared_ptr<Object>> Drawables;
};
