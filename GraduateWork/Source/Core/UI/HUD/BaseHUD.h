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

    void Draw() override;
    bool ContinueToDraw() const override;

protected:
    std::vector<std::shared_ptr<UIBase>> UIElements;
};
