#include "Astar.h"

#include <iostream>
#include <set>

#include "../../StaticFunctions/Debug.h"

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

    {
        int RowCount{};
        int ColumnCount{};
        constexpr float SIZE{256.0f}; 

        for (auto& Row : Grid)
        {
            for (auto&& Column : Row)
            {
                Debug::GetInstance().DrawRectangle({RowCount * SIZE, ColumnCount * SIZE, SIZE, SIZE}, Column ? BLUE : DARKGREEN);

                ++RowCount;
            }
            ++ColumnCount;
            RowCount = 0;
        }
    }

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
        if (IsValid(Neighbours[North_East], GridSize))
        {
            if (IsDestination(Neighbours[North_East], End))
            {
                CellDetails[Neighbours[North_East].first][Neighbours[North_East].second] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[Neighbours[North_East].first][Neighbours[North_East].second]
                && IsUnblocked(Grid, Neighbours[North_East]))
            {
                GNew = CellDetails[Position.first][Position.second].G + 1.0;
                HNew = CalculateHValue(Neighbours[North_East], End);
                FNew = GNew + HNew;

                if (CellDetails[Neighbours[North_East].first][Neighbours[North_East].second].F == FLT_MAX
                    || CellDetails[Neighbours[North_East].first][Neighbours[North_East].second].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[North_East]));

                    CellDetails[Neighbours[North_East].first][Neighbours[North_East].second] = Cell{
                        Position, GNew, HNew, FNew
                    };
                }
            }
        }
        // ~North-East

        // North-West
        if (IsValid(Neighbours[North_West], GridSize))
        {
            if (IsDestination(Neighbours[North_West], End))
            {
                CellDetails[Neighbours[North_West].first][Neighbours[North_West].second] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[Neighbours[North_West].first][Neighbours[North_West].second]
                && IsUnblocked(Grid, Neighbours[North_West]))
            {
                GNew = CellDetails[Position.first][Position.second].G + 1.0;
                HNew = CalculateHValue(Neighbours[North_West], End);
                FNew = GNew + HNew;

                if (CellDetails[Neighbours[North_West].first][Neighbours[North_West].second].F == FLT_MAX
                    || CellDetails[Neighbours[North_West].first][Neighbours[North_West].second].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[North_West]));

                    CellDetails[Neighbours[North_West].first][Neighbours[North_West].second] = Cell{
                        Position, GNew, HNew, FNew
                    };
                }
            }
        }
        // ~North-West

        // South-West
        if (IsValid(Neighbours[South_West], GridSize))
        {
            if (IsDestination(Neighbours[South_West], End))
            {
                CellDetails[Neighbours[South_West].first][Neighbours[South_West].second] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[Neighbours[South_West].first][Neighbours[South_West].second]
                && IsUnblocked(Grid, Neighbours[South_West]))
            {
                GNew = CellDetails[Position.first][Position.second].G + 1.0;
                HNew = CalculateHValue(Neighbours[South_West], End);
                FNew = GNew + HNew;

                if (CellDetails[Neighbours[South_West].first][Neighbours[South_West].second].F == FLT_MAX
                    || CellDetails[Neighbours[South_West].first][Neighbours[South_West].second].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[South_West]));

                    CellDetails[Neighbours[South_West].first][Neighbours[South_West].second] = Cell{
                        Position, GNew, HNew, FNew
                    };
                }
            }
        }
        // ~South-West

        // South-East
        if (IsValid(Neighbours[South_East], GridSize))
        {
            if (IsDestination(Neighbours[South_East], End))
            {
                CellDetails[Neighbours[South_East].first][Neighbours[South_East].second] = Cell{Position, 0, 0, 0};
                bFoundDest = true;
                break;
            }
            else if (!ClosedList[Neighbours[South_East].first][Neighbours[South_East].second] && IsUnblocked(
                Grid, Neighbours[South_East]))
            {
                GNew = CellDetails[Position.first][Position.second].G + 1.0;
                HNew = CalculateHValue(Neighbours[South_East], End);
                FNew = GNew + HNew;

                if (CellDetails[Neighbours[South_East].first][Neighbours[South_East].second].F == FLT_MAX
                    || CellDetails[Neighbours[South_East].first][Neighbours[South_East].second].F > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, Neighbours[South_East]));

                    CellDetails[Neighbours[South_East].first][Neighbours[South_East].second] = Cell{
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
