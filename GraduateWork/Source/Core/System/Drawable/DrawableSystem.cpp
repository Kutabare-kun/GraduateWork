#include "DrawableSystem.h"

#include <algorithm>

#include "../../Object/Object.h"

void DrawableSystem::ProcessRemovals()
{
    for (auto& [Layer, Objects] : Drawables)
    {
        auto Iter = Objects.begin();
        while (Iter != Objects.end())
        {
            if (!(*Iter)->ContinueToDraw())
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

void DrawableSystem::Draw(const Camera2D& OwnerCamera)
{
    Sort();

    for (auto& [Layer, Objects] : Drawables)
    {
        for (auto& Element : Objects)
        {
            Element->Draw(OwnerCamera);
        }
    }
}

void DrawableSystem::Add(std::shared_ptr<Object>& NewObject)
{
    const std::vector<std::shared_ptr<DrawableComponent>> Draw = NewObject->GetDrawable();

    if (Draw.empty()) return;

    for (auto& Comp : Draw)
    {
        DrawLayer Layer = Comp->GetDrawLayer();

        auto Iter = Drawables.find(Layer);
        if (Iter != Drawables.end())
        {
            Iter->second.emplace_back(Comp);
        }
        else
        {
            std::vector<std::shared_ptr<DrawableComponent>> Objs;
            Objs.emplace_back(Comp);

            Drawables.emplace(Layer, Objs);
        }
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

bool DrawableSystem::LayerSort(const std::shared_ptr<DrawableComponent>& Left,
                               const std::shared_ptr<DrawableComponent>& Right)
{
    return Left->GetSortOrder() < Right->GetSortOrder();
}
