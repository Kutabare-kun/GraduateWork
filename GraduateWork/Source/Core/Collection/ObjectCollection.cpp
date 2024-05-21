#include "ObjectCollection.h"

#include "../Object/Object.h"
#include "../StaticFunctions/Debug.h"

ObjectCollection::ObjectCollection(DrawableSystem& Drawables, ColliderSystem& Collidables)
    : Drawables(Drawables), Collidables(Collidables)
{
}

void ObjectCollection::AddObject(std::shared_ptr<Object> NewObject)
{
    NewObjects.push_back(NewObject);
}

void ObjectCollection::AddObject(std::vector<std::shared_ptr<Object>>& Objects)
{
    NewObjects.insert(NewObjects.end(), Objects.begin(), Objects.end());
}

void ObjectCollection::Update(float DeltaTime)
{
    for (auto& Element : Objects)
    {
        Element->Update(DeltaTime);
    }

    Collidables.Update();
}

void ObjectCollection::LateUpdate(float DeltaTime)
{
    for (auto& Element : Objects)
    {
        Element->LateUpdate(DeltaTime);
    }
}

void ObjectCollection::Draw(const Camera2D& OwnerCamera)
{
    Drawables.Draw(OwnerCamera);
}

void ObjectCollection::ProcessNewObjects()
{
    if (NewObjects.empty()) return;

    for (const auto& Element : NewObjects)
    {
        Element->Awake();
    }

    for (auto& Element : NewObjects)
    {
        Element->Start();

        Drawables.Add(Element);
        Collidables.Add(Element);
    }

    Objects.insert(Objects.end(), NewObjects.begin(), NewObjects.end());

    NewObjects.clear();
    Objects.shrink_to_fit();
}

void ObjectCollection::ProcessRemovals()
{
    Drawables.ProcessRemovals();
    Collidables.ProcessRemovals();

    auto Iter = Objects.begin();
    while (Iter != Objects.end())
    {
        if (auto Obj = *Iter->get(); Obj.IsQueuedForRemoval())
        {
            Iter = Objects.erase(Iter);
        }
        else
        {
            ++Iter;
        }
    }
}
