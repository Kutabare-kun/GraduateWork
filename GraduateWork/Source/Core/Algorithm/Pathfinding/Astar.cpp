#include "Astar.h"

#include <iostream>
#include <set>

std::pair<bool, std::vector<std::pair<int, int>>> Astar::FindPath(const std::vector<std::vector<bool>>& Grid,
                                                                  const std::pair<int, int>& Start, const std::pair<int, int>& End)
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

        const std::vector<std::pair<int, int>> Neighbours {
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
                CellDetails[Neighbours[North].first][Neighbours[North].second] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[Neighbours[North].first][Neighbours[North].second]
                && IsUnblocked(Grid, Neighbours[North]))
            {
                GNew = CellDetails[Position.first][Position.second].G + 1.0;
                HNew = CalculateHValue(Neighbours[North], End);
                FNew = GNew + HNew;

                if (CellDetails[Neighbours[North].first][Neighbours[North].second].F == FLT_MAX
                    || CellDetails[Neighbours[North].first][Neighbours[North].second].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[North]));

                    CellDetails[Neighbours[North].first][Neighbours[North].second] = Cell{Position, GNew, HNew, FNew};
                }
            }
        }
        // ~North

        // South
        if (IsValid(Neighbours[South], GridSize))
        {
            if (IsDestination(Neighbours[South], End))
            {
                CellDetails[Neighbours[South].first][Neighbours[South].second] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[Neighbours[South].first][Neighbours[South].second]
                && IsUnblocked(Grid, Neighbours[South]))
            {
                GNew = CellDetails[Position.first][Position.second].G + 1.0;
                HNew = CalculateHValue(Neighbours[South], End);
                FNew = GNew + HNew;

                if (CellDetails[Neighbours[South].first][Neighbours[South].second].F == FLT_MAX
                    || CellDetails[Neighbours[South].first][Neighbours[South].second].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[South]));

                    CellDetails[Neighbours[South].first][Neighbours[South].second] = Cell{Position, GNew, HNew, FNew};
                }
            }
        }
        // ~South

        // East
        if (IsValid(Neighbours[East], GridSize))
        {
            if (IsDestination(Neighbours[East], End))
            {
                CellDetails[Neighbours[East].first][Neighbours[East].second] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[Neighbours[East].first][Neighbours[East].second]
                && IsUnblocked(Grid, Neighbours[East]))
            {
                GNew = CellDetails[Position.first][Position.second].G + 1.0;
                HNew = CalculateHValue(Neighbours[East], End);
                FNew = GNew + HNew;

                if (CellDetails[Neighbours[East].first][Neighbours[East].second].F == FLT_MAX
                    || CellDetails[Neighbours[East].first][Neighbours[East].second].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[East]));

                    CellDetails[Neighbours[East].first][Neighbours[East].second] = Cell{Position, GNew, HNew, FNew};
                }
            }
        }
        // ~East

        // West
        if (IsValid(Neighbours[West], GridSize))
        {
            if (IsDestination(Neighbours[West], End))
            {
                CellDetails[Neighbours[West].first][Neighbours[West].second] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[Neighbours[West].first][Neighbours[West].second]
                && IsUnblocked(Grid, Neighbours[West]))
            {
                GNew = CellDetails[Position.first][Position.second].G + 1.0;
                HNew = CalculateHValue(Neighbours[West], End);
                FNew = GNew + HNew;

                if (CellDetails[Neighbours[West].first][Neighbours[West].second].F == FLT_MAX
                    || CellDetails[Neighbours[West].first][Neighbours[West].second].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[West]));

                    CellDetails[Neighbours[West].first][Neighbours[West].second] = Cell{Position, GNew, HNew, FNew};
                }
            }
        }
        // ~West

        // North-East
        if (IsValid(Neighbours[NorthEast], GridSize))
        {
            if (IsDestination(Neighbours[NorthEast], End))
            {
                CellDetails[Neighbours[NorthEast].first][Neighbours[NorthEast].second] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[Neighbours[NorthEast].first][Neighbours[NorthEast].second]
                && IsUnblocked(Grid, Neighbours[NorthEast]))
            {
                GNew = CellDetails[Position.first][Position.second].G + 1.0;
                HNew = CalculateHValue(Neighbours[NorthEast], End);
                FNew = GNew + HNew;
        
                if (CellDetails[Neighbours[NorthEast].first][Neighbours[NorthEast].second].F == FLT_MAX
                    || CellDetails[Neighbours[NorthEast].first][Neighbours[NorthEast].second].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[NorthEast]));
        
                    CellDetails[Neighbours[NorthEast].first][Neighbours[NorthEast].second] = Cell{
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
                CellDetails[Neighbours[NorthWest].first][Neighbours[NorthWest].second] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[Neighbours[NorthWest].first][Neighbours[NorthWest].second]
                && IsUnblocked(Grid, Neighbours[NorthWest]))
            {
                GNew = CellDetails[Position.first][Position.second].G + 1.0;
                HNew = CalculateHValue(Neighbours[NorthWest], End);
                FNew = GNew + HNew;
        
                if (CellDetails[Neighbours[NorthWest].first][Neighbours[NorthWest].second].F == FLT_MAX
                    || CellDetails[Neighbours[NorthWest].first][Neighbours[NorthWest].second].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[NorthWest]));
        
                    CellDetails[Neighbours[NorthWest].first][Neighbours[NorthWest].second] = Cell{
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
                CellDetails[Neighbours[SouthWest].first][Neighbours[SouthWest].second] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[Neighbours[SouthWest].first][Neighbours[SouthWest].second]
                && IsUnblocked(Grid, Neighbours[SouthWest]))
            {
                GNew = CellDetails[Position.first][Position.second].G + 1.0;
                HNew = CalculateHValue(Neighbours[SouthWest], End);
                FNew = GNew + HNew;
        
                if (CellDetails[Neighbours[SouthWest].first][Neighbours[SouthWest].second].F == FLT_MAX
                    || CellDetails[Neighbours[SouthWest].first][Neighbours[SouthWest].second].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[SouthWest]));
        
                    CellDetails[Neighbours[SouthWest].first][Neighbours[SouthWest].second] = Cell{
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
                CellDetails[Neighbours[SouthEast].first][Neighbours[SouthEast].second] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[Neighbours[SouthEast].first][Neighbours[SouthEast].second] && IsUnblocked(
                Grid, Neighbours[SouthEast]))
            {
                GNew = CellDetails[Position.first][Position.second].G + 1.0;
                HNew = CalculateHValue(Neighbours[SouthEast], End);
                FNew = GNew + HNew;
        
                if (CellDetails[Neighbours[SouthEast].first][Neighbours[SouthEast].second].F == FLT_MAX
                    || CellDetails[Neighbours[SouthEast].first][Neighbours[SouthEast].second].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[SouthEast]));
        
                    CellDetails[Neighbours[SouthEast].first][Neighbours[SouthEast].second] = Cell{
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
    return !Grid[Position.first][Position.second];
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
