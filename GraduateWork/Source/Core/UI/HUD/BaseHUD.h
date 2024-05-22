#pragma once
#include <memory>
#include <vector>

#include "../../Component/ActorComponent.h"
#include "../UIBase/UIBase.h"

class BaseHUD
    : public ActorComponent, public DrawableComponent
{
public:
    BaseHUD(Object* Owner);

    void Awake() override;
    void LateUpdate(float DeltaTime) override;

    void Draw(const Camera2D& OwnerCamera) override;
    bool ContinueToDraw() const override;

    void ProcessNewElements();
    void ProcessRemovals();

    void Add(std::shared_ptr<UIBase> Element);

private:
    std::vector<std::shared_ptr<UIBase>> UIElements;
    std::vector<std::shared_ptr<UIBase>> NewUIElements;
};
