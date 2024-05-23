#include "LevelComponent.h"

#include <fstream>

#include "../../../Core/Directory/Directory.h"
#include "../../../Core/Object/Object.h"
#include "../../UI/HUD/PlayerHUD.h"
#include "../../UI/Widgets/GameUI/GameUI.h"
#include "../../UI/Widgets/LevelBorder/LevelBorder.h"
#include "../../UI/Widgets/PopUp/LevelUp/PopUpLevelUp.h"
#include "../Attribute/AttributeComponent.h"

using Json = nlohmann::json;

LevelComponent::LevelComponent(Object* Owner)
    : ActorComponent(Owner), Level(1), CurrentExperience()
{
}

void LevelComponent::Awake()
{
    ActorComponent::Awake();

    std::string Name = GetOwner()->GetName();
    Name.erase(Name.find('_'));

    Json LevelInfoJson;
    std::ifstream LevelInfoFile(Directory::GetInstance().GetData("Level.json"));
    LevelInfoFile >> LevelInfoJson;

    auto Info = LevelInfoJson[Name];
    for (const auto& InfoJson : Info)
    {
        const auto& [InfoLevel, InfoExperience] = InfoJson["Level"].get<ExperienceLevelTable>();
        ExperienceTable.emplace(InfoLevel, InfoExperience);
    }

    ApplyExperience(0);
}

void LevelComponent::ApplyExperience(unsigned Experience)
{
    CurrentExperience += Experience;

    while (CurrentExperience >= ExperienceTable[Level] && !IsMaxLevel())
    {
        CurrentExperience -= ExperienceTable[Level];
        LevelUp();
    }
}

void LevelComponent::PopUpWidget()
{
    const std::shared_ptr<PlayerHUD> HUD = GetOwner()->GetComponent<PlayerHUD>();

    const Vector2 WindowResolution = Window::GetInstance().GetScreenSize();
    const std::shared_ptr<PopUpLevelUp> LevelUp = std::make_shared<PopUpLevelUp>(GetOwner(),
        Slot{
            Padding{0.0f},
            Crop{0.0f},
            Rectangle{
                WindowResolution.x / 2.0f - 96.0f,
                WindowResolution.y / 2.0f - 84.0f,
                192.0f, 64.0f
            }
        }, nullptr);
    HUD->Add(LevelUp);

    const std::shared_ptr<GameUI> GameUIWidget = HUD->GetGameUIWidget();
    const std::shared_ptr<LevelBorder> PlayerLevelBorder = GameUIWidget->GetLevelBorderWidget();
    PlayerLevelBorder->UpdateLevel();
}

void LevelComponent::LevelUp()
{
    ++Level;

    if (!OwnerAttribute) OwnerAttribute = GetOwner()->GetComponent<AttributeComponent>();

    OwnerAttribute->LevelUp();

    if (!GetOwner()->GetTag()->Compare(Tag::Player)) return;
    PopUpWidget();
}
