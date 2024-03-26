#include "ObjectCollection.h"

#include "../Object/Object.h"

void ObjectCollection::AddObject(std::shared_ptr<Object> NewObject)
{
    NewObjects.push_back(NewObject);
}

void ObjectCollection::Update(float DeltaTime)
{
    for (auto& Element : Objects)
    {
        Element->Update(DeltaTime);
    }
}

void ObjectCollection::LateUpdate(float DeltaTime)
{
    for (auto& Element : Objects)
    {
        Element->LateUpdate(DeltaTime);
    }
}

void ObjectCollection::Draw()
{
    for (auto& Element : Objects)
    {
        Element->Draw();
    }
}

void ObjectCollection::ProcessNewObjects()
{
    if (NewObjects.empty()) return;

    for (const auto& Element : NewObjects)
    {
        Element->Awake();
    }

    for (const auto& Element : NewObjects)
    {
        Element->Start();
    }

    Objects.assign(NewObjects.begin(), NewObjects.end());
    NewObjects.clear();
}

void ObjectCollection::ProcessRemovals()
{
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
