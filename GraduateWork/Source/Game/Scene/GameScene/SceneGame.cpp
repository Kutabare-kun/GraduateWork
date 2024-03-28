#include "SceneGame.h"

#include "../../../Core/Animation/Animation.h"
#include "../../../Core/Component/Animation/AnimationComponent.h"
#include "../../../Core/Component/Movement/MovementComponent.h"
#include "../../../Core/Resource/Texture/TextureResource.h"
#include "../../../Core/Component/Sprite/SpriteComponent.h"
#include "../../../Core/Directory/Directory.h"
#include "../../../Core/Object/Pawn/Pawn.h"
#include "../../../Core/StaticFunctions/Debug.h"

SceneGame::SceneGame(Directory& NewDirectory, ResourceAllocator<TextureResource>& NewTextureAllocator)
    : WorkingDirectory(NewDirectory), TextureAllocator(NewTextureAllocator)
{
    Objects = std::make_unique<ObjectCollection>();
    MapParser = std::make_unique<TileMapParser>(TextureAllocator);
}

void SceneGame::OnCreate()
{
    Vector2 MapOffset = {0.0f, 0.0f};
    std::vector<std::shared_ptr<Object>> LevelTiles = MapParser->Parse(WorkingDirectory.GetMap("TestMap.tmx"), MapOffset);
    Objects->AddObject(LevelTiles);
    
    auto InitSpriteAllocator = [this](Object* Object)
    {
        auto Sprite = Object->GetComponent<SpriteComponent>();
        if (!Sprite) return;
        
        Sprite->SetTextureAllocator(&TextureAllocator);
    };

    {
        auto Player = Objects->CreateObject<Pawn>(Vector2{0.0f, 0.0f}, 200.0f);
        PlayerMovement = Player->GetComponent<MovementComponent>();
        auto PlayerAnimation = Player->GetComponent<AnimationComponent>();
        InitSpriteAllocator(Player.get());

        const int RightVikingTextureID = TextureAllocator.Add(WorkingDirectory.GetTexture("RightViking.png"));
        const int LeftVikingTextureID = TextureAllocator.Add(WorkingDirectory.GetTexture("LeftViking.png"));

        constexpr int FrameWidth = 165;
        constexpr int FrameHeight = 145;

        std::shared_ptr<Animation> RightIdleAnimation = std::make_shared<Animation>();
        constexpr float RightIdleAnimFrameTime = 0.2f;
        RightIdleAnimation->AddFrame(RightVikingTextureID, 600, 0, FrameWidth, FrameHeight, RightIdleAnimFrameTime);
        RightIdleAnimation->AddFrame(RightVikingTextureID, 800, 0, FrameWidth, FrameHeight, RightIdleAnimFrameTime);
        RightIdleAnimation->AddFrame(RightVikingTextureID, 0, 145, FrameWidth, FrameHeight, RightIdleAnimFrameTime);
        RightIdleAnimation->AddFrame(RightVikingTextureID, 200, 0, FrameWidth, FrameHeight, RightIdleAnimFrameTime);
        PlayerAnimation->AddAnimation(FacingDirection::Right, AnimationState::Idle, RightIdleAnimation);

        std::shared_ptr<Animation> RightWalkAnimation = std::make_shared<Animation>();
        constexpr float RightWalkAnimFrameTime = 0.15f;
        RightWalkAnimation->AddFrame(RightVikingTextureID, 600, 290, FrameWidth, FrameHeight, RightWalkAnimFrameTime);
        RightWalkAnimation->AddFrame(RightVikingTextureID, 800, 290, FrameWidth, FrameHeight, RightWalkAnimFrameTime);
        RightWalkAnimation->AddFrame(RightVikingTextureID, 0, 435, FrameWidth, FrameHeight, RightWalkAnimFrameTime);
        RightWalkAnimation->AddFrame(RightVikingTextureID, 200, 435, FrameWidth, FrameHeight, RightWalkAnimFrameTime);
        RightWalkAnimation->AddFrame(RightVikingTextureID, 400, 435, FrameWidth, FrameHeight, RightWalkAnimFrameTime);
        PlayerAnimation->AddAnimation(FacingDirection::Right, AnimationState::Walk, RightWalkAnimation);

        std::shared_ptr<Animation> LeftIdleAnimation = std::make_shared<Animation>();
        const float LeftIdleAnimFrameTime = 0.2f;
        LeftIdleAnimation->AddFrame(LeftVikingTextureID, 600, 0, FrameWidth, FrameHeight, LeftIdleAnimFrameTime);
        LeftIdleAnimation->AddFrame(LeftVikingTextureID, 800, 0, FrameWidth, FrameHeight, LeftIdleAnimFrameTime);
        LeftIdleAnimation->AddFrame(LeftVikingTextureID, 0, 145, FrameWidth, FrameHeight, LeftIdleAnimFrameTime);
        LeftIdleAnimation->AddFrame(LeftVikingTextureID, 200, 0, FrameWidth, FrameHeight, LeftIdleAnimFrameTime);
        PlayerAnimation->AddAnimation(FacingDirection::Left, AnimationState::Idle, LeftIdleAnimation);

        std::shared_ptr<Animation> LeftWalkAnimation = std::make_shared<Animation>();
        const float LeftWalkAnimFrameTime = 0.15f;
        LeftWalkAnimation->AddFrame(LeftVikingTextureID, 600, 290, FrameWidth, FrameHeight, LeftWalkAnimFrameTime);
        LeftWalkAnimation->AddFrame(LeftVikingTextureID, 800, 290, FrameWidth, FrameHeight, LeftWalkAnimFrameTime);
        LeftWalkAnimation->AddFrame(LeftVikingTextureID, 0, 435, FrameWidth, FrameHeight, LeftWalkAnimFrameTime);
        LeftWalkAnimation->AddFrame(LeftVikingTextureID, 200, 435, FrameWidth, FrameHeight, LeftWalkAnimFrameTime);
        LeftWalkAnimation->AddFrame(LeftVikingTextureID, 400, 435, FrameWidth, FrameHeight, LeftWalkAnimFrameTime);
        PlayerAnimation->AddAnimation(FacingDirection::Left, AnimationState::Walk, LeftWalkAnimation);

        auto Collider = Player->AddComponent<BoxColliderComponent>(Player.get());
        Collider->SetCollidable(Rectangle{0.0f, 0.0f, FrameWidth, FrameHeight});
        Collider->SetLayer(CollisionLayer::Player);

        Camera = Player->AddComponent<CameraComponent>(Player.get());
        Camera->UpdateZoom(0.5f);
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; ++j)
        {
            constexpr float FrameWidth = 165;
            constexpr float FrameHeight = 145;
            auto Player = Objects->CreateObject<Pawn>(Vector2{FrameWidth * i, FrameHeight * j}, 200.0f);
            auto PlayerAnimation = Player->GetComponent<AnimationComponent>();
            InitSpriteAllocator(Player.get());

            const int RightVikingTextureID = TextureAllocator.Add(WorkingDirectory.GetTexture("RightViking.png"));
            const int LeftVikingTextureID = TextureAllocator.Add(WorkingDirectory.GetTexture("LeftViking.png"));

            std::shared_ptr<Animation> RightIdleAnimation = std::make_shared<Animation>();
            constexpr float RightIdleAnimFrameTime = 0.2f;
            RightIdleAnimation->AddFrame(RightVikingTextureID, 600, 0, FrameWidth, FrameHeight, RightIdleAnimFrameTime);
            RightIdleAnimation->AddFrame(RightVikingTextureID, 800, 0, FrameWidth, FrameHeight, RightIdleAnimFrameTime);
            RightIdleAnimation->AddFrame(RightVikingTextureID, 0, 145, FrameWidth, FrameHeight, RightIdleAnimFrameTime);
            RightIdleAnimation->AddFrame(RightVikingTextureID, 200, 0, FrameWidth, FrameHeight, RightIdleAnimFrameTime);
            PlayerAnimation->AddAnimation(FacingDirection::Right, AnimationState::Idle, RightIdleAnimation);

            std::shared_ptr<Animation> RightWalkAnimation = std::make_shared<Animation>();
            constexpr float RightWalkAnimFrameTime = 0.15f;
            RightWalkAnimation->AddFrame(RightVikingTextureID, 600, 290, FrameWidth, FrameHeight, RightWalkAnimFrameTime);
            RightWalkAnimation->AddFrame(RightVikingTextureID, 800, 290, FrameWidth, FrameHeight, RightWalkAnimFrameTime);
            RightWalkAnimation->AddFrame(RightVikingTextureID, 0, 435, FrameWidth, FrameHeight, RightWalkAnimFrameTime);
            RightWalkAnimation->AddFrame(RightVikingTextureID, 200, 435, FrameWidth, FrameHeight, RightWalkAnimFrameTime);
            RightWalkAnimation->AddFrame(RightVikingTextureID, 400, 435, FrameWidth, FrameHeight, RightWalkAnimFrameTime);
            PlayerAnimation->AddAnimation(FacingDirection::Right, AnimationState::Walk, RightWalkAnimation);

            std::shared_ptr<Animation> LeftIdleAnimation = std::make_shared<Animation>();
            const float LeftIdleAnimFrameTime = 0.2f;
            LeftIdleAnimation->AddFrame(LeftVikingTextureID, 600, 0, FrameWidth, FrameHeight, LeftIdleAnimFrameTime);
            LeftIdleAnimation->AddFrame(LeftVikingTextureID, 800, 0, FrameWidth, FrameHeight, LeftIdleAnimFrameTime);
            LeftIdleAnimation->AddFrame(LeftVikingTextureID, 0, 145, FrameWidth, FrameHeight, LeftIdleAnimFrameTime);
            LeftIdleAnimation->AddFrame(LeftVikingTextureID, 200, 0, FrameWidth, FrameHeight, LeftIdleAnimFrameTime);
            PlayerAnimation->AddAnimation(FacingDirection::Left, AnimationState::Idle, LeftIdleAnimation);

            std::shared_ptr<Animation> LeftWalkAnimation = std::make_shared<Animation>();
            const float LeftWalkAnimFrameTime = 0.15f;
            LeftWalkAnimation->AddFrame(LeftVikingTextureID, 600, 290, FrameWidth, FrameHeight, LeftWalkAnimFrameTime);
            LeftWalkAnimation->AddFrame(LeftVikingTextureID, 800, 290, FrameWidth, FrameHeight, LeftWalkAnimFrameTime);
            LeftWalkAnimation->AddFrame(LeftVikingTextureID, 0, 435, FrameWidth, FrameHeight, LeftWalkAnimFrameTime);
            LeftWalkAnimation->AddFrame(LeftVikingTextureID, 200, 435, FrameWidth, FrameHeight, LeftWalkAnimFrameTime);
            LeftWalkAnimation->AddFrame(LeftVikingTextureID, 400, 435, FrameWidth, FrameHeight, LeftWalkAnimFrameTime);
            PlayerAnimation->AddAnimation(FacingDirection::Left, AnimationState::Walk, LeftWalkAnimation);

            auto Collider = Player->AddComponent<BoxColliderComponent>(Player.get());
            Collider->SetCollidable(Rectangle{0.0f, 0.0f, FrameWidth, FrameHeight});
            Collider->SetLayer(CollisionLayer::Player);
        }
    }
}

void SceneGame::OnDestroy()
{
}

void SceneGame::ProcessInput()
{    
    if (!PlayerMovement) return;
    
    Vector2 PlayerInput = {0, 0};

    if (IsKeyDown(KEY_A)) PlayerInput.x += -1.0f;
    if (IsKeyDown(KEY_D)) PlayerInput.x +=  1.0f;
    if (IsKeyDown(KEY_W)) PlayerInput.y += -1.0f;
    if (IsKeyDown(KEY_S)) PlayerInput.y +=  1.0f;

    // UD = Up Down, LR = Left Right
    constexpr Vector2 DirectionUD = { 0.0f, 1.0f };
    constexpr Vector2 DirectionLR = { 1.0f, 0.0f };
    
    PlayerMovement->InputValue(PlayerInput.y, DirectionUD);
    PlayerMovement->InputValue(PlayerInput.x, DirectionLR);
}

void SceneGame::Update(float DeltaTime)
{
    Objects->ProcessRemovals();
    Objects->ProcessNewObjects();
    
    Objects->Update(DeltaTime);
}

void SceneGame::LateUpdate(float DeltaTime)
{
    Objects->LateUpdate(DeltaTime);
}

void SceneGame::Draw()
{
    BeginMode2D(Camera->GetCamera());
    
    Objects->Draw();

    Debug::GetInstance().Draw();
    
    EndMode2D();
}
