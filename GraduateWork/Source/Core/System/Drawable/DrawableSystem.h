#pragma once
#include <map>
#include <memory>
#include <vector>

#include "../../Component/Drawable/DrawableComponent.h"

class Object;

class DrawableSystem
{
public:
    void Add(std::shared_ptr<Object>& NewObject);

    void ProcessRemovals();

    void Draw(const Camera2D& OwnerCamera);

private:
    void Sort();

    static bool LayerSort(const std::shared_ptr<DrawableComponent>& Left,
                          const std::shared_ptr<DrawableComponent>& Right);

    std::map<DrawLayer, std::vector<std::shared_ptr<DrawableComponent>>> Drawables;
};
