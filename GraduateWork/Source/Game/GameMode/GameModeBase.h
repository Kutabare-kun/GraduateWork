#pragma once
#include <map>
#include <memory>
#include <vector>

#include <nlohmann/json.hpp>

#include "../../Core/Object/Actor/Actor.h"

struct SharedContext;
class Object;
class ObjectCollection;

struct EnemyInfo
{
    unsigned Experience;
    unsigned Count;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(EnemyInfo, Experience, Count);
};

struct EnemyWaveInfo
{
    EnemyInfo Slime;
    EnemyInfo Goblin;
    EnemyInfo Eye;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(EnemyWaveInfo, Slime, Goblin, Eye);
};

enum class PowerUpType
{
    HealthPotion,
    UpgradeAbility
};

using WaveInfo = std::map<unsigned, EnemyWaveInfo>;

class GameModeBase
{
public:
    GameModeBase();

    void Init(SharedContext* Context);

    void Awake();

    void Remove(std::shared_ptr<Object> ThisObject);

    unsigned GetCurrentWave() const { return CurrentWave; }

protected:
    void NextWave();
    void SpawnFirstWave();

    void SpawnPowerUp();

    void AddEnemy(std::shared_ptr<Object> Enemy);

    void RemoveEnemy(std::shared_ptr<Object> Enemy);

private:
    Vector2 RandomLocation(const Vector2& PlayerPosition) const;
    void ImproveEnemy(std::shared_ptr<Object> Enemy, const EnemyInfo& Info);

    SharedContext* Context;

    std::vector<std::shared_ptr<Object>> Enemies;

    WaveInfo GameWave;
    unsigned CurrentWave;

    float StartFirstWaveTime = 5.0f;
    float StartNextWaveTime = 8.0f;

    float ChanceToSpawnPowerUp = 0.2f;
};
