#pragma once
#include <memory>
#include <vector>

#include "../../Component/ActorComponent.h"
#include "../UIBase/UIBase.h"

class BaseHUD
    : public ActorComponent
{
public:
    BaseHUD(Object* Owner);
    
    void Awake() override;
    void LateUpdate(float DeltaTime) override;

    virtual void Draw();

protected:
    std::vector<std::shared_ptr<UIBase>> UIElements;
};
