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
