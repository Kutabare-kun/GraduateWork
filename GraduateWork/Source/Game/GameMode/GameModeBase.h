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
    unsigned Slime;
    unsigned Goblin;
    unsigned Eye;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(EnemyInfo, Slime, Goblin, Eye);
};

enum class PowerUpType
{
    HealthPotion,
    UpgradeAbility
};

using WaveInfo = std::map<unsigned, EnemyInfo>;

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

    SharedContext* Context;

    std::vector<std::shared_ptr<Object>> Enemies;

    WaveInfo GameWave;
    unsigned CurrentWave;

    float StartFirstWaveTime = 5.0f;
    float StartNextWaveTime = 8.0f;

    float ChanceToSpawnPowerUp = 0.2f;
};
