#pragma once
#include <vector>

#include "../../Pattern/Singleton.h"
#include <raylib.h>

struct Cell
{
    std::pair<int, int> Position;
    double G;
    double H;
    double F;
};

class Astar : public Singleton<Astar>
{
public:
    std::pair<bool, std::vector<std::pair<int, int>>> FindPath(const std::vector<std::vector<bool>>& Grid,
                                                               const std::pair<int, int>& Start,
                                                               const std::pair<int, int>& End) const;

    Vector2 GridToVec(const std::pair<int, int>& Position, const int CellSize) const;
    std::pair<int, int> VecToGrid(const Vector2& Position, const int CellSize) const;

protected:
    bool IsValid(const std::pair<int, int>& Position, const std::pair<int, int>& GridSize) const;
    bool IsUnblocked(const std::vector<std::vector<bool>>& Grid, const std::pair<int, int>& Position) const;
    bool IsDestination(const std::pair<int, int>& Position, const std::pair<int, int>& End) const;

    double CalculateHValue(const std::pair<int, int>& Position, const std::pair<int, int>& End) const;

    std::pair<bool, std::vector<std::pair<int, int>>> MakePath(const std::vector<std::vector<Cell>>& CellDetails,
                                                               const std::pair<int, int>& End) const;
};