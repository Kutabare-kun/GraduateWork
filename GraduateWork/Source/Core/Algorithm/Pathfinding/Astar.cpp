#include "Astar.h"

#include <iostream>
#include <raymath.h>
#include <set>

Vector2 Astar::GridToVec(const std::pair<int, int>& Position, const int CellSize) const
{
    return Vector2{
        static_cast<float>(Position.first * CellSize),
        static_cast<float>(Position.second * CellSize)
    };
}

std::pair<int, int> Astar::VecToGrid(const Vector2& Position, const int CellSize) const
{
    return std::make_pair<int, int>(static_cast<int>(Position.x / CellSize),
                                    static_cast<int>(Position.y / CellSize));
}

std::pair<bool, std::vector<std::pair<int, int>>> Astar::FindPath(const std::vector<std::vector<bool>>& Grid,
                                                                  const std::pair<int, int>& Start,
                                                                  const std::pair<int, int>& End)
{
    const std::pair GridSize = std::make_pair(Grid.size(), Grid[0].size());
    if (!IsValid(Start, GridSize) || !IsValid(End, GridSize))
    {
        return std::make_pair<bool, std::vector<std::pair<int, int>>>(false, {});
    }

    if (!IsUnblocked(Grid, Start) || !IsUnblocked(Grid, End))
    {
        return std::make_pair<bool, std::vector<std::pair<int, int>>>(false, {});
    }

    if (IsDestination(Start, End))
    {
        return std::make_pair<bool, std::vector<std::pair<int, int>>>(true, {});
    }

    std::vector<std::vector<Cell>> CellDetails(GridSize.first,
                                               std::vector<Cell>(GridSize.second,
                                                                 Cell{
                                                                     std::make_pair<int, int>(-1, -1),
                                                                     FLT_MAX,
                                                                     FLT_MAX,
                                                                     FLT_MAX
                                                                 })
    );

    std::pair<int, int> Position{Start};

    CellDetails[Position.first][Position.second] = Cell{Position, 0, 0, 0};

    std::vector<std::vector<bool>> ClosedList(GridSize.first, std::vector<bool>(GridSize.second, false));
    std::set<std::pair<double, std::pair<int, int>>> OpenList;

    OpenList.insert(std::make_pair(0.0, Position));

    bool bFoundDest = false;

    while (!OpenList.empty())
    {
        std::pair<double, std::pair<int, int>> P = *OpenList.begin();
        OpenList.erase(OpenList.begin());

        Position = std::make_pair(P.second.first, P.second.second);
        ClosedList[Position.first][Position.second] = true;

        double GNew, HNew, FNew;

        const std::vector<std::pair<int, int>> Neighbours = {
            std::make_pair(Position.first - 1, Position.second), // North
            std::make_pair(Position.first + 1, Position.second), // South
            std::make_pair(Position.first, Position.second + 1), // East
            std::make_pair(Position.first, Position.second - 1), // West
            std::make_pair(Position.first - 1, Position.second + 1), // North-East
            std::make_pair(Position.first - 1, Position.second - 1), // North-West
            std::make_pair(Position.first + 1, Position.second + 1), // South-East
            std::make_pair(Position.first + 1, Position.second - 1), // South-West
        };

        enum Compass
        {
            North,
            South,
            East,
            West,
            North_East,
            North_West,
            South_West,
            South_East
        };

        auto CheckPath = [&](int Index) -> bool
        {
            if (IsValid(Neighbours[Index], GridSize))
            {
                if (IsDestination(Neighbours[Index], End))
                {
                    CellDetails[Neighbours[Index].first][Neighbours[Index].second] = Cell{Position, 0, 0, 0};
                    bFoundDest = true;
                    return true;
                }
                else if (!ClosedList[Neighbours[Index].first][Neighbours[Index].second]
                    && IsUnblocked(Grid, Neighbours[Index]))
                {
                    GNew = CellDetails[Position.first][Position.second].G + 1.0;
                    HNew = CalculateHValue(Neighbours[Index], End);
                    FNew = GNew + HNew;

                    if (CellDetails[Neighbours[Index].first][Neighbours[Index].second].F == FLT_MAX
                        || CellDetails[Neighbours[Index].first][Neighbours[Index].second].F > FNew)
                    {
                        OpenList.insert(std::make_pair(FNew, Neighbours[Index]));

                        CellDetails[Neighbours[Index].first][Neighbours[Index].second] = Cell{
                            Position, GNew, HNew, FNew
                        };
                    }
                }
            }

            return false;
        };

        // North
        if (CheckPath(North)) break;
        // ~North

        // South
        if (CheckPath(South)) break;
        // ~South

        // East
        if (CheckPath(East)) break;
        // ~East

        // West
        if (CheckPath(West)) break;
        // ~West

        // North-East
        if (CheckPath(North_East)) break;
        // ~North-East

        // North-West
        if (CheckPath(North_West)) break;
        // ~North-West

        // South-West
        if (CheckPath(South_West)) break;
        // ~South-West

        // South-East
        if (CheckPath(South_East)) break;
        // ~South-East
    }

    if (bFoundDest)
    {
        return MakePath(CellDetails, End);
    }

    return std::make_pair<bool, std::vector<std::pair<int, int>>>(false, {});
}

bool Astar::IsValid(const std::pair<int, int>& Position, const std::pair<int, int>& GridSize) const
{
    return Position.first >= 0
        && Position.first < GridSize.first
        && Position.second >= 0
        && Position.second < GridSize.second;
}

bool Astar::IsUnblocked(const std::vector<std::vector<bool>>& Grid, const std::pair<int, int>& Position) const
{
    return !Grid[Position.second][Position.first];
}

bool Astar::IsDestination(const std::pair<int, int>& Position, const std::pair<int, int>& End) const
{
    return Position.first == End.first
        && Position.second == End.second;
}

double Astar::CalculateHValue(const std::pair<int, int>& Position, const std::pair<int, int>& End) const
{
    return sqrt(pow(Position.first - End.first, 2) + pow(Position.second - End.second, 2));
}

std::pair<bool, std::vector<std::pair<int, int>>> Astar::MakePath(const std::vector<std::vector<Cell>>& CellDetails,
                                                                  const std::pair<int, int>& End) const
{
    std::pair<int, int> Position = End;
    std::vector<std::pair<int, int>> Path;

    while (CellDetails[Position.first][Position.second].Position != Position)
    {
        Path.emplace_back(Position);
        Position = CellDetails[Position.first][Position.second].Position;
    }

    std::reverse(Path.begin(), Path.end());
    return std::make_pair(true, Path);
}
