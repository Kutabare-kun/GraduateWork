#include "FindLocation.h"

#include "../../../../../Core/Algorithm/Pathfinding/Astar.h"
#include "../../../../../Core/Algorithm/Raycast/Raycast.h"
#include "../../../../../Core/Object/Object.h"
#include "../../../../../Core/StaticFunctions/Debug.h"
#include "../../Simple/BehaviorTreeSimple.h"

FindLocation::FindLocation(std::shared_ptr<Blackboard> NodeBlackboard)
    : BTNode(NodeBlackboard)
{
}

bool FindLocation::Run()
{
    std::shared_ptr<Blackboard> BB = GetBlackboard();
    if (!BB) return false;

    std::shared_ptr<BlackboardSimple> BBS = std::dynamic_pointer_cast<BlackboardSimple>(BB);
    if (!BBS) return false;

    {
        int RowCount{};
        int ColumnCount{};
        constexpr float SIZE{256.0f};

        for (auto& Row : BBS->GetOwner()->GetContext()->CollisionMap)
        {
            for (auto&& Column : Row)
            {
                Debug::GetInstance().DrawRectangle({RowCount * SIZE, ColumnCount * SIZE, SIZE, SIZE},
                                                   Column ? BLUE : DARKGREEN);

                ++RowCount;
            }
            ++ColumnCount;
            RowCount = 0;
        }

        if (BBS->MoveToLocation)
        {
            Debug::GetInstance().DrawLine(BBS->GetOwner()->GetTransform()->GetPosition(), *BBS->MoveToLocation, BLACK);
        }
    }

    if (!BBS->Target) return false;

    if (BBS->MoveToLocation) return true;

    std::shared_ptr<TransformComponent> OwnerTransformComp = BBS->GetOwner()->GetTransform();
    if (!OwnerTransformComp) return false;

    std::shared_ptr<TransformComponent> TargetTransformComp = BBS->Target->GetTransform();
    if (!TargetTransformComp) return false;

    SharedContext* Context = BBS->GetOwner()->GetContext();

    RaycastResult HitResult = Context->RaycastSys->Cast(OwnerTransformComp->GetPosition(),
                                                        TargetTransformComp->GetPosition(),
                                                        BBS->GetOwner()->GetInstanceID()->GetID()
    );

    if (HitResult.Collision == BBS->Target)
    {
        return true;
    }

    const int MaxTileSize = Context->MaxTileSize;

    auto OwnerGridPos = Astar::GetInstance().VecToGrid(OwnerTransformComp->GetPosition(), MaxTileSize);
    auto TargetGridPos = Astar::GetInstance().VecToGrid(TargetTransformComp->GetPosition(), MaxTileSize);

    auto [Success, Path] = Astar::GetInstance().FindPath(Context->CollisionMap,
                                                         OwnerGridPos,
                                                         TargetGridPos
    );

    if (Success)
    {
        const Vector2 Offset{Context->MaxTileSize / 2.0f, Context->MaxTileSize / 2.0f};

        Vector2 Start = OwnerTransformComp->GetPosition();

        for (int Index = 0; Index < Path.size(); ++Index)
        {
            Vector2 EndVec = Astar::GetInstance().GridToVec(Path[Index], MaxTileSize);
            if (Index != 0)
            {
                Debug::GetInstance().DrawLine({Start.x + Offset.x, Start.y + Offset.y},
                                              {EndVec.x + Offset.x, EndVec.y + Offset.y}, BLACK);
            }
            else
            {
                Debug::GetInstance().DrawLine(Start, {EndVec.x + Offset.x, EndVec.y + Offset.y}, BLACK);
            }
            Start = Astar::GetInstance().GridToVec(Path[Index], MaxTileSize);
        }

        BBS->MoveToLocation = Path.empty()
                                  ? nullptr
                                  : std::make_unique<Vector2>(Astar::GetInstance().GridToVec(Path[0], MaxTileSize));

        BBS->MoveToLocation->x += Offset.x;
        BBS->MoveToLocation->y += Offset.y;
    }

    return Success;
}
