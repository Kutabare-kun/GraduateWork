#include "DrawableSystem.h"

#include <algorithm>

#include "../../Object/Object.h"

void DrawableSystem::Add(std::vector<std::shared_ptr<Object>>& NewObjects)
{
    for (auto& Element : NewObjects)
    {
        Add(Element);
    }
}

void DrawableSystem::ProcessRemovals()
{
    for (auto& [Layer, Objects] : Drawables)
    {
        auto Iter = Objects.begin();
        while (Iter != Objects.end())
        {
            if ((*Iter)->ContinueToDraw())
            {
                Iter = Objects.erase(Iter);
            }
            else
            {
                ++Iter;
            }
        }
    }
}

void DrawableSystem::Draw()
{
    Sort();
    
    for (auto& [Layer, Objects] : Drawables)
    {
        for (auto& Element : Objects)
        {
            Element->Draw();
        }
    }
}

void DrawableSystem::Add(std::shared_ptr<Object>& NewObject)
{
    const std::shared_ptr<DrawableComponent> Draw = NewObject->GetDrawable();

    if (!Draw) return;

    DrawLayer Layer = Draw->GetDrawLayer();

    auto Iter = Drawables.find(Layer);
    if (Iter != Drawables.end())
    {
        Iter->second.emplace_back(Draw);
    }
    else
    {
        std::vector<std::shared_ptr<DrawableComponent>> Objs;
        Objs.emplace_back(Draw);

        Drawables.emplace(Layer, Objs);
    }
}

void DrawableSystem::Sort()
{
    for (auto& [Layer, Objects] : Drawables)
    {
        if (!std::ranges::is_sorted(Objects.begin(), Objects.end(), LayerSort))
        {
            std::ranges::sort(Objects.begin(), Objects.end(), LayerSort);
        }
    }
}

bool DrawableSystem::LayerSort(const std::shared_ptr<DrawableComponent>& Left, const std::shared_ptr<DrawableComponent>& Right)
{
    return Left->GetSortOrder() < Right->GetSortOrder();
}
