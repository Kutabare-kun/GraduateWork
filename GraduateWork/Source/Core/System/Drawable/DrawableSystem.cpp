#include "DrawableSystem.h"

#include <algorithm>

#include "../../Component/Drawable/DrawableComponent.h"
#include "../../Object/Object.h"

void DrawableSystem::Add(std::vector<std::shared_ptr<Object>>& NewObjects)
{
    for (auto& Element : NewObjects)
    {
        Add(Element);
    }

    Sort();
}

void DrawableSystem::ProcessRemovals()
{
    auto Iter = Drawables.begin();
    while (Iter != Drawables.end())
    {
        if ((*Iter)->IsQueuedForRemoval())
        {
            Iter = Drawables.erase(Iter);
        }
        else
        {
            ++Iter;
        }
    }
}

void DrawableSystem::Draw()
{
    for (auto& Element : Drawables)
    {
        Element->Draw();
    }
}

void DrawableSystem::Add(std::shared_ptr<Object>& NewObject)
{
    const std::shared_ptr<DrawableComponent> Draw = NewObject->GetDrawable();

    if (!Draw) return;
    Drawables.emplace_back(NewObject);
}

void DrawableSystem::Sort()
{
    std::sort(Drawables.begin(), Drawables.end(),
              [](std::shared_ptr<Object>& Left, std::shared_ptr<Object>& Right) -> bool
              {
                  return Left->GetDrawable()->GetSortOrder() < Right->GetDrawable()->GetSortOrder();
              });
}
