#include "SceneGame.h"

#include "../../../Core/Animation/Animation.h"
#include "../../../Core/Component/Movement/MovementComponent.h"
#include "../../../Core/Resource/Texture/TextureResource.h"
#include "../../../Core/Component/Sprite/SpriteComponent.h"
#include "../../../Core/Directory/Directory.h"
#include "../../../Core/StaticFunctions/Debug.h"
#include "../../Actors/Enemy/Eye/EyeEnemy.h"
#include "../../Actors/Enemy/Goblin/GoblinEnemy.h"
#include "../../Actors/Enemy/Slime/SlimeEnemy.h"
#include "../../Actors/Player/Player.h"
#include "../../Actors/Trader/Trader.h"
#include "../../UI/HUD/PlayerHUD.h"

SceneGame::SceneGame(Directory& NewDirectory, ResourceAllocator<TextureResource>& NewTextureAllocator,
                     ResourceAllocator<FontResource>& NewFontAllocator)
    : WorkingDirectory(NewDirectory), TextureAllocator(NewTextureAllocator), FontAllocator(NewFontAllocator)
{
    DrawableSys = std::make_unique<DrawableSystem>();
    CollisionTree = std::make_unique<Quadtree>(5, 5, 0, Rectangle{0, 0, 8'192, 8'192}, nullptr);
    ColliderSys = std::make_unique<ColliderSystem>(*CollisionTree);
    RaycastSys = std::make_unique<Raycast>(*CollisionTree);
    TimerManagerSys = std::make_unique<TimerManager>();

    Objects = std::make_unique<ObjectCollection>(*DrawableSys, *ColliderSys);
    MapParser = std::make_unique<TileMapParser>(TextureAllocator, Context);
}

void SceneGame::OnCreate()
{
    // Make SharedContext
    Context.Objects = Objects.get();
    Context.TextureAllocator = &TextureAllocator;
    Context.FontAllocator = &FontAllocator;
    Context.RaycastSys = RaycastSys.get();
    Context.TimerManagerSys = TimerManagerSys.get();
    // ~Make SharedContext

    Vector2 MapOffset = {384.0f, 128.0f};
    std::vector<std::shared_ptr<Object>> LevelTiles = MapParser->Parse(WorkingDirectory.GetMap("TestMap.tmx"),
                                                                       MapOffset);
    Objects->AddObject(LevelTiles);

    auto _Player = Objects->CreateObject<Player>(&Context, nullptr, Vector2{400.0f, 400.0f});
    PlayerMovement = _Player->GetMovement();
    Camera = _Player->GetCamera();
    HUD = _Player->GetComponent<PlayerHUD>();

    Context.Camera = &Camera->GetCamera();

    // Objects->CreateObject<Trader>(&Context, Vector2{600.0f, 600.0f});

    Objects->CreateObject<EyeEnemy>(&Context, nullptr, Vector2{700.0f, 700.0f});
    Objects->CreateObject<GoblinEnemy>(&Context, nullptr, Vector2{700.0f, 800.0f});
    Objects->CreateObject<SlimeEnemy>(&Context, nullptr, Vector2{800.0f, 700.0f});
}

void SceneGame::OnDestroy()
{
}

void SceneGame::ProcessInput()
{
    if (!PlayerMovement || !PlayerMovement->IsEnabled()) return;

    Vector2 PlayerInput = {0, 0};

    if (IsKeyDown(KEY_A)) PlayerInput.x += -1.0f;
    if (IsKeyDown(KEY_D)) PlayerInput.x += 1.0f;
    if (IsKeyDown(KEY_W)) PlayerInput.y += -1.0f;
    if (IsKeyDown(KEY_S)) PlayerInput.y += 1.0f;

    const float MouseWheel = GetMouseWheelMove();

    if (MouseWheel > 0.0f) Camera->AddZoom(0.01f);
    if (MouseWheel < 0.0f) Camera->AddZoom(-0.01f);

    // UD = Up Down, LR = Left Right
    constexpr Vector2 DirectionUD = {0.0f, 1.0f};
    constexpr Vector2 DirectionLR = {1.0f, 0.0f};

    PlayerMovement->InputValue(PlayerInput.y, DirectionUD);
    PlayerMovement->InputValue(PlayerInput.x, DirectionLR);
}

void SceneGame::Update(float DeltaTime)
{
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
    Objects->Draw(Camera->GetCamera());

    Debug::GetInstance().Draw(Camera->GetCamera());
}
