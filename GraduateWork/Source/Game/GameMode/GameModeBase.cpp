#include "GameModeBase.h"

#include <fstream>
#include <random>

#include "../../Core/Algorithm/Pathfinding/Astar.h"
#include "../../Core/Collection/ObjectCollection.h"
#include "../../Core/Directory/Directory.h"
#include "../../Core/SceneManager/SceneStateMachine.h"
#include "../../Core/Timer/Manager/TimerManager.h"
#include "../Actors/Enemy/Eye/EyeEnemy.h"
#include "../Actors/Enemy/Goblin/GoblinEnemy.h"
#include "../Actors/Enemy/Slime/SlimeEnemy.h"
#include "../Actors/Player/Player.h"
#include "../Components/Level/LevelComponent.h"
#include "../PowerUp/AbilityUpgrade/AbilityUpgradePowerUp.h"
#include "../PowerUp/Health/HealthPowerUp.h"
#include "../Interface/Level/Ilevel.h"
#include "../Scene/GameWinScene/SceneGameWin.h"

using Json = nlohmann::json;

GameModeBase::GameModeBase()
    : Context(nullptr), CurrentWave(0)
{
}

void GameModeBase::Init(SharedContext* Context)
{
    this->Context = Context;
}

void GameModeBase::Awake()
{
    Context->TimerManagerSys->AddTimer([&]() -> void
    {
        SpawnFirstWave();
    }, StartFirstWaveTime);

    Json WaveInfoJson;
    std::ifstream WaveInfoFile(Directory::GetInstance().GetData("Wave.json"));
    WaveInfoFile >> WaveInfoJson;

    unsigned Count{};

    // TODO: Make Difficult Mode

    auto Info = WaveInfoJson["Easy"];
    for (const auto& BasicJsons : Info)
    {
        auto ThisWave = BasicJsons["Wave"].get<EnemyWaveInfo>();
        GameWave.emplace(Count, ThisWave);
        ++Count;
    }
}

void GameModeBase::Remove(std::shared_ptr<Object> ThisObject)
{
    if (ThisObject->GetTag()->Compare(Tag::Enemy))
        RemoveEnemy(ThisObject);
}

void GameModeBase::NextWave()
{
    const std::shared_ptr<Player> ThisPlayer = Context->Objects->GetObject<Player>();
    const Vector2 PlayerPosition = ThisPlayer->GetTransform()->GetPosition();

    const auto& CurrentWaveInfo = GameWave[CurrentWave];
    for (unsigned CountSlime = 0; CountSlime < CurrentWaveInfo.Slime.Count; ++CountSlime)
    {
        ImproveEnemy(Context->Objects->CreateObject<SlimeEnemy>(Context, nullptr, RandomLocation(PlayerPosition)), CurrentWaveInfo.Slime);
    }

    for (unsigned CountGoblin = 0; CountGoblin < CurrentWaveInfo.Goblin.Count; ++CountGoblin)
    {
        ImproveEnemy(Context->Objects->CreateObject<GoblinEnemy>(Context, nullptr, RandomLocation(PlayerPosition)), CurrentWaveInfo.Goblin);
    }

    for (unsigned CountEye = 0; CountEye < CurrentWaveInfo.Eye.Count; ++CountEye)
    {
        ImproveEnemy(Context->Objects->CreateObject<EyeEnemy>(Context, nullptr, RandomLocation(PlayerPosition)), CurrentWaveInfo.Eye);
    }

    ++CurrentWave;
}

void GameModeBase::SpawnFirstWave()
{
    NextWave();
}

void GameModeBase::SpawnPowerUp()
{
    std::random_device RandomDevice;
    std::mt19937 Generator(RandomDevice());
    std::uniform_real_distribution<float> Distribution(0.0f, 1.0f);

    if (!(Distribution(Generator) <= ChanceToSpawnPowerUp)) return;

    std::shared_ptr<Player> ThisPlayer = Context->Objects->GetObject<Player>();
    const Vector2 PlayerPosition = ThisPlayer->GetTransform()->GetPosition();

    std::uniform_int_distribution<int> DistributionPowerUp(0, static_cast<int>(PowerUpType::UpgradeAbility));
    switch (static_cast<PowerUpType>(DistributionPowerUp(Generator)))
    {
    case PowerUpType::HealthPotion:
        {
            Context->Objects->CreateObject<HealthPowerUp>(Context, nullptr, RandomLocation(PlayerPosition));
        }
        break;
    case PowerUpType::UpgradeAbility:
        {
            Context->Objects->CreateObject<AbilityUpgradePowerUp>(Context, nullptr, RandomLocation(PlayerPosition));
        }
        break;
    }
}

void GameModeBase::AddEnemy(std::shared_ptr<Object> Enemy)
{
    Enemies.push_back(Enemy);
}

void GameModeBase::RemoveEnemy(std::shared_ptr<Object> Enemy)
{
    SpawnPowerUp();

    std::erase(Enemies, Enemy);

    if (Enemies.empty() && CurrentWave < GameWave.size())
    {
        Context->TimerManagerSys->AddTimer([&]()
        {
            NextWave();
        }, StartNextWaveTime);
    }
    else if (Enemies.empty() && CurrentWave == GameWave.size())
    {
        const int SceneID = SceneStateMachine::GetInstance().GetScene<SceneGameWin>();
        SceneStateMachine::GetInstance().SwitchTo(SceneID);
    }
}

Vector2 GameModeBase::RandomLocation(const Vector2& PlayerPosition) const
{
    std::random_device RandomDevice;
    std::mt19937 Generator(RandomDevice());

    const std::pair<int, int> GridPlayerLocation = Astar::GetInstance().VecToGrid(PlayerPosition, Context->MaxTileSize);

    std::uniform_int_distribution<int> LocationOnGrid(0, static_cast<int>(Context->CollisionMap.size()) - 1);
    std::pair<int, int> RandomLocation = std::make_pair(LocationOnGrid(Generator), LocationOnGrid(Generator));

    while (Context->CollisionMap[RandomLocation.first][RandomLocation.second] && RandomLocation != GridPlayerLocation)
    {
        RandomLocation = std::make_pair(LocationOnGrid(Generator), LocationOnGrid(Generator));
    }

    return Astar::GetInstance().GridToVec(RandomLocation, Context->MaxTileSize);
}

void GameModeBase::ImproveEnemy(std::shared_ptr<Object> Enemy, const EnemyInfo& Info)
{
    if (const Ilevel* EnemyLevel = dynamic_cast<Ilevel*>(Enemy.get()); EnemyLevel)
    {
        EnemyLevel->GetLevelComp()->ApplyExperience(Info.Experience);
    }

    AddEnemy(Enemy);
}
