#pragma once
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>


#include "../../Algorithm/Quadtree/Quadtree.h"
#include "../../Object/Object.h"
#include "../../Bitmask/Bitmask.h"
#include "../../Hash/ComponentPairHash/ComponentPairHash.h"
#include "../../Hash/EnumHash/EnumClassHash.h"

class ColliderSystem
{
public:
    ColliderSystem(Quadtree& CollisionTree);

    void Add(std::vector<std::shared_ptr<Object>>& Objects);
    void ProcessRemovals();
    void Update();

private:
    void Resolve();
    void ProcessCollidingObjects();

    Quadtree& CollisionTree;

    std::unordered_map<CollisionLayer, Bitmask, EnumClassHash> CollisionLayers;
    std::unordered_map<CollisionLayer, std::vector<std::shared_ptr<BoxColliderComponent>>, EnumClassHash> Collidables;
    std::unordered_set<std::pair<std::shared_ptr<BoxColliderComponent>, std::shared_ptr<BoxColliderComponent>>, ComponentPairHash> ObjectsColliding;
};
