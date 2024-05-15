#include "Astar.h"

#include <iostream>
#include <raymath.h>
#include <set>

struct PairComparator {
    bool operator()(const std::pair<double, Vector2>& a, const std::pair<double, Vector2>& b) const {
        // Compare the pairs based on the double value
        return a.first < b.first;
    }
};

std::pair<bool, std::vector<Vector2>> Astar::FindPath(const std::vector<std::vector<bool>>& Grid,
                                                                  const Vector2& Start, const Vector2& End)
{
    const Vector2 GridSize = Vector2{static_cast<float>(Grid.size()), static_cast<float>(Grid[0].size())};
    if (!IsValid(Start, GridSize) || !IsValid(End, GridSize))
    {
        return std::make_pair<bool, std::vector<Vector2>>(false, {});
    }

    if (!IsUnblocked(Grid, Start) || !IsUnblocked(Grid, End))
    {
        return std::make_pair<bool, std::vector<Vector2>>(false, {});
    }

    if (IsDestination(Start, End))
    {
        return std::make_pair<bool, std::vector<Vector2>>(true, {});
    }

    std::vector<std::vector<Cell>> CellDetails(static_cast<int>(GridSize.x),
                                               std::vector<Cell>(static_cast<int>(GridSize.y),
                                                                 Cell{
                                                                     Vector2{-1, -1},
                                                                     FLT_MAX,
                                                                     FLT_MAX,
                                                                     FLT_MAX
                                                                 })
    );

    Vector2 Position{Start};

    CellDetails[static_cast<int>(Position.x)][static_cast<int>(Position.y)] = Cell{Position, 0, 0, 0};

    std::vector<std::vector<bool>> ClosedList(static_cast<int>(GridSize.x), std::vector<bool>(static_cast<int>(GridSize.y), false));
    std::set<std::pair<double, Vector2>, PairComparator> OpenList;

    OpenList.insert(std::make_pair(0.0, Position));

    bool bFoundDest = false;

    while (!OpenList.empty())
    {
        std::pair<double, Vector2> P = *OpenList.begin();
        OpenList.erase(OpenList.begin());

        Position = {P.second.x, P.second.y};
        ClosedList[static_cast<int>(Position.x)][static_cast<int>(Position.y)] = true;

        double GNew, HNew, FNew;

        const std::vector<Vector2> Neighbours {
            {Position.x - 1, Position.y},              // North
            {Position.x + 1, Position.y},              // South
            {Position.x, Position.y + 1},              // East
            {Position.x, Position.y - 1},              // West
            {Position.x - 1, Position.y + 1},       // North-East
            {Position.x - 1, Position.y - 1},       // North-West
            {Position.x + 1, Position.y + 1},       // South-East
            {Position.x + 1, Position.y - 1},       // South-West
        };

        enum Compass
        {
            North,
            South,
            East,
            West,
            NorthEast,
            NorthWest,
            SouthWest,
            SouthEast
        };

        // North
        if (IsValid(Neighbours[North], GridSize))
        {
            if (IsDestination(Neighbours[North], End))
            {
                CellDetails[static_cast<int>(Neighbours[North].x)][static_cast<int>(Neighbours[North].y)] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[static_cast<int>(Neighbours[North].x)][static_cast<int>(Neighbours[North].y)]
                && IsUnblocked(Grid, Neighbours[North]))
            {
                GNew = CellDetails[static_cast<int>(Position.x)][static_cast<int>(Position.y)].G + 1.0;
                HNew = CalculateHValue(Neighbours[North], End);
                FNew = GNew + HNew;

                if (CellDetails[static_cast<int>(Neighbours[North].x)][static_cast<int>(Neighbours[North].y)].F == FLT_MAX
                    || CellDetails[static_cast<int>(Neighbours[North].x)][static_cast<int>(Neighbours[North].y)].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[North]));

                    CellDetails[static_cast<int>(Neighbours[North].x)][static_cast<int>(Neighbours[North].y)] = Cell{Position, GNew, HNew, FNew};
                }
            }
        }
        // ~North

        // South
        if (IsValid(Neighbours[South], GridSize))
        {
            if (IsDestination(Neighbours[South], End))
            {
                CellDetails[static_cast<int>(static_cast<int>(Neighbours[South].x))][static_cast<int>(Neighbours[South].y)] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[static_cast<int>(Neighbours[South].x)][static_cast<int>(Neighbours[South].y)]
                && IsUnblocked(Grid, Neighbours[South]))
            {
                GNew = CellDetails[static_cast<int>(Position.x)][static_cast<int>(Position.y)].G + 1.0;
                HNew = CalculateHValue(Neighbours[South], End);
                FNew = GNew + HNew;

                if (CellDetails[static_cast<int>(Neighbours[South].x)][static_cast<int>(Neighbours[South].y)].F == FLT_MAX
                    || CellDetails[static_cast<int>(Neighbours[South].x)][static_cast<int>(Neighbours[South].y)].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[South]));

                    CellDetails[static_cast<int>(Neighbours[South].x)][static_cast<int>(Neighbours[South].y)] = Cell{Position, GNew, HNew, FNew};
                }
            }
        }
        // ~South

        // East
        if (IsValid(Neighbours[East], GridSize))
        {
            if (IsDestination(Neighbours[East], End))
            {
                CellDetails[static_cast<int>(Neighbours[East].x)][static_cast<int>(Neighbours[East].y)] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[static_cast<int>(Neighbours[East].x)][static_cast<int>(Neighbours[East].y)]
                && IsUnblocked(Grid, Neighbours[East]))
            {
                GNew = CellDetails[static_cast<int>(Position.x)][static_cast<int>(Position.y)].G + 1.0;
                HNew = CalculateHValue(Neighbours[East], End);
                FNew = GNew + HNew;

                if (CellDetails[static_cast<int>(Neighbours[East].x)][static_cast<int>(Neighbours[East].y)].F == FLT_MAX
                    || CellDetails[static_cast<int>(Neighbours[East].x)][static_cast<int>(Neighbours[East].y)].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[East]));

                    CellDetails[static_cast<int>(Neighbours[East].x)][static_cast<int>(Neighbours[East].y)] = Cell{Position, GNew, HNew, FNew};
                }
            }
        }
        // ~East

        // West
        if (IsValid(Neighbours[West], GridSize))
        {
            if (IsDestination(Neighbours[West], End))
            {
                CellDetails[static_cast<int>(Neighbours[West].x)][static_cast<int>(Neighbours[West].y)] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[static_cast<int>(Neighbours[West].x)][static_cast<int>(Neighbours[West].y)]
                && IsUnblocked(Grid, Neighbours[West]))
            {
                GNew = CellDetails[static_cast<int>(Position.x)][static_cast<int>(Position.y)].G + 1.0;
                HNew = CalculateHValue(Neighbours[West], End);
                FNew = GNew + HNew;

                if (CellDetails[static_cast<int>(Neighbours[West].x)][static_cast<int>(Neighbours[West].y)].F == FLT_MAX
                    || CellDetails[static_cast<int>(Neighbours[West].x)][static_cast<int>(Neighbours[West].y)].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[West]));

                    CellDetails[static_cast<int>(Neighbours[West].x)][static_cast<int>(Neighbours[West].y)] = Cell{Position, GNew, HNew, FNew};
                }
            }
        }
        // ~West

        // North-East
        if (IsValid(Neighbours[NorthEast], GridSize))
        {
            if (IsDestination(Neighbours[NorthEast], End))
            {
                CellDetails[static_cast<int>(Neighbours[NorthEast].x)][static_cast<int>(Neighbours[NorthEast].y)] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[static_cast<int>(Neighbours[NorthEast].x)][static_cast<int>(Neighbours[NorthEast].y)]
                && IsUnblocked(Grid, Neighbours[NorthEast]))
            {
                GNew = CellDetails[static_cast<int>(Position.x)][static_cast<int>(Position.y)].G + 1.0;
                HNew = CalculateHValue(Neighbours[NorthEast], End);
                FNew = GNew + HNew;
        
                if (CellDetails[static_cast<int>(Neighbours[NorthEast].x)][static_cast<int>(Neighbours[NorthEast].y)].F == FLT_MAX
                    || CellDetails[static_cast<int>(Neighbours[NorthEast].x)][static_cast<int>(Neighbours[NorthEast].y)].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[NorthEast]));
        
                    CellDetails[static_cast<int>(Neighbours[NorthEast].x)][static_cast<int>(Neighbours[NorthEast].y)] = Cell{
                        Position, GNew, HNew, FNew
                    };
                }
            }
        }
        // ~North-East
        
        // North-West
        if (IsValid(Neighbours[NorthWest], GridSize))
        {
            if (IsDestination(Neighbours[NorthWest], End))
            {
                CellDetails[static_cast<int>(Neighbours[NorthWest].x)][static_cast<int>(Neighbours[NorthWest].y)] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[static_cast<int>(Neighbours[NorthWest].x)][static_cast<int>(Neighbours[NorthWest].y)]
                && IsUnblocked(Grid, Neighbours[NorthWest]))
            {
                GNew = CellDetails[static_cast<int>(Position.x)][static_cast<int>(Position.y)].G + 1.0;
                HNew = CalculateHValue(Neighbours[NorthWest], End);
                FNew = GNew + HNew;
        
                if (CellDetails[static_cast<int>(Neighbours[NorthWest].x)][static_cast<int>(Neighbours[NorthWest].y)].F == FLT_MAX
                    || CellDetails[static_cast<int>(Neighbours[NorthWest].x)][static_cast<int>(Neighbours[NorthWest].y)].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[NorthWest]));
        
                    CellDetails[static_cast<int>(Neighbours[NorthWest].x)][static_cast<int>(Neighbours[NorthWest].y)] = Cell{
                        Position, GNew, HNew, FNew
                    };
                }
            }
        }
        // ~North-West
        
        // South-West
        if (IsValid(Neighbours[SouthWest], GridSize))
        {
            if (IsDestination(Neighbours[SouthWest], End))
            {
                CellDetails[static_cast<int>(Neighbours[SouthWest].x)][static_cast<int>(Neighbours[SouthWest].y)] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[static_cast<int>(Neighbours[SouthWest].x)][static_cast<int>(Neighbours[SouthWest].y)]
                && IsUnblocked(Grid, Neighbours[SouthWest]))
            {
                GNew = CellDetails[static_cast<int>(Position.x)][static_cast<int>(Position.y)].G + 1.0;
                HNew = CalculateHValue(Neighbours[SouthWest], End);
                FNew = GNew + HNew;
        
                if (CellDetails[static_cast<int>(Neighbours[SouthWest].x)][static_cast<int>(Neighbours[SouthWest].y)].F == FLT_MAX
                    || CellDetails[static_cast<int>(Neighbours[SouthWest].x)][static_cast<int>(Neighbours[SouthWest].y)].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[SouthWest]));
        
                    CellDetails[static_cast<int>(Neighbours[SouthWest].x)][static_cast<int>(Neighbours[SouthWest].y)] = Cell{
                        Position, GNew, HNew, FNew
                    };
                }
            }
        }
        // ~South-West
        
        // South-East
        if (IsValid(Neighbours[SouthEast], GridSize))
        {
            if (IsDestination(Neighbours[SouthEast], End))
            {
                CellDetails[static_cast<int>(Neighbours[SouthEast].x)][static_cast<int>(Neighbours[SouthEast].y)] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[static_cast<int>(Neighbours[SouthEast].x)][static_cast<int>(Neighbours[SouthEast].y)] && IsUnblocked(
                Grid, Neighbours[SouthEast]))
            {
                GNew = CellDetails[static_cast<int>(Position.x)][static_cast<int>(Position.y)].G + 1.0;
                HNew = CalculateHValue(Neighbours[SouthEast], End);
                FNew = GNew + HNew;
        
                if (CellDetails[static_cast<int>(Neighbours[SouthEast].x)][static_cast<int>(Neighbours[SouthEast].y)].F == FLT_MAX
                    || CellDetails[static_cast<int>(Neighbours[SouthEast].x)][static_cast<int>(Neighbours[SouthEast].y)].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[SouthEast]));
        
                    CellDetails[static_cast<int>(Neighbours[SouthEast].x)][static_cast<int>(Neighbours[SouthEast].y)] = Cell{
                        Position, GNew, HNew, FNew
                    };
                }
            }
        }
        // ~South-East
    }

    if (bFoundDest)
    {
        return MakePath(CellDetails, End);
    }

    return std::make_pair<bool, std::vector<Vector2>>(false, {});
}

bool Astar::IsValid(const Vector2& Position, const Vector2& GridSize) const
{
    return Position.x >= 0
        && Position.x < GridSize.x
        && Position.y >= 0
        && Position.y < GridSize.y;
}

bool Astar::IsUnblocked(const std::vector<std::vector<bool>>& Grid, const Vector2& Position) const
{
    return !Grid[static_cast<int>(Position.x)][static_cast<int>(Position.y)];
}

bool Astar::IsDestination(const Vector2& Position, const Vector2& End) const
{
    return static_cast<int>(Position.x) == static_cast<int>(End.x)
        && static_cast<int>(Position.y) == static_cast<int>(End.y);
}

double Astar::CalculateHValue(const Vector2& Position, const Vector2& End) const
{
    return sqrt(pow(Position.x - End.x, 2) + pow(Position.y - End.y, 2));
}

std::pair<bool, std::vector<Vector2>> Astar::MakePath(const std::vector<std::vector<Cell>>& CellDetails,
                                                                  const Vector2& End) const
{
    Vector2 Position = End;
    std::vector<Vector2> Path;

    while (!Vector2Equals(CellDetails[static_cast<int>(Position.x)][static_cast<int>(Position.y)].Position, Position))
    {
        Path.emplace_back(Position);
        Position = CellDetails[static_cast<int>(Position.x)][static_cast<int>(Position.y)].Position;
    }

    std::reverse(Path.begin(), Path.end());
    return std::make_pair(true, Path);
}
