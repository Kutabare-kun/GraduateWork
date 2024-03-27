#include "ObjectCollection.h"

#include "../Object/Object.h"

ObjectCollection::ObjectCollection()
{
    Drawables = std::make_unique<DrawableSystem>();
    Collidables = std::make_unique<ColliderSystem>();
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

    Collidables->Update();
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
    Drawables->Draw();
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
    
    Drawables->Add(Objects);
    Collidables->Add(Objects);
    
    NewObjects.clear();
}

void ObjectCollection::ProcessRemovals()
{
    bool bRemoved = false;
    
    auto Iter = Objects.begin();
    while (Iter != Objects.end())
    {
        if (auto Obj = *Iter->get(); Obj.IsQueuedForRemoval())
        {
            Iter = Objects.erase(Iter);
            bRemoved = true;
        }
        else
        {
            ++Iter;
        }
    }

    if (bRemoved)
    {
        Drawables->ProcessRemovals();
        Collidables->ProcessRemovals();
    }    
}
