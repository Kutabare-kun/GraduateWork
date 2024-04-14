#pragma once
#include "../UIObject.h"

class Panel
    : public UIObject
{
public:
    template<typename Type>
    std::shared_ptr<Type>& GetFirstChildOfType()
    {
        for (auto& Element : Children)
        {
            if (auto ExistingElement = std::dynamic_pointer_cast<Type>(Element); ExistingElement)
            {
                return ExistingElement;
            }
        }

        return nullptr;
    }

    template<typename Type>
    std::vector<std::shared_ptr<Type>> GetChildrenOfType()
    {
        std::vector<std::shared_ptr<Type>> MatchingChildren;
        for (auto& Element : Children)
        {
            if (auto ExistingElement = std::dynamic_pointer_cast<Type>(Element); ExistingElement)
            {
                MatchingChildren.emplace_back(ExistingElement);
            }
        }

        return MatchingChildren;
    }
    
public:
    Panel(Object* Owner, const Rectangle& Bounds, std::shared_ptr<UIObject>&& Parent = nullptr, Alignment HorizontalAlignment = Alignment::None);
    
    void Awake() override;
    void Update(float DeltaTime) override;
    void Draw() override;

protected:
    void AddChild(std::shared_ptr<UIObject>& Child);
    void RemoveChild(std::shared_ptr<UIObject>& Child);

private:
    std::vector<std::shared_ptr<UIObject>> Children;
};
