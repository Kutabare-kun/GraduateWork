#include "FindLocation.h"

#include "../../../../../Core/Algorithm/Pathfinding/Astar.h"
#include "../../../../../Core/Algorithm/Raycast/Raycast.h"
#include "../../../../../Core/Object/Object.h"
#include "../../Simple/BehaviorTreeSimple.h"

FindLocation::FindLocation(std::shared_ptr<Blackboard> NodeBlackboard)
    : BTNode(NodeBlackboard)
{
}

bool FindLocation::Run()
{
    const std::shared_ptr<Blackboard> BB = GetBlackboard();
    if (!BB) return false;

    const std::shared_ptr<BlackboardSimple> BBS = std::dynamic_pointer_cast<BlackboardSimple>(BB);
    if (!BBS) return false;

    if (!BBS->Target) return false;

    if (BBS->MoveToLocation) return true;

    std::shared_ptr<TransformComponent> OwnerTransformComp = BBS->GetOwner()->GetTransform();
    if (!OwnerTransformComp) return false;

    std::shared_ptr<TransformComponent> TargetTransformComp = BBS->Target->GetTransform();
    if (!TargetTransformComp) return false;

    SharedContext* Context = BBS->GetOwner()->GetContext();

    const std::vector<CollisionLayer> Layers{CollisionLayer::Enemy, CollisionLayer::Ability, CollisionLayer::PowerUp};
    RaycastResult HitResult = Context->RaycastSys->Cast(OwnerTransformComp->GetPosition(),
                                                        TargetTransformComp->GetPosition(),
                                                        Layers
    );

    if (HitResult.Collision == BBS->Target)
    {
        return true;
    }

    const int MaxTileSize = Context->MaxTileSize;

    const auto OwnerGridPos = Astar::GetInstance().VecToGrid(OwnerTransformComp->GetPosition(), MaxTileSize);
    const auto TargetGridPos = Astar::GetInstance().VecToGrid(TargetTransformComp->GetPosition(), MaxTileSize);

    const auto [Success, Path] = Astar::GetInstance().FindPath(Context->CollisionMap,
                                                         OwnerGridPos,
                                                         TargetGridPos
    );

    if (Success)
    {
        const Vector2 Offset{
            static_cast<float>(Context->MaxTileSize) / 2.0f, static_cast<float>(Context->MaxTileSize) / 2.0f
        };

        BBS->MoveToLocation = Path.empty()
                                  ? nullptr
                                  : std::make_unique<Vector2>(Astar::GetInstance().GridToVec(Path[0], MaxTileSize));

        if (BBS->MoveToLocation)
        {
            BBS->MoveToLocation->x += Offset.x;
            BBS->MoveToLocation->y += Offset.y;
        }
    }

    return Success;
}
