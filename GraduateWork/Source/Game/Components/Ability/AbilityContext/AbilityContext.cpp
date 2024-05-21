#include "AbilityContext.h"

#include <fstream>

#include "../../../../Core/Directory/Directory.h"
#include "../../../../Core/Timer/Timer.h"

using Json = nlohmann::json;

AbilityContext::AbilityContext(const std::string&& AbilityName, AbilityTag Tag, unsigned MaxLevel)
    : ClampLevel(MaxLevel), Name(AbilityName), Tag(Tag)
{
    Json AbilityInfoJson;
    std::ifstream AbilityInfoFile(Directory::GetInstance().GetData("Ability.json"));
    AbilityInfoFile >> AbilityInfoJson;

    std::vector<AbilityInfo> Info = AbilityInfoJson[Name];
    for (size_t Index = 0; Index < Info.size(); ++Index)
        InfoByLevel.emplace(Index + 1, Info[Index]);
}

AbilityContext::~AbilityContext()
{
    AbilityTimer->UpdateTimer(false);
}

void AbilityContext::LevelUp()
{
    Level = std::clamp<unsigned>(Level + 1U, 1U, ClampLevel);
    AbilityTimer->UpdateTimer(InfoByLevel[Level].Cooldown);
}
