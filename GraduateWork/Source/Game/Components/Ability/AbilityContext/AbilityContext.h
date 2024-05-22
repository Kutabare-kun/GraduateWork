#pragma once
#include <nlohmann/json.hpp>

class Timer;
enum class AbilityTag;

struct AbilityInfo
{
    float Cooldown;
    float Damage;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(AbilityInfo, Cooldown, Damage)
};

class AbilityContext
{
public:
    AbilityContext(const std::string&& AbilityName, AbilityTag Tag);

    void LevelUp();

    void SetAbilityTimer(std::shared_ptr<Timer>& NewTimer) { AbilityTimer = NewTimer; }

    const AbilityInfo& GetInfo() { return InfoByLevel[Level]; }
    const std::string& GetName() { return Name; }
    AbilityTag GetAbilityTag() const { return Tag; }

private:
    unsigned Level = 1;
    unsigned ClampLevel;

    std::shared_ptr<Timer> AbilityTimer;

    std::map<unsigned, AbilityInfo> InfoByLevel;

    std::string Name;
    AbilityTag Tag;
};
