#include "Constructor.h"
#include <fstream>

std::vector<std::vector<bool>> Constructor::ReadMap(const std::string& MapPath)
{
    std::fstream MapFile(MapPath);
    std::vector<std::vector<bool>> Map;

    if (MapFile.is_open())
    {
        std::string Line;
        while (std::getline(MapFile, Line))
        {
            std::vector<bool> MapLine;
            for (const char& Char : Line)
            {
                if (Char == '0')
                {
                    MapLine.emplace_back(false);
                }
                else if (Char == '1')
                {
                    MapLine.emplace_back(true);
                }
            }

            MapLine.shrink_to_fit();
            Map.emplace_back(MapLine);
        }
    }

    Map.shrink_to_fit();
    MapFile.close();

    return Map;
}

Vector2 Constructor::ConvertToVector2(std::pair<int, int> Position, int CellSize)
{
    return Vector2{
        static_cast<float>(Position.first * CellSize + CellSize / 2.0f),
        static_cast<float>(Position.second * CellSize + CellSize / 2.0f)
    };
}

std::pair<int, int> Constructor::ConvertToPair(const Vector2& Position, int CellSize)
{
    return std::make_pair(static_cast<int>(Position.x / (float)CellSize),
                          static_cast<int>(Position.y / (float)CellSize)
    );
}
