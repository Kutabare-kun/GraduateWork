#include "AbilityContext.h"

#include <fstream>

#include "../../../../Core/Directory/Directory.h"
#include "../../../../Core/StaticFunctions/Debug.h"
#include "../../../../Core/Timer/Timer.h"

using Json = nlohmann::json;

AbilityContext::AbilityContext(const std::string&& AbilityName, AbilityTag Tag)
    : Name(AbilityName), Tag(Tag)
{
    Json AbilityInfoJson;
    std::ifstream AbilityInfoFile(Directory::GetInstance().GetData("Ability.json"));
    AbilityInfoFile >> AbilityInfoJson;

    unsigned Count{};

    auto Info = AbilityInfoJson[Name];
    for (const auto& BasicJsons : Info)
    {
        AbilityInfo ThisInfo = BasicJsons["Level"].get<AbilityInfo>();
        InfoByLevel.emplace(Count + 1, ThisInfo);
        ++Count;
    }

    ClampLevel = Count;
}

void AbilityContext::LevelUp()
{
    Level = std::clamp<unsigned>(Level + 1U, 1U, ClampLevel);
    AbilityTimer->UpdateTimer(InfoByLevel[Level].Cooldown);
}
