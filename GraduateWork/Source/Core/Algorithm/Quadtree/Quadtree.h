#pragma once
#include <memory>
#include <raylib.h>
#include <vector>

#include "../../Component/Collider/BoxCollider/BoxColliderComponent.h"

class Quadtree
{
public:
    Quadtree();
    Quadtree(int MaxObjects, int MaxLevels, int Level, Rectangle Bounds, Quadtree* Parent);

    void Insert(std::shared_ptr<BoxColliderComponent> Object);

    void Remove(std::shared_ptr<BoxColliderComponent> Object);

    void Clear();

    std::vector<std::shared_ptr<BoxColliderComponent>> Search(const Rectangle& Area);

    const Rectangle& GetBounds() const;

private:
    void Search(const Rectangle& Area, std::vector<std::shared_ptr<BoxColliderComponent>>& OverlappingObjects);

    int GetChildIndex(const Rectangle& ObjectBounds) const;

    void Split();

    static const int ThisTree = -1;
    static const int ChildNE = 0;
    static const int ChildNW = 1;
    static const int ChildSW = 2;
    static const int ChildSE = 3;

    int MaxObjects;
    int MaxLevels;

    Quadtree* Parent;
    std::shared_ptr<Quadtree> Children[4];

    std::vector<std::shared_ptr<BoxColliderComponent>> Objects;

    int Level;

    Rectangle Bounds;
};
