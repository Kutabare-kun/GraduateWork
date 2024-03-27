#pragma once
#include <map>
#include <memory>
#include <vector>


#include "../../Algorithm/Quadtree/Quadtree.h"
#include "../../Object/Object.h"
#include "../../Bitmask/Bitmask.h"

class ColliderSystem
{
public:
    ColliderSystem();

    void Add(std::vector<std::shared_ptr<Object>>& Objects);
    void ProcessRemovals();
    void Update();

private:
    void Resolve();
    void ProcessCollisions(std::vector<std::shared_ptr<Object>>& First, std::vector<std::shared_ptr<Object>>& Second);

    std::map<CollisionLayer, Bitmask> CollisionLayers;

    std::map<CollisionLayer, std::vector<std::shared_ptr<BoxColliderComponent>>> Collidables;

    std::unique_ptr<Quadtree> CollisionTree;
};
