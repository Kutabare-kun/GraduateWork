#pragma once
#include <vector>
#include "raylib.h"

#include "../../../Core/Pattern/Singleton.h"

struct Cell
{
    Vector2 Position;
    double G;
    double H;
    double F;
};

class Astar : public Singleton<Astar>
{
public:
    std::pair<bool, std::vector<Vector2>> FindPath(const std::vector<std::vector<bool>>& Grid,
                                                               const Vector2& Start,
                                                               const Vector2& End);

protected:
    bool IsValid(const Vector2& Position, const Vector2& GridSize) const;
    bool IsUnblocked(const std::vector<std::vector<bool>>& Grid, const Vector2& Position) const;
    bool IsDestination(const Vector2& Position, const Vector2& End) const;

    double CalculateHValue(const Vector2& Position, const Vector2& End) const;

    std::pair<bool, std::vector<Vector2>> MakePath(const std::vector<std::vector<Cell>>& CellDetails,
                                                               const Vector2& End) const;
};
