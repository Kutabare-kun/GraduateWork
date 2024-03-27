#include "Quadtree.h"

#include "../../Object/Object.h"

Quadtree::Quadtree()
    : Quadtree(5, 5, 0, Rectangle{0, 0, 0, 0}, nullptr)
{
}

Quadtree::Quadtree(int MaxObjects, int MaxLevels, int Level, Rectangle Bounds, Quadtree* Parent)
    : MaxObjects(MaxObjects), MaxLevels(MaxLevels), Level(Level), Bounds(Bounds), Parent(Parent)
{
}

void Quadtree::Insert(std::shared_ptr<BoxColliderComponent> Object)
{
    if (Children[0] != nullptr)
    {
        int IndexToPlaceObject = GetChildIndex(Object->GetCollidable());

        if (IndexToPlaceObject != ThisTree)
        {
            Children[IndexToPlaceObject]->Insert(Object);
            return;
        }
    }

    Objects.emplace_back(Object);

    if (Objects.size() > MaxObjects
        && Level < MaxLevels
        && Children[0] == nullptr)
    {
        Split();

        auto Iter = Objects.begin();
        while (Iter != Objects.end())
        {
            int IndexToPlaceObject = GetChildIndex((*Iter)->GetCollidable());

            if (IndexToPlaceObject != ThisTree)
            {
                Children[IndexToPlaceObject]->Insert(*Iter);
                Iter = Objects.erase(Iter);
            }
            else
            {
                ++Iter;
            }
        }
    }
}

void Quadtree::Remove(std::shared_ptr<BoxColliderComponent> Object)
{
    int ChildIndex = GetChildIndex(Object->GetCollidable());

    if (ChildIndex == ThisTree || Children[ChildIndex] == nullptr)
    {
        for (int Index = 0; Index < Objects.size(); ++Index)
        {
            if (Objects.at(Index)->GetOwner()->GetInstanceID()->GetInstanceID() == Object->
                GetOwner()->GetInstanceID()->GetInstanceID())
            {
                Objects.erase(Objects.begin() + Index);
                break;
            }
        }
    }
    else
    {
        Children[ChildIndex]->Remove(Object);
    }
}

void Quadtree::Clear()
{
    Objects.clear();
    for (int Index = 0; Index < 4; ++Index)
    {
        if (Children[Index])
        {
            Children[Index]->Clear();
            Children[Index] = nullptr;
        }
    }
}

std::vector<std::shared_ptr<BoxColliderComponent>> Quadtree::Search(const Rectangle& Area)
{
    std::vector<std::shared_ptr<BoxColliderComponent>> PossibleOverlaps;
    Search(Area, PossibleOverlaps);

    std::vector<std::shared_ptr<BoxColliderComponent>> ReturnList;

    for (auto& Collider : PossibleOverlaps)
    {
        if (CheckCollisionRecs(Area, Collider->GetCollidable()))
        {
            ReturnList.emplace_back(Collider);
        }
    }

    return ReturnList;
}

const Rectangle& Quadtree::GetBounds() const
{
    return Bounds;
}

void Quadtree::Search(const Rectangle& Area, std::vector<std::shared_ptr<BoxColliderComponent>>& OverlappingObjects)
{
    OverlappingObjects.insert(OverlappingObjects.end(), Objects.begin(), Objects.end());

    if (Children[0] == nullptr) return;
    int IndexToSearch = GetChildIndex(Area);

    if (IndexToSearch != ThisTree)
    {
        Children[IndexToSearch]->Search(Area, OverlappingObjects);
    }
    else
    {
        for (int Index = 0; Index < 4; ++Index)
        {
            if (CheckCollisionRecs(Area, Children[Index]->GetBounds()))
            {
                Children[Index]->Search(Area, OverlappingObjects);
            }
        }
    }
}

int Quadtree::GetChildIndex(const Rectangle& ObjectBounds) const
{
    int Index{-1};

    const double VerticalDividingLine = Bounds.x + Bounds.width / 2.0f;
    const double HorizontalDividingLine = Bounds.y + Bounds.height / 2.0f;

    const bool North = ObjectBounds.y < HorizontalDividingLine && ObjectBounds.y + ObjectBounds.height <
        HorizontalDividingLine;
    const bool South = ObjectBounds.y > HorizontalDividingLine;
    const bool West = ObjectBounds.x < VerticalDividingLine && ObjectBounds.x + ObjectBounds.width <
        VerticalDividingLine;
    const bool East = ObjectBounds.x > VerticalDividingLine;

    if (West && North)
    {
        Index = ChildNW;
    }
    else if (East && North)
    {
        Index = ChildNE;
    }
    else if (West && South)
    {
        Index = ChildSW;
    }
    else if (East && South)
    {
        Index = ChildSE;
    }

    return Index;
}

void Quadtree::Split()
{
    const float ChildWidth = Bounds.width / 2.0f;
    const float ChildHeight = Bounds.height / 2.0f;

    Children[ChildNE] = std::make_shared<Quadtree>(MaxObjects, MaxLevels, Level + 1,
                                                   Rectangle{Bounds.x + ChildWidth, Bounds.y, ChildWidth, ChildHeight},
                                                   this);
    Children[ChildNW] = std::make_shared<Quadtree>(MaxObjects, MaxLevels, Level + 1,
                                                   Rectangle{Bounds.x, Bounds.y, ChildWidth, ChildHeight},
                                                   this);
    Children[ChildSW] = std::make_shared<Quadtree>(MaxObjects, MaxLevels, Level + 1,
                                                   Rectangle{Bounds.x, Bounds.y + ChildHeight, ChildWidth, ChildHeight},
                                                   this);
    Children[ChildSE] = std::make_shared<Quadtree>(MaxObjects, MaxLevels, Level + 1,
                                                   Rectangle{Bounds.x + ChildWidth, Bounds.y + ChildHeight, ChildWidth,
                                                             ChildHeight},
                                                   this);
}
