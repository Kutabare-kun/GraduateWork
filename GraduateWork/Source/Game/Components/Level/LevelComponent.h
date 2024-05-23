#pragma once
#include <map>
#include <nlohmann/json.hpp>

#include "../../../Core/Component/ActorComponent.h"

class AttributeComponent;

struct ExperienceLevelTable
{
    unsigned LevelID;
    unsigned Experience;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ExperienceLevelTable, LevelID, Experience);
};

class LevelComponent
    : public ActorComponent
{
public:
    LevelComponent(Object* Owner);

    void Awake() override;

    void ApplyExperience(unsigned Experience);
    void PopUpWidget();

    unsigned GetLevel() const { return Level; }
    bool IsMaxLevel() const { return Level == ExperienceTable.size(); }

protected:
    void LevelUp();

private:
    unsigned Level;
    unsigned CurrentExperience;

    std::map<unsigned, unsigned> ExperienceTable;

    std::shared_ptr<AttributeComponent> OwnerAttribute;
};
