#pragma once
#include <string>
#include <vector>

#include "raylib.h"
#include "../Pattern/Singleton.h"

class Constructor : public Singleton<Constructor>
{
public:
    std::vector<std::vector<bool>> ReadMap(const std::string& MapPath);
    
    Vector2 ConvertToVector2(std::pair<int, int> Position, int CellSize);
    std::pair<int, int> ConvertToPair(const Vector2& Position, int CellSize);    
};
