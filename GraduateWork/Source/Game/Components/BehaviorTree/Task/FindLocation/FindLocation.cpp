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

    if (!BBS->Target) return false;

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
        Vector2 Start = OwnerTransformComp->GetPosition();
        for (auto& End : Path)
        {
            Debug::GetInstance().DrawLine(Start, Astar::GetInstance().GridToVec(End, MaxTileSize), BLACK);
            Start = Astar::GetInstance().GridToVec(End, MaxTileSize);
        }

        BBS->MoveToLocation = Path.empty()
                                  ? nullptr
                                  : std::make_unique<Vector2>(Astar::GetInstance().GridToVec(Path[0], MaxTileSize));
    }

    return Success;
}
