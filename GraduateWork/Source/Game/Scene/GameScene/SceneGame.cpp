#include "SceneGame.h"

#include "../../../Core/Animation/Animation.h"
#include "../../../Core/Component/Movement/MovementComponent.h"
#include "../../../Core/Resource/Texture/TextureResource.h"
#include "../../../Core/Component/Sprite/SpriteComponent.h"
#include "../../../Core/Component/Camera/CameraComponent.h"
#include "../../../Core/Directory/Directory.h"
#include "../../Actors/Player/Player.h"
#include "../../UI/HUD/PlayerHUD.h"

SceneGame::SceneGame(ResourceAllocator<TextureResource>& NewTextureAllocator,
                     ResourceAllocator<FontResource>& NewFontAllocator)
    : TextureAllocator(NewTextureAllocator), FontAllocator(NewFontAllocator)
{
}

void SceneGame::OnActivate()
{
    Scene::OnActivate();

    DrawableSys = std::make_unique<DrawableSystem>();
    CollisionTree = std::make_unique<Quadtree>(5, 5, 0, Rectangle{0, 0, 8'192, 8'192}, nullptr);
    ColliderSys = std::make_unique<ColliderSystem>(*CollisionTree);
    RaycastSys = std::make_unique<Raycast>(*CollisionTree);
    TimerManagerSys = std::make_unique<TimerManager>();

    GameMode = std::make_unique<GameModeBase>();
    Objects = std::make_unique<ObjectCollection>(*DrawableSys, *ColliderSys, *GameMode);
    MapParser = std::make_unique<TileMapParser>(TextureAllocator, Context);

    // Make SharedContext
    Context.Objects = Objects.get();
    Context.TextureAllocator = &TextureAllocator;
    Context.FontAllocator = &FontAllocator;
    Context.RaycastSys = RaycastSys.get();
    Context.TimerManagerSys = TimerManagerSys.get();
    Context.GameMode = GameMode.get();
    // ~Make SharedContext

    GameMode->Init(&Context);

    constexpr Vector2 MapOffset = {384.0f, 128.0f};
    std::vector<std::shared_ptr<Object>> LevelTiles = MapParser->Parse(Directory::GetInstance().GetMap("TestMap.tmx"),
                                                                       MapOffset);
    Objects->AddObject(LevelTiles);

    const auto ThisPlayer = Objects->CreateObject<Player>(&Context, nullptr, Vector2{400.0f, 400.0f});
    PlayerMovement = ThisPlayer->GetMovement();
    HUD = ThisPlayer->GetComponent<PlayerHUD>();

    Context.Camera = &ThisPlayer->GetCamera()->GetCamera();

    // Start First Wave
    GameMode->Awake();
}

void SceneGame::ProcessInput()
{
    if (!PlayerMovement || !PlayerMovement->IsEnabled()) return;

    Vector2 PlayerInput = {0, 0};

    if (IsKeyDown(KEY_A)) PlayerInput.x += -1.0f;
    if (IsKeyDown(KEY_D)) PlayerInput.x += 1.0f;
    if (IsKeyDown(KEY_W)) PlayerInput.y += -1.0f;
    if (IsKeyDown(KEY_S)) PlayerInput.y += 1.0f;

    // UD = Up Down, LR = Left Right
    constexpr Vector2 DirectionUD = {0.0f, 1.0f};
    constexpr Vector2 DirectionLR = {1.0f, 0.0f};

    PlayerMovement->InputValue(PlayerInput.y, DirectionUD);
    PlayerMovement->InputValue(PlayerInput.x, DirectionLR);
}

void SceneGame::Update(float DeltaTime)
{
    HUD->ProcessRemovals();
    HUD->ProcessNewElements();

    Objects->ProcessRemovals();
    Objects->ProcessNewObjects();

    TimerManagerSys->Update(DeltaTime);

    Objects->Update(DeltaTime);
}

void SceneGame::LateUpdate(float DeltaTime)
{
    Objects->LateUpdate(DeltaTime);
}

void SceneGame::Draw()
{
    Objects->Draw(*Context.Camera);

    //Debug::GetInstance().Draw(*Context.Camera);
}
