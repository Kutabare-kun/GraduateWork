#pragma once

class LevelComponent;

class Ilevel
{
public:
    virtual unsigned GetLevel() const = 0;
    virtual std::shared_ptr<LevelComponent> GetLevelComp() const = 0;
};
