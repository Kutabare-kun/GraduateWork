#include "ColliderSystem.h"

#include <ranges>

#include "../../Window/Window.h"

ColliderSystem::ColliderSystem(Quadtree& CollisionTree)
    : CollisionTree(CollisionTree)
{
    // Default collision layers
    Bitmask DefaultCollision;
    DefaultCollision.SetBit((int)CollisionLayer::Default);
    CollisionLayers.emplace(CollisionLayer::Default, DefaultCollision);
    CollisionLayers.insert(std::make_pair(CollisionLayer::Tile, Bitmask{}));
    // ~Default collision layers

    // Player collision layer
    Bitmask PlayerCollision;
    PlayerCollision.SetBit((int)CollisionLayer::Player);
    PlayerCollision.SetBit((int)CollisionLayer::Tile);
    CollisionLayers.insert(std::make_pair(CollisionLayer::Player, PlayerCollision));
    // ~Player collision layer

    // Enemy collision layer
    Bitmask EnemyCollision;
    EnemyCollision.SetBit((int)CollisionLayer::Enemy);
    EnemyCollision.SetBit((int)CollisionLayer::Tile);
    EnemyCollision.SetBit((int)CollisionLayer::Player);
    EnemyCollision.SetBit((int)CollisionLayer::Ability);
    CollisionLayers.insert(std::make_pair(CollisionLayer::Enemy, EnemyCollision));

    Bitmask AbilityCollision;
    AbilityCollision.SetBit((int)CollisionLayer::Enemy);
    CollisionLayers.insert(std::make_pair(CollisionLayer::Ability, AbilityCollision));
    // ~Enemy collision layer

    Bitmask PowerUpCollision;
    PowerUpCollision.SetBit((int)CollisionLayer::Player);
    PowerUpCollision.SetBit((int)CollisionLayer::Tile);
    PowerUpCollision.SetBit((int)CollisionLayer::PowerUp);
    CollisionLayers.insert(std::make_pair(CollisionLayer::PowerUp, PowerUpCollision));

    const Vector2& ScreenSize = Window::GetInstance().GetScreenSize();
}

void ColliderSystem::Add(std::shared_ptr<Object>& ThisObject)
{
    if (const auto ColliderComp = ThisObject->GetComponent<BoxColliderComponent>(); ColliderComp)
    {
        CollisionLayer Layer = ColliderComp->GetLayer();

        if (auto Iter = Collidables.find(Layer);
            Iter != Collidables.end())
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

void ColliderSystem::ProcessRemovals()
{
    for (auto& Layer : Collidables | std::views::values)
    {
        auto Iter = Layer.begin();
        while (Iter != Layer.end())
        {
            if ((*Iter)->GetOwner()->IsQueuedForRemoval())
            {
                CollisionTree.Remove(*Iter);
                Iter = Layer.erase(Iter);
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
    ProcessCollidingObjects();

    CollisionTree.Clear();
    for (auto Colliders : Collidables | std::views::values)
    {
        for (const auto& ColliderComp : Colliders)
        {
            CollisionTree.Insert(ColliderComp);
        }
    }

    Resolve();
}

void ColliderSystem::Resolve()
{
    for (auto [Layer, Colliders] : Collidables)
    {
        if (CollisionLayers[Layer].GetMask() == 0)
        {
            continue;
        }

        for (const auto& ColliderComp : Colliders)
        {
            if (ColliderComp->GetOwner()->GetTransform()->IsStatic())
            {
                continue;
            }

            if (ColliderComp->GetOwner()->IsQueuedForRemoval())
            {
                continue;
            }

            const std::vector<std::shared_ptr<BoxColliderComponent>> Collisions
                = CollisionTree.Search(ColliderComp->GetCollidable());

            for (const auto& Collision : Collisions)
            {
                if (Collision->GetOwner()->GetInstanceID()->GetID()
                    == ColliderComp->GetOwner()->GetInstanceID()->GetID())
                {
                    continue;
                }

                if (Collision->GetOwner()->IsQueuedForRemoval()) continue;

                if (!CollisionLayers[ColliderComp->GetLayer()].GetBit((int)Collision->GetLayer())) continue;
                Manifold CollisionInfo = ColliderComp->Intersects(Collision);

                if (!CollisionInfo.bColliding) continue;

                if (const auto& [Iter, IsEmplaced] = ObjectsColliding.emplace(std::make_pair(ColliderComp, Collision));
                    IsEmplaced)
                {
                    ColliderComp->GetOwner()->OnCollisionBeginOverlap(Collision);
                    Collision->GetOwner()->OnCollisionBeginOverlap(ColliderComp);
                }

                if (Collision->GetOwner()->GetTransform()->IsStatic())
                {
                    ColliderComp->ResolveCollision(CollisionInfo);
                }
                else
                {
                    if (!(ColliderComp->GetOwner()->GetTag()->Compare(Tag::Ability) || Collision->GetOwner()->
                        GetTag()->Compare(Tag::Ability)))
                    {
                        ColliderComp->ResolveCollision(CollisionInfo);
                    }
                }
            }
        }
    }
}

void ColliderSystem::ProcessCollidingObjects()
{
    auto Iter = ObjectsColliding.begin();
    while (Iter != ObjectsColliding.end())
    {
        const auto& [Left, Right] = *Iter;

        const std::shared_ptr<BoxColliderComponent> First = Left;
        const std::shared_ptr<BoxColliderComponent> Second = Right;

        if (First->GetOwner()->IsQueuedForRemoval() || Second->GetOwner()->IsQueuedForRemoval())
        {
            First->GetOwner()->OnCollisionEndOverlap(Second);
            Second->GetOwner()->OnCollisionEndOverlap(First);

            Iter = ObjectsColliding.erase(Iter);
        }
        else
        {
            if (const auto& [bColliding, Other] = First->Intersects(Second); !bColliding)
            {
                First->GetOwner()->OnCollisionEndOverlap(Second);
                Second->GetOwner()->OnCollisionEndOverlap(First);

                Iter = ObjectsColliding.erase(Iter);
            }
            else
            {
                First->GetOwner()->OnCollisionStayOverlap(Second);
                Second->GetOwner()->OnCollisionStayOverlap(First);

                ++Iter;
            }
        }
    }
}
