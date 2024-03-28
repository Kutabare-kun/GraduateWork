#include "ColliderSystem.h"

#include "../../StaticFunctions/Debug.h"
#include "../../Window/Window.h"

ColliderSystem::ColliderSystem()
{
    Bitmask DefaultCollision;
    DefaultCollision.SetBit((int)CollisionLayer::Default);
    CollisionLayers.emplace(CollisionLayer::Default, DefaultCollision);

    CollisionLayers.insert(std::make_pair(CollisionLayer::Tile, Bitmask{}));

    Bitmask PlayerCollision;
    PlayerCollision.SetBit((int)CollisionLayer::Player);
    PlayerCollision.SetBit((int)CollisionLayer::Tile);
    CollisionLayers.insert(std::make_pair(CollisionLayer::Player, PlayerCollision));

    const Vector2& ScreenSize = Window::GetInstance().GetScreenSize();
    CollisionTree = std::make_unique<Quadtree>(5, 5, 0, Rectangle{0, 0, ScreenSize.x, ScreenSize.y}, nullptr);
}

void ColliderSystem::Add(std::vector<std::shared_ptr<Object>>& Objects)
{
    for (auto Element : Objects)
    {
        auto ColliderComp = Element->GetComponent<BoxColliderComponent>();
        if (ColliderComp)
        {
            CollisionLayer Layer = ColliderComp->GetLayer();

            auto Iter = Collidables.find(Layer);
            if (Iter != Collidables.end())
            {
                Collidables[Layer].push_back(ColliderComp);
            }
            else
            {
                std::vector<std::shared_ptr<BoxColliderComponent>> Objs;
                Objs.push_back(ColliderComp);

                Collidables.insert(std::make_pair(Layer, Objs));
            }
        }
    }
}

void ColliderSystem::ProcessRemovals()
{
    for (auto& Layer : Collidables)
    {
        auto Iter = Layer.second.begin();
        while (Iter != Layer.second.end())
        {
            if ((*Iter)->GetOwner()->IsQueuedForRemoval())
            {
                Iter = Layer.second.erase(Iter);
            }
            else
            {
                ++Iter;
            }
        }
    }
}

void ColliderSystem::Update()
{    
    CollisionTree->Clear();
    for (auto [Layer, Colliders] : Collidables)
    {
        for (auto ColliderComp : Colliders)
        {
            CollisionTree->Insert(ColliderComp);

            Debug::GetInstance().DrawRectangle(ColliderComp->GetCollidable(), RED);
        }
    }

    Resolve();

    CollisionTree->DrawDebug();
}

void ColliderSystem::Resolve()
{
    for (auto [Layer, Colliders] : Collidables)
    {
        if (CollisionLayers[Layer].GetMask() == 0)
        {
            continue;
        }

        for (auto ColliderComp : Colliders)
        {
            if (ColliderComp->GetOwner()->GetTransform()->IsStatic())
            {
                continue;
            }

            std::vector<std::shared_ptr<BoxColliderComponent>> Collisions
                = CollisionTree->Search(ColliderComp->GetCollidable());

            for (auto Collision : Collisions)
            {
                if (Collision->GetOwner()->GetInstanceID()->GetInstanceID()
                    == ColliderComp->GetOwner()->GetInstanceID()->GetInstanceID())
                {
                    continue;
                }

                bool LayersCollide = CollisionLayers[ColliderComp->GetLayer()].GetBit((int)Collision->GetLayer());

                if (LayersCollide)
                {
                    Manifold CollisionInfo = ColliderComp->Intersects(Collision);
                    
                    if (CollisionInfo.bColliding)
                    {                        
                        if (Collision->GetOwner()->GetTransform()->IsStatic())
                        {
                            ColliderComp->ResolveCollision(CollisionInfo);
                        }
                        else
                        {
                            // TODO: Implement collision resolution for dynamic objects
                            ColliderComp->ResolveCollision(CollisionInfo);
                        }
                    }
                }
            }
        }
    }
}
